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


// Length of arms and legs
#define ARM_LENGTH 150
#define LEG_LENGTH 3
#define LEFT_ARM_LENGTH ARM_LENGTH
#define RIGHT_ARM_LENGTH ARM_LENGTH
#define LEFT_LEG_LENGTH LEG_LENGTH
#define RIGHT_LEG_LENGTH LEG_LENGTH


// Body parts
#define LEFT_ARM 0x01
#define RIGHT_ARM 0x02
#define LEFT_LEG 0x04
#define RIGHT_LEG 0x08
#define WHOLE_SUIT (LEFT_ARM + RIGHT_ARM + LEFT_LEG + RIGHT_LEG)


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
	black, // Led off
	ledColorEnumSize // Used to determine enum size
} ledColor;

typedef enum
{
	forwards,
	backwards
} direction;



// Initializes the LED suit with all LEDs switched off (all LEDs are enabled with color (0, 0, 0))
void ledSuit_init(void);


/******************************************************************************
 * 																			  *
 *		Manual suit coloring functions:										  *
 *		LED strips are only updated when update is true or after running	  *
 *		the update function.												  *
 *		Body part may be a combination of the body parts defined above.	      *										   *
 * 																			  *
 ******************************************************************************/

// Writes the configuration of a body part to the LED strip
void ledSuit_update(uint8_t bodyPart);

// Enables (enabled != 0) or disables (enabled == 0) the LEDs of a body part
void ledSuit_enable(uint8_t bodyPart, uint8_t enabled, uint8_t update);
// Returns the enabled state (enabled != 0) of the body part (for multiple body parts, the first in the list above is selected)
uint8_t ledSuit_getEnabled(uint8_t bodyPart);

// Sets the brightness of a body part
void ledSuit_setBrightness(uint8_t bodyPart, uint8_t brightness, uint8_t update);
// Returns the brightness of the body part (for multiple body parts, the first in the list above is selected)
uint8_t ledSuit_getBrightness(uint8_t bodyPart);

// Colors a number of LEDs with an RGB value (ledCount == 0 colors the whole body part)
void ledSuit_colorRgb(uint8_t bodyPart, uint16_t startIndex, uint16_t ledCount, uint8_t red, uint8_t green, uint8_t blue, uint8_t update);
// Colors a number of LEDs with a color (ledCount == 0 colors the whole body part)
void ledSuit_color(uint8_t bodyPart, uint16_t startIndex, uint16_t ledCount, ledColor color, uint8_t update);
// Colors a number of LEDs with an rgbLed value (ledCount == 0 colors the whole body part)
void ledSut_colorRgbLed(uint8_t bodyPart, uint16_t startIndex, uint16_t ledCount, rgbLed rgb, uint8_t update);
// Colors a number of LEDs with the values of an LED array
void ledSut_colorArray(uint8_t bodyPart, uint16_t startIndex, uint16_t ledCount, rgbLed * leds, uint8_t update);
// Colors a body part with a color fade of 2 to 10 colors
void ledSuit_colorFade(uint8_t bodyPart, uint8_t colorCount, rgbLed * colors, uint8_t update);

// Rotates the colors of a body part in the given direction
void ledSuit_Rotate(uint8_t bodyPart, direction direction, uint8_t update);
// Shifts the colors of a body part in the given direction, shiftColor is the new color of the first/last LED
void ledSuit_Shift(uint8_t bodyPart, direction direction, rgbLed shiftColor, uint8_t update);


/******************************************************************************
 * 																			  *
 *		Automatic suit coloring functions:									  *
 *		LED strips are continuously updated by a timer. Those functions		  *
 *		use the manual coloring functions and may change the internal 		  *
 *		state of the suit. (for example after switching off the strobe, 	  *
 *		the whole suit remains in the last enabled state.)					  *
 *		Body part may be a combination of the body parts defined above.	 	  *
 * 																			  *
 ******************************************************************************/

/************************
 *** Strobe functions ***
 ************************/
// Enables (enabled != 0) or disables (enabled == 0) the strobe function of a body part
void ledSuit_enableStrobe(uint8_t bodyPart, uint8_t enabled);
// Returns the enabled state (enabled != 0) of the body parts strobe function (for multiple body parts, the first in the list above is selected)
uint8_t ledSuit_getStrobeEnabledState(uint8_t bodyPart);
// Sets the strobe period in 20ms steps (starting with 0)
void ledSuit_setStrobePeriod(uint8_t time);

/*****************************
 *** Auto rotate functions ***
 *****************************/
// Enables (enabled != 0) or disables (enabled == 0) the auto rotate function of a body part
void ledSuit_enableAutoRotate(uint8_t bodyPart, uint8_t enabled);
// Returns the enabled state (enabled != 0) of the body parts auto rotate function (for multiple body parts, the first in the list above is selected)
uint8_t ledSuit_getAutoRotateEnabledState(uint8_t bodyPart);
// Configures the auto rotate function of a body part
void ledSuit_configureAutoRotate(uint8_t bodyPart, direction direction, uint8_t speed);

/*********************************
 *** Auto color fade functions ***
 *********************************/
// Enables ((enabled != 0) or disables (enabled == 0) the auto color fade function of a body part
void ledSuit_enableAutoColorFade(uint8_t bodyPart, uint8_t enabled);
// Returns the enabled state (enabled != 0) of the body parts auto color fade function (for multiple body parts, the first in the list above is selected)
uint8_t ledSuit_getAutoColorFadeEnabledState(uint8_t bodyPart);
// Configures the auto color fade function of a body part
void ledSuit_configureAutoColorFade(uint8_t bodyPart, uint8_t colorCount, rgbLed * colors, uint8_t speed);
// Synchronizes the auto color fade functions of all body parts (for a synchronous operation, all body parts have to be configured with the same speed)
void ledSuit_synchronizeAutoColorFade();


#endif /* LIB_LEDSUIT_H_ */
