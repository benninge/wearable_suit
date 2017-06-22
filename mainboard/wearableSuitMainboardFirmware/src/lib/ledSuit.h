/*
 * ledSuit.h
 *
 *  Created on: 17.06.2017
 *      Author: kekse
 */

#ifndef LIB_LEDSUIT_H_
#define LIB_LEDSUIT_H_

#include "stm32f4xx.h"


typedef enum
{
	red,
	orange,
	yellow,
	green,
	teal,
	blue,
	purple,
	pink,
	white,
	ledColorEnumSize // Used to determine enum size
} ledColor;


// Initializes the LED suit with all LEDs switched off (all LEDs are enabled with color (0, 0, 0))
void ledSuit_init(void);

// Enables (enabled != 0) or disables (enabled == 1) the LEDs of a body part
void ledSuit_enableLeftArm(uint8_t enabled);
void ledSuit_enableRightArm(uint8_t enabled);
void ledSuit_enableLeftLeg(uint8_t enabled);
void ledSuit_enableRightLeg(uint8_t enabled);
// Enables (enabled != 0) or disables (enabled == 1) the LEDs of a the whole suit
void ledSuit_enableAll(uint8_t enabled);

// Colors a body part with an RGB value
void ledSuit_colorLeftArmRgb(uint8_t red, uint8_t green, uint8_t blue);
void ledSuit_colorRightArmRgb(uint8_t red, uint8_t green, uint8_t blue);
void ledSuit_colorLeftLegRgb(uint8_t red, uint8_t green, uint8_t blue);
void ledSuit_colorRightLegRgb(uint8_t red, uint8_t green, uint8_t blue);
// Colors the whole suit with an RGB value
void ledSuit_colorAllRgb(uint8_t red, uint8_t green, uint8_t blue);

// Colors a body part with a color
void ledSuit_colorLeftArm(ledColor color);
void ledSuit_colorRightArm(ledColor color);
void ledSuit_colorLeftLeg(ledColor color);
void ledSuit_colorRightLeg(ledColor color);
// Colors the whole suit with an RGB value
void ledSuit_colorAll(ledColor color);

#endif /* LIB_LEDSUIT_H_ */
