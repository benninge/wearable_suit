/*
 * ledSuit.h
 *
 *  Created on: 17.06.2017
 *      Author: kekse
 */

#ifndef LIB_LEDSUIT_H_
#define LIB_LEDSUIT_H_

#include "stm32f4xx.h"
#include "ws2812.h"


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


/*******************************************************************************
 * 																			   *
 *		Manual suit coloring functions:										   *
 *		LED strips are only updated when update is true or after running the   *
 *		update function.													   *
 * 																			   *
 ******************************************************************************/

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
// Returns != 0 if the body part is enabled and 0 if it is disabled
uint8_t ledSuit_getBodyPartEnabledState(bodyPart bodyPart);

// Sets the brightness of a body part
// Updates the LED strips only if (update != 0)
void ledSuit_setBodyPartBrightness(bodyPart bodyPart, uint8_t brightness, uint8_t update);
// Sets the brightness of the whole suit
// Updates the LED strips only if (update != 0)
void ledSuit_setAllBrightness(uint8_t brightness, uint8_t update);
// Returns the brightness of the body part
uint8_t ledSuit_getBodyPartBrightness(bodyPart bodyPart);

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

// Colors a body part with an rgbLed value
// Updates the LED strips only if (update != 0)
void ledSuit_colorBodyPartRgbLed(bodyPart bodyPart, rgbLed rgb, uint8_t update);
// Colors the whole suit with an rgbLed value
// Updates the LED strips only if (update != 0)
void ledSuit_colorAllRgbLed(rgbLed rgb, uint8_t update);


/*******************************************************************************
 * 																			   *
 *		Automatic suit coloring functions:									   *
 *		LED strips are continuously updated by a timer. Those functions use    *
 *		the manual coloring functions and may change the internal state of 	   *
 *		the suit (for example after switching off the strobe, the whole suit   *
 *		remains in the last enabled state)									   *
 * 																			   *
 ******************************************************************************/

// Enables (enabled != 0) or disables (enabled == 0) the strobe function of a body part
void ledSuit_enableBodyPartStrobe(bodyPart bodyPart, uint8_t enabled);
// Enables (enabled != 0) or disables (enabled == 0) the strobe function of the whole suit
void ledSuit_enableAllStrobe(uint8_t enabled);
// Returns != 0 if the body parts strobe function is enabled and 0 if it is disabled
uint8_t ledSuit_getBodyPartStrobeEnabledState(bodyPart bodyPart);
// Sets the strobe toggle time in 10ms (starting with 0)
void ledSuit_setStrobeToggleTime(uint8_t time);
// Returns the strobe toggle time in 10ms (starting with 0)
uint8_t ledSuit_getStrobeToggleTime(void);

#endif /* LIB_LEDSUIT_H_ */
