/*
 * simonSays.c
 *
 *  Created on: 01.08.2017
 *      Author: kekse
 */

#include "simonSays.h"

#include "ledSuit.h"
#include "rs485.h"


// A very basic and bad delay implementation, only used for demo purposes
void _delay(uint32_t time)
{
	time *= 10000;
	while(time--);
}

// Displays a number from 0 to 3 on the chest
void _displayNumber(uint8_t number)
{
	ledSuit_color(CHEST, 0, 0, black, 0);

	switch (number)
	{
		case 0:
			ledSuit_colorChestPixelRgb(4, 0, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 0, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 1, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 1, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(2, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(2, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(2, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(2, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(2, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(2, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 8, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 8, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 9, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 9, 255, 255, 255, 0);
			break;
		case 1:
			ledSuit_colorChestPixelRgb(6, 0, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 1, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 1, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 8, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 9, 255, 255, 255, 0);
			break;
		case 2:
			ledSuit_colorChestPixelRgb(4, 0, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 0, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 1, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 1, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(2, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(2, 8, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(2, 9, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 9, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 9, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 9, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 9, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 9, 255, 255, 255, 0);
			break;
		case 3:
			ledSuit_colorChestPixelRgb(4, 0, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 0, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 1, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 1, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(2, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(2, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 8, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(6, 8, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 9, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 9, 255, 255, 255, 0);
			break;
		default:
			break;
	}

	ledSuit_update(CHEST);
}

// Gets a "random" number between 0 and 3 based on the current timer2 count register
uint8_t _getRandomBodyPart()
{
	return (uint8_t)((TIM2->CNT & 0x0C) >> 2);
}

// Lights up a body part for a short time
void _showBodyPart(uint8_t bodyPart, ledColor color)
{
	switch (bodyPart)
	{
	case 0:
		ledSuit_color(LEFT_ARM, 0, 0, color, 1);
		_delay(500);
		ledSuit_color(LEFT_ARM, 0, 0, black, 1);
		_delay(500);
		break;
	case 1:
		ledSuit_color(RIGHT_ARM, 0, 0, color, 1);
		_delay(500);
		ledSuit_color(RIGHT_ARM, 0, 0, black, 1);
		_delay(500);
		break;
	case 2:
		ledSuit_color(LEFT_LEG, 0, 0, color, 1);
		_delay(500);
		ledSuit_color(LEFT_LEG, 0, 0, black, 1);
		_delay(500);
		break;
	default:
		ledSuit_color(RIGHT_LEG, 0, 0, color, 1);
		_delay(500);
		ledSuit_color(RIGHT_LEG, 0, 0, black, 1);
		_delay(500);
		break;
	}
}

// Awaits a body part to move and returns its number
uint8_t getBodyPartMoving()
{
	while (1)
	{
		// Get current IMU sensor data
		uint8_t leftArmMoving = rs485_getMoving(leftArmSensor);
		uint8_t rightArmMoving = rs485_getMoving(rightArmSensor);
		uint8_t leftLegMoving = rs485_getMoving(leftLegSensor);
		uint8_t rightLegMoving = rs485_getMoving(rightLegSensor);

		if (leftArmMoving && !rightArmMoving && !leftLegMoving && !rightLegMoving) return 0;
		if (!leftArmMoving && rightArmMoving && !leftLegMoving && !rightLegMoving) return 1;
		if (!leftArmMoving && !rightArmMoving && leftLegMoving && !rightLegMoving) return 2;
		if (!leftArmMoving && !rightArmMoving && !leftLegMoving && rightLegMoving) return 3;
	}
}

// Displays the round number on the chest
void _displayRound(uint16_t round)
{
	ledSuit_color(CHEST, 0, 0, black, 0);

	uint8_t digit0 = round % 10;
	uint8_t digit1 = (round / 10) % 10;
	uint8_t digit2 = round / 100;

	switch (digit0)
	{
		case 0:
			ledSuit_colorChestPixelRgb(8, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 8, 255, 255, 255, 0);
			break;
		case 1:
			ledSuit_colorChestPixelRgb(9, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 8, 255, 255, 255, 0);
			break;
		case 2:
			ledSuit_colorChestPixelRgb(8, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 8, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 8, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 8, 255, 255, 255, 0);
			break;
		case 3:
			ledSuit_colorChestPixelRgb(8, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 8, 255, 255, 255, 0);
			break;
		case 4:
			ledSuit_colorChestPixelRgb(9, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 8, 255, 255, 255, 0);
			break;
		case 5:
			ledSuit_colorChestPixelRgb(7, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 8, 255, 255, 255, 0);
			break;
		case 6:
			ledSuit_colorChestPixelRgb(9, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 8, 255, 255, 255, 0);
			break;
		case 7:
			ledSuit_colorChestPixelRgb(7, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 8, 255, 255, 255, 0);
			break;
		case 8:
			ledSuit_colorChestPixelRgb(8, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 8, 255, 255, 255, 0);
			break;
		default:
			ledSuit_colorChestPixelRgb(8, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(9, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(8, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(7, 8, 255, 255, 255, 0);
			break;
	}

	switch (digit1)
	{
		case 0:
			ledSuit_colorChestPixelRgb(4, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 8, 255, 255, 255, 0);
			break;
		case 1:
			ledSuit_colorChestPixelRgb(5, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 8, 255, 255, 255, 0);
			break;
		case 2:
			ledSuit_colorChestPixelRgb(4, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 8, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 8, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 8, 255, 255, 255, 0);
			break;
		case 3:
			ledSuit_colorChestPixelRgb(4, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 8, 255, 255, 255, 0);
			break;
		case 4:
			ledSuit_colorChestPixelRgb(5, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 8, 255, 255, 255, 0);
			break;
		case 5:
			ledSuit_colorChestPixelRgb(3, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 8, 255, 255, 255, 0);
			break;
		case 6:
			ledSuit_colorChestPixelRgb(5, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 8, 255, 255, 255, 0);
			break;
		case 7:
			ledSuit_colorChestPixelRgb(3, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 8, 255, 255, 255, 0);
			break;
		case 8:
			ledSuit_colorChestPixelRgb(4, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 8, 255, 255, 255, 0);
			break;
		default:
			ledSuit_colorChestPixelRgb(4, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(5, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(4, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(3, 8, 255, 255, 255, 0);
			break;
	}

	switch (digit2)
	{
		case 0:
			break;
		case 1:
			ledSuit_colorChestPixelRgb(1, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(0, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(1, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(1, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(1, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(1, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(1, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(1, 8, 255, 255, 255, 0);
			break;
		default:
			ledSuit_colorChestPixelRgb(0, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(1, 2, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(0, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(1, 3, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(1, 4, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(1, 5, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(0, 6, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(0, 7, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(0, 8, 255, 255, 255, 0);
			ledSuit_colorChestPixelRgb(1, 8, 255, 255, 255, 0);
			break;
	}

	ledSuit_update(CHEST);
}

// Play Simon says
void simonSays_play()
{
	uint8_t gameState[255];

	ledSuit_color(WHOLE_SUIT, 0, 0, black, 1);

	// Start countdown
	_displayNumber(3);
	_delay(1000);
	_displayNumber(2);
	_delay(1000);
	_displayNumber(1);
	_delay(1000);
	_displayNumber(0);
	_delay(1000);
	ledSuit_color(WHOLE_SUIT, 0, 0, black, 1);

	for (uint16_t round = 0; round <= 255; round++)
	{
		// Display round
		_displayRound(round + 1);

		gameState[round] = _getRandomBodyPart();

		// Display game state
		for (uint16_t i = 0; i <= round; i++)
		{
			_showBodyPart(gameState[i], white);
		}

		// Request game state movements
		for (uint16_t i = 0; i <= round; i++)
		{
			if (getBodyPartMoving() == gameState[i]) // Correct movement
			{
				_showBodyPart(gameState[i], green);
			}
			else // Wrong movement
			{
				ledSuit_color(WHOLE_SUIT, 0, 0, red, 1);
				_delay(2000);
				ledSuit_color(WHOLE_SUIT, 0, 0, black, 1);
				_delay(1000);
				return;
			}
		}
	}
}
