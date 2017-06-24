/*
 * ledSuit.c
 *
 *  Created on: 17.06.2017
 *      Author: kekse
 */

#include "ledSuit.h"


// Length of arms and legs
#define ARM_LENGTH 150
#define LEG_LENGTH 3
// Length, channel and start index of the LED strips of the left arm
#define LEFT_ARM_CHANNEL 1
#define LEFT_ARM_START 0
#define LEFT_ARM_LENGTH ARM_LENGTH
// Length, channel and start index of the LED strips of the right arm
#define RIGHT_ARM_CHANNEL 1
#define RIGHT_ARM_START 150
#define RIGHT_ARM_LENGTH ARM_LENGTH
// Length, channel and start index of the LED strips of the left leg
#define LEFT_LEG_CHANNEL 2
#define LEFT_LEG_START 0
#define LEFT_LEG_LENGTH LEG_LENGTH
// Length, channel and start index of the LED strips of the right leg
#define RIGHT_LEG_CHANNEL 2
#define RIGHT_LEG_START 3
#define RIGHT_LEG_LENGTH LEG_LENGTH

// Auto rotate structure
typedef struct
{
	uint8_t enabled;
	direction direction;
	uint8_t speed; // 255 = 500steps/s, 0 ~ 2steps/s
} autoRotate;

// Auto color fade structure
typedef struct
{
	uint8_t enabled;
	uint8_t colorCount;
	rgbLed colors[10];
	uint8_t speed;
} autoColorFade;

// Arm structure
typedef struct
{
	uint8_t enabled;
	rgbLed leds[ARM_LENGTH];
	uint8_t brightness;
	uint8_t strobeEnabled;
	autoRotate autoRotateState;
	autoColorFade autoColorFadeState;
} arm;

// Leg structure
typedef struct
{
	uint8_t enabled;
	rgbLed leds[LEG_LENGTH];
	uint8_t brightness;
	uint8_t strobeEnabled;
	autoRotate autoRotateState;
	autoColorFade autoColorFadeState;
} leg;


// Lookup table which contains the RGB values for different colors
const rgbLed _colorLut[ledColorEnumSize] = {
		{ .r = 255, .g = 0, .b = 0 }, // Red
		{ .r = 255, .g = 40, .b = 0 }, // Orange
		{ .r = 255, .g = 100, .b = 0 }, // Yellow
		{ .r = 0, .g = 255, .b = 0 }, // Green
		{ .r = 0, .g = 255, .b = 130 }, // Teal
		{ .r = 0, .g = 0, .b = 255 }, // Blue
		{ .r = 100, .g = 0, .b = 255 }, // Purple
		{ .r = 255, .g = 0, .b = 60 }, // Pink
		{ .r = 255, .g = 255, .b = 255 }, // White
		{ .r = 0, .g = 0, .b = 0 } }; // Black


// Variables containing the LED suit status
arm _leftArm, _rightArm;
leg _leftLeg, _rightLeg;
uint8_t _strobePeriod; // in 2ms (starting with 0)


// Flags
uint8_t _autoColorFadeSyncFlag = 0; // Flag which tells the auto color fade to synchronize all body parts



// Writes the configuration in the _leftArm structure to the LED strip
void _updateLeftArm()
{
	if (_leftArm.enabled)
	{
		for (uint16_t i = 0; i < LEFT_ARM_LENGTH; i++)
		{
			uint8_t red = (uint16_t)_leftArm.leds[i].r * _leftArm.brightness / 255;
			uint8_t green = (uint16_t)_leftArm.leds[i].g * _leftArm.brightness / 255;
			uint8_t blue = (uint16_t)_leftArm.leds[i].b * _leftArm.brightness / 255;
			ws2812_setLedsRGB(LEFT_ARM_CHANNEL, LEFT_ARM_START + i, 1, red, green, blue);
		}
	}
	else
	{
		ws2812_switchLedsOff(LEFT_ARM_CHANNEL, LEFT_ARM_START, LEFT_ARM_LENGTH); // switch left arm LEDs off
	}
}

// Writes the configuration in the _rightArm structure to the LED strip
void _updateRightArm()
{
	if (_rightArm.enabled)
	{
		for (uint16_t i = 0; i < RIGHT_ARM_LENGTH; i++)
		{
			uint8_t red = (uint16_t)_rightArm.leds[i].r * _rightArm.brightness / 255;
			uint8_t green = (uint16_t)_rightArm.leds[i].g * _rightArm.brightness / 255;
			uint8_t blue = (uint16_t)_rightArm.leds[i].b * _rightArm.brightness / 255;
			ws2812_setLedsRGB(RIGHT_ARM_CHANNEL, RIGHT_ARM_START + i, 1, red, green, blue);
		}
	}
	else
	{
		ws2812_switchLedsOff(RIGHT_ARM_CHANNEL, RIGHT_ARM_START, RIGHT_ARM_LENGTH); // switch right arm LEDs off
	}
}

// Writes the configuration in the _leftLeg structure to the LED strip
void _updateLeftLeg()
{
	if (_leftLeg.enabled)
	{
		for (uint16_t i = 0; i < LEFT_LEG_LENGTH; i++)
		{
			uint8_t red = (uint16_t)_leftLeg.leds[i].r * _leftLeg.brightness / 255;
			uint8_t green = (uint16_t)_leftLeg.leds[i].g * _leftLeg.brightness / 255;
			uint8_t blue = (uint16_t)_leftLeg.leds[i].b * _leftLeg.brightness / 255;
			ws2812_setLedsRGB(LEFT_LEG_CHANNEL, LEFT_LEG_START + i, 1, red, green, blue);
		}
	}
	else
	{
		ws2812_switchLedsOff(LEFT_LEG_CHANNEL, LEFT_LEG_START, LEFT_LEG_LENGTH); // switch left leg LEDs off
	}
}

// Writes the configuration in the _rightLeg structure to the LED strip
void _updateRightLeg()
{
	if (_rightLeg.enabled)
	{
		for (uint16_t i = 0; i < RIGHT_LEG_LENGTH; i++)
		{
			uint8_t red = (uint16_t)_rightLeg.leds[i].r * _rightLeg.brightness / 255;
			uint8_t green = (uint16_t)_rightLeg.leds[i].g * _rightLeg.brightness / 255;
			uint8_t blue = (uint16_t)_rightLeg.leds[i].b * _rightLeg.brightness / 255;
			ws2812_setLedsRGB(RIGHT_LEG_CHANNEL, RIGHT_LEG_START + i, 1, red, green, blue);
		}
	}
	else
	{
		ws2812_switchLedsOff(RIGHT_LEG_CHANNEL, RIGHT_LEG_START, RIGHT_LEG_LENGTH);  // switch right leg LEDs off
	}
}


// Initializes the LED suit with all LEDs switched off (all LEDs are enabled with color (0, 0, 0))
void ledSuit_init(void)
{
	// Initialize WS2811 library
	ws2812_init();

	// Initialize suit
	ledSuit_enableAll(1, 0); // Enable all body parts, do not update the LED strips
	ledSuit_colorAllRgb(0, 0, 0, 0); // Initialize all body parts with color (0, 0, 0), do not update the LED strips
	ledSuit_setAllBrightness(255, 0); // Initialize the brightness of all body parts with 255
	// Initialize strobe
	ledSuit_enableAllStrobe(0); // Initialize all body parts with strobe switched off
	_strobePeriod = 20; // Initialize strobe period
	// Initialize auto rotate
	ledSuit_enableAllAutoRotate(0); // Initialize all body parts with auto rotate switched off
	ledSuit_setAllAutoRotateDirection(forwards); // Initialize auto rotate direction
	ledSuit_setAllAutoRotateSpeed(150); // Initialize auto rotate speed
	// Initialize auto color fade
	ledSuit_enableAllAutoColorFade(0); // Initialize all body parts with auto color fade switched off
	ledSuit_setAllAutoColorFadeColors(1, &_colorLut[black]); // Initialize auto color fade with no colors
	ledSuit_setAllAutoColorFadeSpeed(150);  // Initialize auto color fade speed

	// Initialize system tick timer
	SysTick_Config(SystemCoreClock/500); // system tick timer 1/500 second
}

/*******************************************************************************
 * 																			   *
 *		Manual suit coloring functions:										   *
 * 																			   *
 ******************************************************************************/

// Writes the configuration of a body part to the LED strip
void ledSuit_updateBodyPart(bodyPart bodyPart)
{
	switch (bodyPart)
	{
	case leftArm:
		_updateLeftArm(); // Write the configuration in the _leftArm structure to the LED strip
		break;
	case rightArm:
		_updateRightArm(); // Write the configuration in the _rightArm structure to the LED strip
		break;
	case leftLeg:
		_updateLeftLeg(); // Write the configuration in the _leftLeg structure to the LED strip
		break;
	case rightLeg:
		_updateRightLeg(); // Write the configuration in the _rightLeg structure to the LED strip
		break;
	default:
		return;
	}
}

// Writes the configuration of the whole suit to the LED strip
void ledSuit_updateAll(void)
{
	// Update all body parts
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_updateBodyPart(i);
	}
}

// Enables (enabled != 0) or disables (enabled == 0) the LEDs of a body part
// Updates the LED strips only if (update != 0)
void ledSuit_enableBodyPart(bodyPart bodyPart, uint8_t enabled, uint8_t update)
{
	switch (bodyPart)
	{
	case leftArm:
		_leftArm.enabled = enabled; // Update the enabled value in the _leftArm structure
		break;
	case rightArm:
		_rightArm.enabled = enabled; // Update the enabled value in the _rightArm structure
		break;
	case leftLeg:
		_leftLeg.enabled = enabled; // Update the enabled value in the _leftLeg structure
		break;
	case rightLeg:
		_rightLeg.enabled = enabled; // Update the enabled value in the _rightLeg structure
		break;
	default:
		return;
	}

	if (update)
	{
		// Write the configuration of the body part to the LED strip
		ledSuit_updateBodyPart(bodyPart);
	}
}

// Enables (enabled != 0) or disables (enabled == 0) the LEDs of the whole suit
// Updates the LED strips only if (update != 0)
void ledSuit_enableAll(uint8_t enabled, uint8_t update)
{
	// Enable or disable all body parts
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_enableBodyPart(i, enabled, update);
	}
}

// Returns != 0 if the body part is enabled and 0 if it is disabled
uint8_t ledSuit_getBodyPartEnabledState(bodyPart bodyPart)
{
	// Return body part enabled value
	switch (bodyPart)
	{
	case leftArm:
		return _leftArm.enabled;
	case rightArm:
		return _rightArm.enabled;
	case leftLeg:
		return _leftLeg.enabled;
	case rightLeg:
		return _rightLeg.enabled;
	default:
		return 0;
	}
}

// Sets the brightness of a body part
// Updates the LED strips only if (update != 0)
void ledSuit_setBodyPartBrightness(bodyPart bodyPart, uint8_t brightness, uint8_t update)
{
	switch (bodyPart)
	{
	case leftArm:
		_leftArm.brightness = brightness; // Update the brightness value in the _leftArm structure
		break;
	case rightArm:
		_rightArm.brightness = brightness; // Update the brightness value in the _rightArm structure
		break;
	case leftLeg:
		_leftLeg.brightness = brightness; // Update the brightness value in the _leftLeg structure
		break;
	case rightLeg:
		_rightLeg.brightness = brightness; // Update the brightness value in the _rightLeg structure
		break;
	default:
		return;
	}

	if (update)
	{
		// Write the configuration of the body part to the LED strip
		ledSuit_updateBodyPart(bodyPart);
	}
}

// Sets the brightness of the whole suit
// Updates the LED strips only if (update != 0)
void ledSuit_setAllBrightness(uint8_t brightness, uint8_t update)
{
	// Update the brightness of all body parts
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_setBodyPartBrightness(i, brightness, update);
	}
}

// Returns the brightness of the body part
uint8_t ledSuit_getBodyPartBrightness(bodyPart bodyPart)
{
	// Return body part brightness value
	switch (bodyPart)
	{
	case leftArm:
		return _leftArm.brightness;
	case rightArm:
		return _rightArm.brightness;
	case leftLeg:
		return _leftLeg.brightness;
	case rightLeg:
		return _rightLeg.brightness;
	default:
		return 0;
	}
}

// Colors an array with an RGB value
void _colorArrayRGB(uint16_t length, rgbLed * arrayPointer, uint8_t red, uint8_t green, uint8_t blue)
{
	// Update the color values in the array
	for (uint16_t i = 0; i < length; i++)
	{
		arrayPointer[i].r = red;
		arrayPointer[i].g = green;
		arrayPointer[i].b = blue;
	}
}

// Colors a number of LEDs with an RGB value
// Updates the LED strips only if (update != 0)
void ledSuit_colorLedsRgb(bodyPart bodyPart, uint16_t startIndex, uint16_t ledCount, uint8_t red, uint8_t green, uint8_t blue, uint8_t update)
{
	switch (bodyPart)
	{
	case leftArm:
		// Update the color values in the _leftArm structure
		_colorArrayRGB(ledCount, &_leftArm.leds[startIndex], red, green, blue);
		break;
	case rightArm:
		// Update the color values in the _rightArm structure
		_colorArrayRGB(ledCount, &_rightArm.leds[startIndex], red, green, blue);
		break;
	case leftLeg:
		// Update the color values in the _leftLeg structure
		_colorArrayRGB(ledCount, &_leftLeg.leds[startIndex], red, green, blue);
		break;
	case rightLeg:
		// Update the color values in the _rightLeg structure
		_colorArrayRGB(ledCount, &_rightLeg.leds[startIndex], red, green, blue);
		break;
	default:
		return;
	}

	if (update)
	{
		// Write the configuration of the body part to the LED strip
		ledSuit_updateBodyPart(bodyPart);
	}
}

// Colors a body part with an RGB value
// Updates the LED strips only if (update != 0)
void ledSuit_colorBodyPartRgb(bodyPart bodyPart, uint8_t red, uint8_t green, uint8_t blue, uint8_t update)
{
	switch (bodyPart)
	{
	case leftArm:
		// Update the color values in the _leftArm structure
		_colorArrayRGB(LEFT_ARM_LENGTH, _leftArm.leds, red, green, blue);
		break;
	case rightArm:
		// Update the color values in the _rightArm structure
		_colorArrayRGB(RIGHT_ARM_LENGTH, _rightArm.leds, red, green, blue);
		break;
	case leftLeg:
		// Update the color values in the _leftLeg structure
		_colorArrayRGB(LEFT_LEG_LENGTH, _leftLeg.leds, red, green, blue);
		break;
	case rightLeg:
		// Update the color values in the _rightLeg structure
		_colorArrayRGB(RIGHT_LEG_LENGTH, _rightLeg.leds, red, green, blue);
		break;
	default:
		return;
	}

	if (update)
	{
		// Write the configuration of the body part to the LED strip
		ledSuit_updateBodyPart(bodyPart);
	}
}

// Colors the whole suit with an RGB value
// Updates the LED strips only if (update != 0)
void ledSuit_colorAllRgb(uint8_t red, uint8_t green, uint8_t blue, uint8_t update)
{
	// Color all body parts
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_colorBodyPartRgb(i, red, green, blue, update);
	}
}

// Colors a number of LEDs
// Updates the LED strips only if (update != 0)
void ledSuit_colorLeds(bodyPart bodyPart, uint16_t startIndex, uint16_t ledCount, ledColor color, uint8_t update)
{
	ledSuit_colorLedsRgb(bodyPart, startIndex, ledCount, _colorLut[color].r, _colorLut[color].g, _colorLut[color].b, update);
}

// Colors a body part with a color
// Updates the LED strips only if (update != 0)
void ledSuit_colorBodyPart(bodyPart bodyPart, ledColor color, uint8_t update)
{
	ledSuit_colorBodyPartRgb(bodyPart, _colorLut[color].r, _colorLut[color].g, _colorLut[color].b, update);
}

// Colors the whole suit with a color
// Updates the LED strips only if (update != 0)
void ledSuit_colorAll(ledColor color, uint8_t update)
{
	ledSuit_colorAllRgb(_colorLut[color].r, _colorLut[color].g, _colorLut[color].b, update);
}

// Colors a number of LEDs with an rgbLed value
// Updates the LED strips only if (update != 0)
void ledSut_colorLedsRgbLed(bodyPart bodyPart, uint16_t startIndex, uint16_t ledCount, rgbLed rgb, uint8_t update)
{
	ledSuit_colorLedsRgb(bodyPart, startIndex, ledCount, rgb.r, rgb.g, rgb.b, update);
}

// Colors a body part with an rgbLed value
// Updates the LED strips only if (update != 0)
void ledSuit_colorBodyPartRgbLed(bodyPart bodyPart, rgbLed rgb, uint8_t update)
{
	ledSuit_colorBodyPartRgb(bodyPart, rgb.r, rgb.g, rgb.b, update);
}

// Colors the whole suit with an rgbLed value
// Updates the LED strips only if (update != 0)
void ledSuit_colorAllRgbLed(rgbLed rgb, uint8_t update)
{
	ledSuit_colorAllRgb(rgb.r, rgb.g, rgb.b, update);
}

// Colors a number of LEDs with the values of an LED array
// Updates the LED strips only if (update != 0)
void ledSut_colorLedsArray(bodyPart bodyPart, uint16_t startIndex, uint16_t ledCount, rgbLed * leds, uint8_t update)
{
	for (uint16_t i = 0; i < ledCount; i++)
	{
		ledSut_colorLedsRgbLed(bodyPart, startIndex + i, 1, leds[i], update);
	}

	if (update)
	{
		// Write the configuration of the body part to the LED strip
		ledSuit_updateBodyPart(bodyPart);
	}
}

// Colors a part of an LED array with a color fade
void _colorLedArrayPartFade(uint16_t length, rgbLed * arrayPointer, rgbLed color1, rgbLed color2)
{
	for (uint16_t i = 0; i < length; i++) // Loop through all LEDs
	{
		// Assign a weighted average of the colors to the individual LED
		arrayPointer[i].r = (color1.r * (length - i) / length) + (color2.r * i / length);
		arrayPointer[i].g = (color1.g * (length - i) / length) + (color2.g * i / length);
		arrayPointer[i].b = (color1.b * (length - i) / length) + (color2.b * i / length);
	}
}

// Colors a part of an LED array with a color fade of 2 to 10 colors
void _colorLedArrayPartMultipleColorFade(uint16_t length, rgbLed * arrayPointer, uint8_t colorCount, rgbLed * colors)
{
	uint16_t markers[10]; // Array containing the positions of the base colors
	// Calculate base colors
	for (uint8_t i = 0; i < colorCount; i++)
	{
		markers[i] = length * i / (colorCount - 1);
	}

	for (uint8_t i = 0; i < (colorCount - 1); i++)
	{
		_colorLedArrayPartFade(markers[i + 1] - markers[i], arrayPointer + markers[i], colors[i], colors[i + 1]);
	}
}

// Colors a body part with a color fade of 2 to 10 colors
// Updates the LED strips only if (update != 0)
void ledSuit_colorBodyPartColorFade(bodyPart bodyPart, uint8_t colorCount, rgbLed * colors, uint8_t update)
{
	switch (bodyPart)
	{
	case leftArm:
		// Update the color values in the _leftArm structure
		_colorLedArrayPartMultipleColorFade(LEFT_ARM_LENGTH, _leftArm.leds, colorCount, colors);
		break;
	case rightArm:
		// Update the color values in the _rightArm structure
		_colorLedArrayPartMultipleColorFade(RIGHT_ARM_LENGTH, _rightArm.leds, colorCount, colors);
		break;
	case leftLeg:
		// Update the color values in the _leftLeg structure
		_colorLedArrayPartMultipleColorFade(LEFT_LEG_LENGTH, _leftLeg.leds, colorCount, colors);
		break;
	case rightLeg:
		// Update the color values in the _rightLeg structure
		_colorLedArrayPartMultipleColorFade(RIGHT_LEG_LENGTH, _rightLeg.leds, colorCount, colors);
		break;
	default:
		return;
	}

	if (update)
	{
		// Write the configuration of the body part to the LED strip
		ledSuit_updateBodyPart(bodyPart);
	}
}

// Colors the whole suit with a color fade of up to 10 colors
// Updates the LED strips only if (update != 0)
void ledSuit_colorAllColorFade(uint8_t colorCount, rgbLed * colors, uint8_t update)
{
	// Update the color values of all body parts
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_colorBodyPartColorFade(i, colorCount, colors, update);
	}
}

// Shifts (rotate == 0) or rotates (rotate != 0) an array
// For a shift operation shiftColor is used as new first/last led color
void _shiftRotateLedArray(uint16_t length, rgbLed * arrayPointer, direction direction, uint8_t rotate, rgbLed shiftColor)
{
	if (direction == backwards) // Rotate backwards
	{
		rgbLed firstLed;
		if (rotate)
		{
			firstLed = arrayPointer[0]; // Temporarily store the first LED
		}
		else
		{
			firstLed = shiftColor; // Shift color in
		}


		for (uint16_t i = 0; i < (length - 1); i++) // Loop through all LEDs
		{
			arrayPointer[i] = arrayPointer[i + 1]; // Shift the LED
		}

		arrayPointer[length - 1] = firstLed; // Last LED is now first LED
	}
	else // Rotate forwards
	{
		rgbLed lastLed;
		if (rotate)
		{
			lastLed = arrayPointer[length - 1]; // Temporarily store the last LED
		}
		else
		{
			lastLed = shiftColor; // Shift color in
		}

		for (uint16_t i = (length - 1); i > 0 ; i--) // Loop through all LEDs
		{
			arrayPointer[i] = arrayPointer[i - 1]; // Shift the LED
		}

		arrayPointer[0] = lastLed; // First LED is now last LED
	}
}

// Rotates the colors of a body part forwards (rotateBackwards == 0) or backwards (rotateBackwards != 0)
// Updates the LED strips only if (update != 0)
void ledSuit_rotateBodyPart(bodyPart bodyPart, direction direction, uint8_t update)
{
	switch (bodyPart)
	{
	case leftArm:
		// Update the color values in the _leftArm structure
		_shiftRotateLedArray(LEFT_ARM_LENGTH, _leftArm.leds, direction, 1, _colorLut[black]);
		break;
	case rightArm:
		// Update the color values in the _rightArm structure
		_shiftRotateLedArray(RIGHT_ARM_LENGTH, _rightArm.leds, direction, 1, _colorLut[black]);
		break;
	case leftLeg:
		// Update the color values in the _leftLeg structure
		_shiftRotateLedArray(LEFT_LEG_LENGTH, _leftLeg.leds, direction, 1, _colorLut[black]);
		break;
	case rightLeg:
		// Update the color values in the _rightLeg structure
		_shiftRotateLedArray(RIGHT_LEG_LENGTH, _rightLeg.leds, direction, 1, _colorLut[black]);
		break;
	default:
		return;
	}

	if (update)
	{
		// Write the configuration of the body part to the LED strip
		ledSuit_updateBodyPart(bodyPart);
	}
}

// Rotates the colors of the whole suit forwards (rotateBackwards == 0) or backwards (rotateBackwards != 0)
// Updates the LED strips only if (update != 0)
void ledSuit_rotateAll(direction direction, uint8_t update)
{
	// Update the color values of all body parts
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_rotateBodyPart(i, direction, update);
	}
}

// Shifts the colors of a body part in the given direction, shiftColor is the new color of the first/last LED
// Updates the LED strips only if (update != 0)
void ledSuit_shiftBodyPart(bodyPart bodyPart, direction direction, rgbLed shiftColor, uint8_t update)
{
	switch (bodyPart)
	{
	case leftArm:
		// Update the color values in the _leftArm structure
		_shiftRotateLedArray(LEFT_ARM_LENGTH, _leftArm.leds, direction, 0, shiftColor);
		break;
	case rightArm:
		// Update the color values in the _rightArm structure
		_shiftRotateLedArray(RIGHT_ARM_LENGTH, _rightArm.leds, direction, 0, shiftColor);
		break;
	case leftLeg:
		// Update the color values in the _leftLeg structure
		_shiftRotateLedArray(LEFT_LEG_LENGTH, _leftLeg.leds, direction, 0, shiftColor);
		break;
	case rightLeg:
		// Update the color values in the _rightLeg structure
		_shiftRotateLedArray(RIGHT_LEG_LENGTH, _rightLeg.leds, direction, 0, shiftColor);
		break;
	default:
		return;
	}

	if (update)
	{
		// Write the configuration of the body part to the LED strip
		ledSuit_updateBodyPart(bodyPart);
	}
}

// Shifts the colors of the whole suit in the given direction, shiftColor is the new color of the first/last LED
// Updates the LED strips only if (update != 0)
void ledSuit_shiftAll(direction direction, rgbLed shiftColor, uint8_t update)
{
	// Update the color values of all body parts
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_shiftBodyPart(i, direction, shiftColor, update);
	}
}

/*******************************************************************************
 * 																			   *
 *		Automatic suit coloring functions:									   *
 * 																			   *
 ******************************************************************************/

// Enables (enabled != 0) or disables (enabled == 0) the strobe function of a body part
void ledSuit_enableBodyPartStrobe(bodyPart bodyPart, uint8_t enabled)
{
	switch (bodyPart)
	{
	case leftArm:
		_leftArm.strobeEnabled = enabled; // Update the strobe enabled value in the _leftArm structure
		break;
	case rightArm:
		_rightArm.strobeEnabled = enabled; // Update the strobe enabled value in the _rightArm structure
		break;
	case leftLeg:
		_leftLeg.strobeEnabled = enabled; // Update the strobe enabled value in the _leftLeg structure
		break;
	case rightLeg:
		_rightLeg.strobeEnabled = enabled; // Update the strobe enabled value in the _rightLeg structure
		break;
	default:
		return;
	}
}

// Enables (enabled != 0) or disables (enabled == 0) the strobe function of the whole suit
void ledSuit_enableAllStrobe(uint8_t enabled)
{
	// Update the strobe enabled value of all body parts
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_enableBodyPartStrobe(i, enabled);
	}
}

// Returns != 0 if the body parts strobe function is enabled and 0 if it is disabled
uint8_t ledSuit_getBodyPartStrobeEnabledState(bodyPart bodyPart)
{
	// Return body part strobe enabled value
	switch (bodyPart)
	{
	case leftArm:
		return _leftArm.strobeEnabled;
	case rightArm:
		return _rightArm.strobeEnabled;
	case leftLeg:
		return _leftLeg.strobeEnabled;
	case rightLeg:
		return _rightLeg.strobeEnabled;
	default:
		return 0;
	}
}

// Sets the strobe period in 10ms (starting with 0)
void ledSuit_setStrobePeriod(uint8_t time)
{
	_strobePeriod = time;
}

// Returns the strobe period in 10ms (starting with 0)
uint8_t ledSuit_getStrobePeriod(void)
{
	return _strobePeriod;
}

// Enables (enabled != 0) or disables (enabled == 0) the auto rotate function of a body part
void ledSuit_enableBodyPartAutoRotate(bodyPart bodyPart, uint8_t enabled)
{
	switch (bodyPart)
	{
	case leftArm:
		_leftArm.autoRotateState.enabled = enabled; // Update the auto rotate enabled value in the _leftArm structure
		break;
	case rightArm:
		_rightArm.autoRotateState.enabled = enabled; // Update the auto rotate enabled value in the _rightArm structure
		break;
	case leftLeg:
		_leftLeg.autoRotateState.enabled = enabled; // Update the auto rotate enabled value in the _leftLeg structure
		break;
	case rightLeg:
		_rightLeg.autoRotateState.enabled = enabled; // Update the auto rotate enabled value in the _rightLeg structure
		break;
	default:
		return;
	}
}

// Enables (enabled != 0) or disables (enabled == 0) the auto rotate function of the whole suit
void ledSuit_enableAllAutoRotate(uint8_t enabled)
{
	// Update the auto rotate enabled value of all body parts
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_enableBodyPartAutoRotate(i, enabled);
	}
}

// Returns != 0 if the body parts auto rotate function is enabled and 0 if it is disabled
uint8_t ledSuit_getBodyPartAutoRotateEnabledState(bodyPart bodyPart)
{
	// Return body part auto rotate enabled value
	switch (bodyPart)
	{
	case leftArm:
		return _leftArm.autoRotateState.enabled;
	case rightArm:
		return _rightArm.autoRotateState.enabled;
	case leftLeg:
		return _leftLeg.autoRotateState.enabled;
	case rightLeg:
		return _rightLeg.autoRotateState.enabled;
	default:
		return 0;
	}
}

// Sets the auto rotate direction of a body part
void ledSuit_setBodyPartAutoRotateDirection(bodyPart bodyPart, direction direction)
{
	switch (bodyPart)
	{
	case leftArm:
		_leftArm.autoRotateState.direction = direction; // Update the auto rotate direction value in the _leftArm structure
		break;
	case rightArm:
		_rightArm.autoRotateState.direction = direction; // Update the auto rotate direction value in the _rightArm structure
		break;
	case leftLeg:
		_leftLeg.autoRotateState.direction = direction; // Update the auto rotate direction value in the _leftLeg structure
		break;
	case rightLeg:
		_rightLeg.autoRotateState.direction = direction; // Update the auto rotate direction value in the _rightLeg structure
		break;
	default:
		return;
	}
}

// Sets the auto rotate direction of the whole suit
void ledSuit_setAllAutoRotateDirection(direction direction)
{
	// Update the auto rotate direction value of all body parts
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_setBodyPartAutoRotateDirection(i, direction);
	}
}

// Returns the auto rotate direction of a body part
uint8_t ledSuit_getBodyPartAutoRotateDirection(bodyPart bodyPart)
{
	// Return body part auto rotate direction value
	switch (bodyPart)
	{
	case leftArm:
		return _leftArm.autoRotateState.direction;
	case rightArm:
		return _rightArm.autoRotateState.direction;
	case leftLeg:
		return _leftLeg.autoRotateState.direction;
	case rightLeg:
		return _rightLeg.autoRotateState.direction;
	default:
		return 0;
	}
}

// Sets the auto rotate speed of a body part (255 = 500steps/s, 0 ~ 2steps/s)
void ledSuit_setBodyPartAutoRotateSpeed(bodyPart bodyPart, uint8_t speed)
{
	switch (bodyPart)
	{
	case leftArm:
		_leftArm.autoRotateState.speed = speed; // Update the auto rotate speed value in the _leftArm structure
		break;
	case rightArm:
		_rightArm.autoRotateState.speed = speed; // Update the auto rotate speed value in the _rightArm structure
		break;
	case leftLeg:
		_leftLeg.autoRotateState.speed = speed; // Update the auto rotate speed value in the _leftLeg structure
		break;
	case rightLeg:
		_rightLeg.autoRotateState.speed = speed; // Update the auto rotate speed value in the _rightLeg structure
		break;
	default:
		return;
	}
}

// Sets the auto rotate speed of the whole suit (255 = 500steps/s, 0 ~ 2steps/s)
void ledSuit_setAllAutoRotateSpeed(uint8_t speed)
{
	// Update the auto rotate speed value of all body parts
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_setBodyPartAutoRotateSpeed(i, speed);
	}
}

// Returns the auto rotate speed of a body part (255 = 500steps/s, 0 ~ 2steps/s)
uint8_t ledSuit_getBodyPartAutoRotateSpeed(bodyPart bodyPart)
{
	// Return body part auto rotate speed value
	switch (bodyPart)
	{
	case leftArm:
		return _leftArm.autoRotateState.speed;
	case rightArm:
		return _rightArm.autoRotateState.speed;
	case leftLeg:
		return _leftLeg.autoRotateState.speed;
	case rightLeg:
		return _rightLeg.autoRotateState.speed;
	default:
		return 0;
	}
}

// Enables ((enabled != 0) or disables (enabled == 0) the auto color fade function of a body part
void ledSuit_enableBodyPartAutoColorFade(bodyPart bodyPart, uint8_t enabled)
{
	switch (bodyPart)
	{
	case leftArm:
		_leftArm.autoColorFadeState.enabled = enabled; // Update the auto color fade enabled value in the _leftArm structure
		break;
	case rightArm:
		_rightArm.autoColorFadeState.enabled = enabled; // Update the auto color fade enabled value in the _rightArm structure
		break;
	case leftLeg:
		_leftLeg.autoColorFadeState.enabled = enabled; // Update the auto color fade enabled value in the _leftLeg structure
		break;
	case rightLeg:
		_rightLeg.autoColorFadeState.enabled = enabled; // Update the auto color fade enabled value in the _rightLeg structure
		break;
	default:
		return;
	}
}

// Enables (enabled != 0) or disables (enabled == 0) the auto color fade function of the whole suit
void ledSuit_enableAllAutoColorFade(uint8_t enabled)
{
	// Update the auto color fade enabled value of all body parts
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_enableBodyPartAutoColorFade(i, enabled);
	}
}

// Returns != 0 if the body parts auto color fade function is enabled and 0 if it is disabled
uint8_t ledSuit_getBodyPartAutoColorFadeEnabledState(bodyPart bodyPart)
{
	// Return body part auto color fade enabled value
	switch (bodyPart)
	{
	case leftArm:
		return _leftArm.autoColorFadeState.enabled;
	case rightArm:
		return _rightArm.autoColorFadeState.enabled;
	case leftLeg:
		return _leftLeg.autoColorFadeState.enabled;
	case rightLeg:
		return _rightLeg.autoColorFadeState.enabled;
	default:
		return 0;
	}
}

// Sets the auto color fade colors of a auto color fade structure
void _setAutoColorFadeStructureColorValues(autoColorFade * structurePointer, uint8_t colorCount, rgbLed * colors)
{
	// Set color count
	structurePointer->colorCount = colorCount;
	// Set individual color values
	for (uint8_t i = 0; i < colorCount; i++)
	{
		structurePointer->colors[i]=colors[i];
	}
}

// Sets the auto color fade colors of a body part (2 to 10 colors are supported)
void ledSuit_setBodyPartAutoColorFadeColors(bodyPart bodyPart, uint8_t colorCount, rgbLed * colors)
{
	switch (bodyPart)
	{
	case leftArm:
		// Update the auto color fade colors in the _leftArm structure
		_setAutoColorFadeStructureColorValues(&_leftArm.autoColorFadeState, colorCount, colors);
		break;
	case rightArm:
		// Update the auto color fade colors in the _rightArm structure
		_setAutoColorFadeStructureColorValues(&_rightArm.autoColorFadeState, colorCount, colors);
		break;
	case leftLeg:
		// Update the auto color fade colors in the _leftLeg structure
		_setAutoColorFadeStructureColorValues(&_leftLeg.autoColorFadeState, colorCount, colors);
		break;
	case rightLeg:
		// Update the auto color fade colors in the _rightLeg structure
		_setAutoColorFadeStructureColorValues(&_rightLeg.autoColorFadeState, colorCount, colors);
		break;
	default:
		return;
	}
}

// Sets the auto color fade colors of the whole suit (2 to 10 colors are supported)
void ledSuit_setAllAutoColorFadeColors(uint8_t colorCount, rgbLed * colors)
{
	// Update the auto color fade enabled value of all body parts
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_setBodyPartAutoColorFadeColors(i, colorCount, colors);
	}
}

// Sets the auto color fade speed of a body part
void ledSuit_setBodyPartAutoColorFadeSpeed(bodyPart bodyPart, uint8_t speed)
{
	switch (bodyPart)
	{
	case leftArm:
		_leftArm.autoColorFadeState.speed = speed; // Update the auto color fade speed value in the _leftArm structure
		break;
	case rightArm:
		_rightArm.autoColorFadeState.speed = speed; // Update the auto color fade speed value in the _rightArm structure
		break;
	case leftLeg:
		_leftLeg.autoColorFadeState.speed = speed; // Update the auto color fade speed value in the _leftLeg structure
		break;
	case rightLeg:
		_rightLeg.autoColorFadeState.speed = speed; // Update the auto color fade speed value in the _rightLeg structure
		break;
	default:
		return;
	}
}

// Sets the auto color fade speed of the whole suit
void ledSuit_setAllAutoColorFadeSpeed(uint8_t speed)
{
	// Update the auto color fade speed value of all body parts
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_setBodyPartAutoColorFadeSpeed(i, speed);
	}
}

// Returns the auto color fade speed of a body part
uint8_t ledSuit_getBodyPartAutoColorFadeSpeed(bodyPart bodyPart)
{
	// Return body part auto color fade speed value
	switch (bodyPart)
	{
	case leftArm:
		return _leftArm.autoColorFadeState.speed;
	case rightArm:
		return _rightArm.autoColorFadeState.speed;
	case leftLeg:
		return _leftLeg.autoColorFadeState.speed;
	case rightLeg:
		return _rightLeg.autoColorFadeState.speed;
	default:
		return 0;
	}
}

// Synchronizes the auto color fade functions of all body parts
// For a synchronous operation, all body parts have to be configured with the same speed
void ledSuit_synchronizeAutoColorFade()
{
	_autoColorFadeSyncFlag = 1;
}


// Executes all strobe actions
void _strobe()
{
	static uint8_t strobeCounter = 0;

	if (strobeCounter < _strobePeriod)
	{
		strobeCounter++; // Increment strobe counter
	}
	else
	{
		// Toggle all body parts which have strobe enabled
		for (uint8_t i = 0; i < bodyPartEnumSize; i++)
		{
			if (ledSuit_getBodyPartStrobeEnabledState(i)) // Strobe enabled
			{
				ledSuit_enableBodyPart(i, !ledSuit_getBodyPartEnabledState(i), 1); // Toggle body part
			}
		}
		strobeCounter = 0; // Reset strobe counter
	}
}

// Executes all auto rotate actions
void _autoRotate()
{
	static uint8_t autoRotateCounter[bodyPartEnumSize] = {255};

	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		if (ledSuit_getBodyPartAutoRotateEnabledState(i)) // Auto rotate enabled
		{
			if (autoRotateCounter[i] > ledSuit_getBodyPartAutoRotateSpeed(i))
			{
				autoRotateCounter[i]--; // Decrement auto rotate counter
			}
			else
			{
				ledSuit_rotateBodyPart(i, ledSuit_getBodyPartAutoRotateDirection(i), 1); // Rotate body part
				autoRotateCounter[i] = 255; // Reset auto rotate counter
			}
		}
	}
}

// Returns the auto color fade structure of the body part
autoColorFade _getBodyPartAutoColorFadeStruct(bodyPart bodyPart)
{
	// Return body part auto color fade structure
	switch (bodyPart)
	{
	default:
	case leftArm:
		return _leftArm.autoColorFadeState;
	case rightArm:
		return _rightArm.autoColorFadeState;
	case leftLeg:
		return _leftLeg.autoColorFadeState;
	case rightLeg:
		return _rightLeg.autoColorFadeState;
	}
}

// Executes an auto color fade step of the body part
void _autoColorFadeStep(bodyPart bodyPart)
{
	autoColorFade bodyPartAutoColorFadeStruct = _getBodyPartAutoColorFadeStruct(bodyPart);

	static uint8_t colorFadeColorCounter[bodyPartEnumSize] = {0};
	static uint8_t colorFadeCounter[bodyPartEnumSize] = {0};

	if(_autoColorFadeSyncFlag) // Auto color fade has to be synchronized
	{
		// Reset all auto color fade counters
		for (uint8_t i = 0; i < bodyPartEnumSize; i++)
		{
			colorFadeColorCounter[i] = 0;
			colorFadeCounter[i] = 0;
		}

		_autoColorFadeSyncFlag = 0; // Reset auto color fade sync flag
	}

	rgbLed currentColor, nextColor;

	currentColor = bodyPartAutoColorFadeStruct.colors[colorFadeColorCounter[bodyPart]];

	if (colorFadeColorCounter[bodyPart] < (bodyPartAutoColorFadeStruct.colorCount - 1))
	{
		nextColor = bodyPartAutoColorFadeStruct.colors[colorFadeColorCounter[bodyPart] + 1]; // Fade to next color
	}
	else // Last color reached
	{
		nextColor = bodyPartAutoColorFadeStruct.colors[0]; // Fade back to first color
	}

	// Calculate a weighted average of the colors
	uint8_t red = (currentColor.r * (255 - colorFadeCounter[bodyPart]) / 255)
			+ (nextColor.r * colorFadeCounter[bodyPart] / 255);
	uint8_t green = (currentColor.g * (255 - colorFadeCounter[bodyPart]) / 255)
			+ (nextColor.g * colorFadeCounter[bodyPart] / 255);
	uint8_t blue = (currentColor.b * (255 - colorFadeCounter[bodyPart]) / 255)
			+ (nextColor.b * colorFadeCounter[bodyPart] / 255);

	ledSuit_colorBodyPartRgb(bodyPart, red, green, blue, 1); // Update body part color

	if (colorFadeCounter[bodyPart] < 254)
	{
		colorFadeCounter[bodyPart]++; // Increment color fade counter
	}
	else
	{
		if (colorFadeColorCounter[bodyPart] < (bodyPartAutoColorFadeStruct.colorCount - 1))
		{
			colorFadeColorCounter[bodyPart]++; // Increment color fade color counter
		}
		else
		{
			colorFadeColorCounter[bodyPart] = 0; // Reset color fade color counter
		}
		colorFadeCounter[bodyPart] = 0; // Reset color fade counter
	}
}

// Executes all auto color fade actions
void _autoColorFade()
{
	static uint8_t autoColorFadeCounter[bodyPartEnumSize] = {255};

	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
	{
		if(ledSuit_getBodyPartAutoColorFadeEnabledState(i)) // Auto color fade enabled
		{
			if (autoColorFadeCounter[i] > ledSuit_getBodyPartAutoColorFadeSpeed(i))
			{
				autoColorFadeCounter[i]--; // Decrement auto color fade counter
			}
			else
			{
				_autoColorFadeStep(i); // Execute an auto color fade step
				autoColorFadeCounter[i] = 255; // Reset auto color fade counter
			}
		}
	}
}

// System tick timer interrupt handler
void SysTick_Handler(void)
{
	_strobe();
	_autoRotate();
	_autoColorFade();
}
