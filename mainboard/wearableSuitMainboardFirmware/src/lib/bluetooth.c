/*
 * bluetooth.c
 *
 *  Created on: 06.07.2017
 *      Author: kekse
 */

#include "bluetooth.h"
#include "usart.h"


// Bluetooth initialization
void bluetooth_init(void)
{
	usart_init(9600);
}
