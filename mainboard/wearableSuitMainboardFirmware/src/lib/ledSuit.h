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

typedef enum
{
	forwards,
	backwards
} direction;



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

// Colors a body part with a color fade of 2 to 10 colors
// Updates the LED strips only if (update != 0)
void ledSuit_colorBodyPartColorFade(bodyPart bodyPart, uint8_t colorCount, rgbLed * colors, uint8_t update);
// Colors the whole suit with a color fade of 2 to 10 colors
// Updates the LED strips only if (update != 0)
void ledSuit_colorAllColorFade(uint8_t colorCount, rgbLed * colors, uint8_t update);

// Rotates the colors of a body part in the given direction
// Updates the LED strips only if (update != 0)
void ledSuit_rotateBodyPart(bodyPart bodyPart, direction direction, uint8_t update);
// Rotates the colors of the whole suit in the given direction
// Updates the LED strips only if (update != 0)
void ledSuit_rotateAll(direction direction, uint8_t update);

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
// Sets the strobe period in 2ms (starting with 0)
void ledSuit_setStrobePeriod(uint8_t time);
// Returns the strobe period in 2ms (starting with 0)
uint8_t ledSuit_getStrobePeriod(void);

// Enables (enabled != 0) or disables (enabled == 0) the auto rotate function of a body part
void ledSuit_enableBodyPartAutoRotate(bodyPart bodyPart, uint8_t enabled);
// Enables (enabled != 0) or disables (enabled == 0) the auto rotate function of the whole suit
void ledSuit_enableAllAutoRotate(uint8_t enabled);
// Returns != 0 if the body parts autoRotate function is enabled and 0 if it is disabled
uint8_t ledSuit_getBodyPartAutoRotateEnabledState(bodyPart bodyPart);
// Sets the auto rotate direction of a body part
void LedSuit_setBodyPartAutoRotateDirection(bodyPart bodyPart, direction direction);
// Sets the auto rotate direction of the whole suit
void LedSuit_setAllAutoRotateDirection(direction direction);
// Returns the auto rotate direction of a body part
uint8_t ledSuit_getBodyPartAutoRotateDirection(bodyPart bodyPart);
// Sets the auto rotate speed of a body part (255 = 500steps/s, 0 ~ 2steps/s)
void LedSuit_setBodyPartAutoRotateSpeed(bodyPart bodyPart, uint8_t speed);
// Sets the auto rotate speed of the whole suit (255 = 500steps/s, 0 ~ 2steps/s)
void LedSuit_setAllAutoRotateSpeed(uint8_t speed);
// Returns the auto rotate speed of a body part (255 = 500steps/s, 0 ~ 2steps/s)
uint8_t ledSuit_getBodyPartAutoRotateSpeed(bodyPart bodyPart);


#endif /* LIB_LEDSUIT_H_ */