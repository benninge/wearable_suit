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

typedef enum
{
	leftArmSensor,
	rightArmSensor,
	leftLegSensor,
	rightLegSensor,
	sensorPartEnumSize // Used to determine enum size
} sensorPart;

void rs485_init(uint32_t baudRate);
void rs485_sendMsg (const uint8_t * data, const uint8_t length);
uint8_t rs485_recvMsg (uint8_t * data, const uint8_t length);
void rs485_requestSensorData(sensorPart sensor);

#endif /* LIB_RS485_H_ */
