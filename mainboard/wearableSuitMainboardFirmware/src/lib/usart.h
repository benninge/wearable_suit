/*
 * usart.h
 *
 *  Created on: 26.07.2017
 *      Author: kekse
 */

#ifndef LIB_USART_H_
#define LIB_USART_H_

#include "stm32f4xx.h"

//#define USART_DEBUG // Use this only for debugging purposes (This will trap the uC if an RX buffer overflow occurs)
#define TX_BUFFER_SIZE 32 // Size of the TX buffer
#define RX_BUFFER_SIZE 64 // Size of the RX buffer


// USART initialization
void usart_init(uint32_t baudrate);

// Writes an array of bytes to the USART (length is the array length), returns 0 on success or 1 if there was not enough space in TX buffer
uint8_t usart_write(uint16_t length, uint8_t * txData);

// Reads up to (length) bytes from the RX buffer, returns the number of bytes
uint16_t usart_read(uint16_t length, uint8_t * rxData);


#endif /* LIB_USART_H_ */
