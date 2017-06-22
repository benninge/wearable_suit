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

typedef enum
{
	leftArm,
	rightArm,
	leftLeg,
	rightLeg,
	bodyPartEnumSize // Used to determine enum size
} bodyPart;


// Initializes the LED suit with all LEDs switched off (all LEDs are enabled with color (0, 0, 0))
void ledSuit_init(void);

// Writes the configuration of a body part to the LED strip
void ledSuit_updateBodyPart(bodyPart bodyPart);
// Writes the configuration of the whole suit to the LED strip
void ledSuit_updateAll(void);

// Enables (enabled != 0) or disables (enabled == 0) the LEDs of a body part
// Updates the LED strips only if (update != 0)
void ledSuit_enableBodyPart(bodyPart bodyPart, uint8_t enabled, uint8_t update);
// Enables (enabled != 0) or disables (enabled == 0) the LEDs of the whole suit
// Updates the LED strips only if (update != 0)
void ledSuit_enableAll(uint8_t enabled, uint8_t update);

// Colors a body part with an RGB value
// Updates the LED strips only if (update != 0)
void ledSuit_colorBodyPartRgb(bodyPart bodyPart, uint8_t red, uint8_t green, uint8_t blue, uint8_t update);
// Colors the whole suit with an RGB value
// Updates the LED strips only if (update != 0)
void ledSuit_colorAllRgb(uint8_t red, uint8_t green, uint8_t blue, uint8_t update);

// Colors a body part with a color
// Updates the LED strips only if (update != 0)
void ledSuit_colorBodyPart(bodyPart bodyPart, ledColor color, uint8_t update);
// Colors the whole suit with a color
// Updates the LED strips only if (update != 0)
void ledSuit_colorAll(ledColor color, uint8_t update);

#endif /* LIB_LEDSUIT_H_ */
