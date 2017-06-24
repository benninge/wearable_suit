/*
 * rs485.h
 *
 *  Created on: Jun 23, 2017
 *      Author: milan
 */

#ifndef LIB_RS485_H_
#define LIB_RS485_H_

#include <stdbool.h>
#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include <stdint.h>

typedef void (*WriteCallback)  (const uint8_t content);    // send a byte to serial port
typedef int  (*AvailableCallback)  ();    // return number of bytes available
typedef int  (*ReadCallback)  ();    // read a byte from serial port

void rs485_init(uint32_t baudRate);
void rs485_sendMsg (WriteCallback fSend,
              const uint8_t * data, const uint8_t length);
uint8_t rs485_recvMsg (
              uint8_t * data, const uint8_t length,
              unsigned long timeout);

#endif /* LIB_RS485_H_ */
