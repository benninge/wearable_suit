/*
 * usart.c
 *
 *  Created on: 26.07.2017
 *      Author: kekse
 */

#include "usart.h"


// Global variables
uint8_t txBuffer[TX_BUFFER_SIZE]; // USART TX ring buffer
uint16_t txIndexIn = 0, txIndexOut = 0; // USART TX ring buffer indexes
uint8_t rxBuffer[RX_BUFFER_SIZE]; // USART RX ring buffer
uint16_t rxIndexIn = 0, rxIndexOut = 0; // USART RX ring buffer indexes


// USART initialization
void usart_init(uint32_t baudrate)
{
	// GPIO initialization
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // Enable clock for GPIO A
	GPIO_InitTypeDef gpioInitStructure;
	GPIO_StructInit(&gpioInitStructure); // Initialize GPIO initialization structure with default values
	gpioInitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpioInitStructure.GPIO_Mode = GPIO_Mode_AF; // GPIO in alternate function mode
	gpioInitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50MHz GPIO speed
	//gpioInitStructure.GPIO_PuPd = GPIO_PuPd_UP; // Pullup at GPIO
	GPIO_Init(GPIOA, &gpioInitStructure); // Initialize GPIO A
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); // Pin A2 alternate function select
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); // Pin A3 alternate function select

	// USART initialization
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // Enable clock for USART 2
	USART_InitTypeDef usartInitStructure;
	USART_StructInit(&usartInitStructure); // Initialize USART initialization structure with default values
	usartInitStructure.USART_BaudRate = baudrate; // Set USART baud rate
	USART_Init(USART2, &usartInitStructure); // Initialize USART 2

	// Initialize RX/TX interrupts
	NVIC_InitTypeDef nvicInitStructure;
	nvicInitStructure.NVIC_IRQChannel = USART2_IRQn; // USART 2 interrupt
	nvicInitStructure.NVIC_IRQChannelPreemptionPriority = 0; // High priority
	nvicInitStructure.NVIC_IRQChannelSubPriority = 0; // High priority
	nvicInitStructure.NVIC_IRQChannelCmd = ENABLE; // Enable interrupt
	NVIC_Init(&nvicInitStructure); // Initialize USART 2 interrupt
	USART_ClearITPendingBit(USART2, USART_IT_RXNE); // Clear USART 2 RX interrupt flag
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // Enable USART 2 RX interrupt

	//Enable USART 2
	USART_Cmd(USART2, ENABLE);
}

// Writes an array of bytes to the USART (length is the array length), returns 0 on success or 1 if there was not enough space in TX buffer
uint8_t usart_write(uint16_t length, uint8_t * txData)
{
	if (((txIndexIn < txIndexOut) && (txIndexIn + length >= txIndexOut))
			|| ((txIndexIn >= txIndexOut) && (txIndexIn + length >= txIndexOut + TX_BUFFER_SIZE)))
	{
		return 1;
	}
	for (uint16_t i = 0; i < length; i++)
	{
		txBuffer[txIndexIn++] = txData[i]; // Write byte to TX buffer
		if (txIndexIn >= TX_BUFFER_SIZE) txIndexIn = 0; // Set TX buffer index to 0 if the end of the array was reached
	}

	USART_ITConfig(USART2, USART_IT_TXE, ENABLE); // Enable USART 2 TX interrupt
	return 0;
}

// Reads up to (length) bytes from the RX buffer, returns the number of bytes
uint16_t usart_read(uint16_t length, uint8_t * rxData)
{
	for (uint16_t i = 0; i < length; i++)
	{
		if (rxIndexIn == rxIndexOut) return i;// RX buffer empty
		rxData[i] = rxBuffer[rxIndexOut++]; // Read byte from the buffer
	}
	return length;
}


void USART2_IRQHandler(void)
{
	if( USART_GetITStatus(USART2, USART_IT_RXNE)) // RX interrupt
	{
		rxBuffer[rxIndexIn++] = (uint8_t)(USART_ReceiveData(USART2) & 0x00ff); // Read received byte (this automatically clears the interrupt flag)
#ifdef USART_DEBUG
		if (rxIndexIn == rxIndexOut)
		{
			while (1); // Buffer overflow, trap uC, increase RX_BUFFER_SIZE or read the RX buffer faster to fix this error
		}
#endif
	}

	if( USART_GetITStatus(USART2, USART_IT_TXE)) // TX interrupt
	{
		if (txIndexIn == txIndexOut) // TX buffer empty
		{
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE); // Disable USART 2 TX interrupt
		}
		else // TX buffer not empty
		{
			USART_SendData(USART2, (uint16_t)txBuffer[txIndexOut++]); // Send next byte (this automatically clears the interrupt flag)
		}
	}
}
