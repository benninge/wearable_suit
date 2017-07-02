/*
 * rs485.c

 *
 *  Created on: Jun 23, 2017
 *      Author: milan
 */

#include "rs485.h"

/*
 RS485 protocol library.
 Devised and written by Nick Gammon.
 Date: 14 November 2011
 Version: 1.1
 Version 1.1 reset the timeout period after getting STX.
 Can send from 1 to 255 uint8_ts from one node to another with:
 * Packet start indicator (STX)
 * Each data uint8_t is doubled and inverted to check validity
 * Packet end indicator (ETX)
 * Packet CRC (checksum)
 To allow flexibility with hardware (eg. Serial, SoftwareSerial, I2C)
 you provide three "callback" functions which send or receive data. Examples are:
 void fWrite (const uint8_t what)
 {
 Serial.write (what);
 }
 int fAvailable ()
 {
 return Serial.available ();
 }
 int fRead ()
 {
 return Serial.read ();
 }
PERMISSION TO DISTRIBUTE
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 LIMITATION OF LIABILITY
 The software is provided "as is", without warranty of any kind, express or implied,
 including but not limited to the warranties of merchantability, fitness for a particular
 purpose and noninfringement. In no event shall the authors or copyright holders be liable
 for any claim, damages or other liability, whether in an action of contract,
 tort or otherwise, arising from, out of or in connection with the software
 or the use or other dealings in the software.
 */

#define MAX_STRLEN 100
#define TIMEOUT 50
#define rs485_DEBUG

bool have_stx = false;
bool have_etx = false;
uint8_t decoded_string[MAX_STRLEN+1];

// Sensor Data structure
typedef struct
{
	union float2bytes {
		float f;
		uint8_t b[sizeof(float)];
	} ypr0, ypr1, ypr2, gyro0, gyro1, gyro2, accel0, accel1, accel2;
} SensorData;

SensorData Sensor_arm_left;
SensorData Sensor_arm_right;
SensorData Sensor_leg_left;
SensorData Sensor_leg_right;

void Delay(uint32_t time)
{
	time *= 10000;
	while(time--);
}

void rs485_init(uint32_t baudRate) {

	rs485_complete_string = false;

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	// Set Clocks
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    // Configure USART1 TX/RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Set Pins
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

    // USART Config
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);

	// Initialize Interrupt
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

  /* Enable the USART */
	USART_Cmd(USART1, ENABLE);

	// Setup Enable pin
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

void USART_puts(USART_TypeDef* USARTx, uint8_t s){
		// wait until data register is empty
		while( !(USARTx->SR & 0x00000040) );
		USART_SendData(USARTx, (uint16_t)s);
		//USARTx->DR = (uint16_t)(s & 0x01FF);
		while( !(USARTx->SR & 0x00000040) );
}

// send a uint8_t complemented, repeated
// only values sent would be (in hex):
//   0F, 1E, 2D, 3C, 4B, 5A, 69, 78, 87, 96, A5, B4, C3, D2, E1, F0
void sendComplemented (const uint8_t what)
{
uint8_t c;

  // first nibble
  c = what >> 4;
  uint8_t send1 = (c << 4) | (c ^ 0x0F);
  USART_puts(USART1,send1 );

  // second nibble
  c = what & 0x0F;
  uint8_t send2 = (c << 4) | (c ^ 0x0F);
  USART_puts(USART1,send2 );

}  // end of sendComplemented

// calculate 8-bit CRC
static uint8_t crc8 (const uint8_t *addr, uint8_t len)
{
  uint8_t crc = 0;
  while (len--)
    {
    uint8_t inuint8_t = *addr++;
    for (uint8_t i = 8; i; i--)
      {
      uint8_t mix = (crc ^ inuint8_t) & 0x01;
      crc >>= 1;
      if (mix)
        crc ^= 0x8C;
      inuint8_t >>= 1;
      }  // end of for
    }  // end of while
  return crc;
}  // end of crc8


// send a message of "length" uint8_ts (max 255) to other end
// put STX at start, ETX at end, and add CRC
void rs485_sendMsg (const uint8_t * data, const uint8_t length)
{
	//uint8_t STX = '\2';
	//uint8_t ETX = '\3';

	USART_puts(USART1, '\2' );
	for (uint8_t i = 0; i < length; i++)
		sendComplemented (data [i]);
	USART_puts(USART1, '\3' );
	sendComplemented (crc8 (data, length));
}  // end of sendMsg

//send message to sensor board to request sensor data
void rs485_requestSensorData(sensorPart sensor) {
	uint8_t msg[3];

	//Enable sending
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	//TODO: add delay here?
	Delay(1);
	switch (sensor) {

		case leftArmSensor:
			msg[0] = 1;
			msg[1] = 0;
			rs485_sendMsg(msg, sizeof msg);
			break;
		case rightArmSensor:
			msg[0] = 2;
			msg[1] = 0;
			rs485_sendMsg(msg, sizeof msg);
			break;
		case leftLegSensor:
			msg[0] = 3;
			msg[1] = 0;
			rs485_sendMsg(msg, sizeof msg);
			break;
		case rightLegSensor:
			msg[0] = 4;
			msg[1] = 0;
			rs485_sendMsg(msg, sizeof msg);
			break;
		default:
			return;

	}
	//Disable sending
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

void rs485_updateSensorData(){
	if (rs485_complete_string) {
		//TODO: adapt to arms+legs, depending on sender of packet (2nd byte in string)
		for ( int i=0; i < sizeof(float); i++ ) {
			Sensor_arm_left.ypr0.b[i] = decoded_string[2+i];
			Sensor_arm_left.ypr1.b[i] = decoded_string[2+4+i];
			Sensor_arm_left.ypr2.b[i] = decoded_string[2+8+i];
			Sensor_arm_left.gyro0.b[i] = decoded_string[2+12+i];
			Sensor_arm_left.gyro1.b[i] = decoded_string[2+12+4+i];
			Sensor_arm_left.gyro2.b[i] = decoded_string[2+12+8+i];
			Sensor_arm_left.accel0.b[i] = decoded_string[2+24+i];
			Sensor_arm_left.accel1.b[i] = decoded_string[2+24+4+i];
			Sensor_arm_left.accel2.b[i] = decoded_string[2+24+8+i];
		}

#ifdef rs485_DEBUG
		float debugyypr0 = Sensor_arm_left.ypr0.f;
		float debugyypr1 = Sensor_arm_left.ypr1.f;
		float debugyypr2 = Sensor_arm_left.ypr2.f;
		float debugygyro0 = Sensor_arm_left.gyro0.f;
		float debugygyro1 = Sensor_arm_left.gyro1.f;
		float debugygyro2 = Sensor_arm_left.gyro2.f;
		float debugyaccel0 = Sensor_arm_left.accel0.f;
		float debugyaccel1 = Sensor_arm_left.accel1.f;
		float debugyaccel2 = Sensor_arm_left.accel2.f;
		int debug = 1;
#endif

		rs485_complete_string = false;
	}
}

void USART1_IRQHandler(void){

	// check if the USART1 receive interrupt flag was set
	if( USART_GetITStatus(USART1, USART_IT_RXNE) ){

		static uint8_t cnt = 0; // this counter is used to determine the string length
		static bool first_nibble = false;
		static bool bad_packet = false;
		uint8_t t = USART1->DR; // the character from the USART1 data register is saved in t
		static uint8_t curr_byte;

		switch (t) {
			//begin of packet
			case '\2':
				cnt = 0;
				have_stx = true;
				have_etx = false;
				first_nibble = true;
				bad_packet = false;
				break;
			//end of packet
			case '\3':
				have_etx = true;
				break;

			default:
				//wait for packet start
				if (!have_stx) {
					break;
				}
		        // check if t is in valid form (4 bits followed by 4 bits complemented)
		        if ((t >> 4) != ((t & 0x0F) ^ 0x0F) )
		            bad_packet = true;  // bad byte

		        t >>= 4; //remove complemented bits
		        // high-order nibble?
		        if (first_nibble) {
		            curr_byte = t;
		            first_nibble = false;
		            break;
		            }  // end of first nibble

		        // low-order nibble
		        curr_byte <<= 4;
		        curr_byte |= t;
		        first_nibble = true;

		        // if we have the ETX this must be the CRC
		        if (have_etx) {
		            if (crc8 (decoded_string, cnt) != curr_byte) {
		            	bad_packet = true;
		            } else if (!bad_packet) {
		            	//good and complete packet
		            	//TODO: adapt for up to 4 bodyparts
		            	rs485_complete_string = true;
		            	//rs485_updateSensorData();
		            }
		            break;
		        }

		        // keep adding to string until packet complete
		        if (cnt < MAX_STRLEN) {
		            decoded_string[cnt++] = curr_byte;
		        } else {
		            bad_packet = true;
		        }
		        break;
		}

		//if bad packet, reset and wait for next stx
		if (bad_packet) {
			have_stx = false;
		}
		USART_ClearFlag(USART1, USART_IT_RXNE);
	}
}

