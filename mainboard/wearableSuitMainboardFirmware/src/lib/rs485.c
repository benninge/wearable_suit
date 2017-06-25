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

#define MAX_STRLEN 254
#define TIMEOUT 50

volatile uint8_t received_string[MAX_STRLEN+1];
uint8_t decoded_string[MAX_STRLEN+1];

// Sensor Data structure
typedef struct
{
	union float2bytes {
		float f;
		uint8_t b[sizeof(float)];
	} ypr0, ypr1, ypr2, accel0, accel1, accel2, gyro0, gyro1, gyro2;
} SensorData;

SensorData Sensor_arm_left;
SensorData Sensor_arm_right;
SensorData Sensor_leg_left;
SensorData Sensor_leg_right;


void rs485_init(uint32_t baudRate) {

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	// Set Clocks
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    // Configure USART2 TX/RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Set Pins
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_USART2);

    // USART Config
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART2, &USART_InitStructure);

	// Initialize Interrupt
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

  /* Enable the USART */
	USART_Cmd(USART2, ENABLE);

	// Setup Enable pin
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}

void USART_puts(USART_TypeDef* USARTx, volatile uint8_t *s){

	while(*s){
		// wait until data register is empty
		while( !(USARTx->SR & 0x00000040) );
		USART_SendData(USARTx, *s);
		*s++;
	}
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
  USART_puts(USART2,&send1 );

  // second nibble
  c = what & 0x0F;
  uint8_t send2 = (c << 4) | (c ^ 0x0F);
  USART_puts(USART2,&send2 );

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
	uint8_t STX = '\2';
	uint8_t ETX = '\3';

	USART_puts(USART2, &STX );
	for (uint8_t i = 0; i < length; i++)
		sendComplemented (data [i]);
	USART_puts(USART2, &ETX );
	sendComplemented (crc8 (data, length));
}  // end of sendMsg

void rs485_requestSensorData(sensorPart sensor) {
	uint8_t msg[2];

	//Enable sending
	GPIO_SetBits(GPIOA, GPIO_Pin_4);

	switch (sensor) {

		case leftArmSensor:
			msg[0] = 1;
			msg[1] = 2;
			rs485_sendMsg(msg, sizeof msg);
			break;
		case rightArmSensor:
			msg[0] = 2;
			msg[1] = 2;
			rs485_sendMsg(msg, sizeof msg);
			break;
		case leftLegSensor:
			msg[0] = 3;
			msg[1] = 2;
			rs485_sendMsg(msg, sizeof msg);
			break;
		case rightLegSensor:
			msg[0] = 4;
			msg[1] = 2;
			rs485_sendMsg(msg, sizeof msg);
			break;
		default:
			return;

	}
	//Disable sending
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}


void USART2_IRQHandler(void){

	// check if the USART2 receive interrupt flag was set
	if( USART_GetITStatus(USART2, USART_IT_RXNE) ){

		static uint8_t cnt = 0; // this counter is used to determine the string length
		char t = USART2->DR; // the character from the USART2 data register is saved in t

		/* check if the received character is not the LF character (used to determine end of string)
		 * or the if the maximum string length has been been reached
		 */
		if( (t != '\3') && (cnt < MAX_STRLEN) ){
			received_string[cnt] = t;
			cnt++;
		}
		else{ // otherwise reset the character counter and analyze the received msg
			cnt = 0;
			uint8_t error;
			error = rs485_recvMsg(decoded_string, MAX_STRLEN+1, TIMEOUT);
			if (error == 0) {
				//TODO: if debug: print error
			}
			else {
				//TODO: adapt for up to 4 bodyparts
		         for ( int i=0; i < sizeof(float); i++ )
		        	 Sensor_arm_left.ypr0.b[i] = decoded_string[2+i];
		         for ( int i=0; i < sizeof(float); i++ )
		        	 Sensor_arm_left.ypr1.b[i] = decoded_string[2+4+i];
		         for ( int i=0; i < sizeof(float); i++ )
		        	 Sensor_arm_left.ypr2.b[i] = decoded_string[2+8+i];
		         for ( int i=0; i < sizeof(float); i++ )
		        	 Sensor_arm_left.gyro0.b[i] = decoded_string[12+2+i];
		         for ( int i=0; i < sizeof(float); i++ )
		        	 Sensor_arm_left.gyro1.b[i] = decoded_string[12+2+4+i];
		         for ( int i=0; i < sizeof(float); i++ )
		        	 Sensor_arm_left.gyro2.b[i] = decoded_string[12+2+8+i];
		         for ( int i=0; i < sizeof(float); i++ )
		        	 Sensor_arm_left.accel0.b[i] = decoded_string[24+2+i];
		         for ( int i=0; i < sizeof(float); i++ )
		        	 Sensor_arm_left.accel1.b[i] = decoded_string[24+2+4+i];
		         for ( int i=0; i < sizeof(float); i++ )
		        	 Sensor_arm_left.accel2.b[i] = decoded_string[24+2+8+i];
			}

		}
	}
}


// receive a message, maximum "length" uint8_ts
// if nothing received, or an error (eg. bad CRC, bad data) return 0
// otherwise, returns length of received data
uint8_t rs485_recvMsg (
              uint8_t * data,                    // decoded_string to receive into
              const uint8_t length,              // maximum decoded_string size
              unsigned long timeout)          // milliseconds before timing out
  {

  bool have_stx = false;
  bool have_etx;
  uint8_t input_pos;
  bool first_nibble;
  uint8_t current_uint8_t;

  for (int i = 0; i < MAX_STRLEN; i++)
    {
      uint8_t inuint8_t = received_string[i];

      switch (inuint8_t)
        {

        case '\2':   // start of text
          have_stx = true;
          have_etx = false;
          input_pos = 0;
          first_nibble = true;
          break;

        case '\3':   // end of text
          have_etx = true;
          break;

        default:
          // wait until packet officially starts
          if (!have_stx)
            break;

          // check uint8_t is in valid form (4 bits followed by 4 bits complemented)
          if ((inuint8_t >> 4) != ((inuint8_t & 0x0F) ^ 0x0F) )
            return 0;  // bad character

          // convert back
          inuint8_t >>= 4;

          // high-order nibble?
          if (first_nibble)
            {
            current_uint8_t = inuint8_t;
            first_nibble = false;
            break;
            }  // end of first nibble

          // low-order nibble
          current_uint8_t <<= 4;
          current_uint8_t |= inuint8_t;
          first_nibble = true;

          // if we have the ETX this must be the CRC
          if (have_etx)
            {
            if (crc8 (data, input_pos) != current_uint8_t)
              return 0;  // bad CRC
            return input_pos;  // return received length
            }  // end if have ETX already

          // keep adding if not full
          if (input_pos < length)
            data [input_pos++] = current_uint8_t;
          else
            return 0;  // overflow
          break;

        }  // end of switch
    } // end of while

  return 0;  // timeout
} // end of recvMsg

