/*
 * ledSuit.c
 *
 *  Created on: 17.06.2017
 *      Author: kekse
 */

#include "ledSuit.h"
#include "ws2812.h"


// Lengths and start indices of the LED strips of each body part
#define ARM_LENGTH 3
#define LEFT_ARM_START 0
#define RIGHT_ARM_START 3
#define LEG_LENGTH 3
#define LEFT_LEG_START 0
#define RIGHT_LEG_START 3


// Arm structure
typedef struct
{
	rgbLed leds[ARM_LENGTH];
	uint8_t enabled;
} arm;

// Leg structure
typedef struct
{
	rgbLed leds[LEG_LENGTH];
	uint8_t enabled;
} leg;


// Lookup table which contains the RGB values for different colors
const rgbLed _colorLut[ledColorEnumSize] = {
		{ .r = 255, .g = 0, .b = 0 }, // Red
		{ .r = 255, .g = 80, .b = 0 }, // Orange
		{ .r = 255, .g = 170, .b = 0 }, // Yellow
		{ .r = 0, .g = 255, .b = 0 }, // Green
		{ .r = 0, .g = 255, .b = 180 }, // Teal
		{ .r = 0, .g = 0, .b = 255 }, // Blue
		{ .r = 150, .g = 0, .b = 255 }, // Purple
		{ .r = 255, .g = 0, .b = 60 }, // Pink
		{ .r = 255, .g = 255, .b = 255 } }; // White


// Variables containing the LED suit status
arm _leftArm, _rightArm;
leg _leftLeg, _rightLeg;


// Writes the configuration in the _leftArm structure to the LED strip
void _updateLeftArm()
{
	if (_leftArm.enabled)
	{
		ws2812_updateLeds(LEFT_ARM_START, ARM_LENGTH, _leftArm.leds);
	}
	else
	{
		ws2812_switchLedsOff(LEFT_ARM_START, ARM_LENGTH);
	}
}

// Writes the configuration in the _rightArm structure to the LED strip
void _updateRightArm()
{
	if (_rightArm.enabled)
	{
		ws2812_updateLeds(RIGHT_ARM_START, ARM_LENGTH, _rightArm.leds);
	}
	else
	{
		ws2812_switchLedsOff(RIGHT_ARM_START, ARM_LENGTH);
	}
}


// Initializes the LED suit with all LEDs switched off (all LEDs are enabled with color (0, 0, 0))
void ledSuit_init(void)
{
	// Initialize WS2811 library
	ws2812_init();

	// Initialize arms
	_leftArm.enabled = 1;
	_rightArm.enabled = 1;
	for (int i = 0; i < ARM_LENGTH; i++)
	{
		_leftArm.leds[i].r = 0;
		_rightArm.leds[i].r = 0;
		_leftArm.leds[i].g = 0;
		_rightArm.leds[i].g = 0;
		_leftArm.leds[i].b = 0;
		_rightArm.leds[i].b = 0;
	}

	// Initialize legs
	_leftLeg.enabled = 1;
	_rightLeg.enabled = 1;
	for (int i = 0; i < LEG_LENGTH; i++)
	{
		_leftLeg.leds[i].r = 0;
		_rightLeg.leds[i].r = 0;
		_leftLeg.leds[i].g = 0;
		_rightLeg.leds[i].g = 0;
		_leftLeg.leds[i].b = 0;
		_rightLeg.leds[i].b = 0;
	}
}


// Enables (enabled != 0) or disables (enabled == 1) the LEDs of the left arm
void ledSuit_enableLeftArm(uint8_t enabled)
{
	// Update the enabled value in the _leftArm structure
	_leftArm.enabled = enabled;

	// Write the configuration in the _leftArm structure to the LED strip
	_updateLeftArm();
}

// Enables (enabled != 0) or disables (enabled == 1) the LEDs of the right arm
void ledSuit_enableRightArm(uint8_t enabled)
{
	// Update the enabled value in the _rightArm structure
	_rightArm.enabled = enabled;

	// Write the configuration in the _rightArm structure to the LED strip
	_updateRightArm();
}

// Enables (enabled != 0) or disables (enabled == 1) the LEDs of a the whole suit
void ledSuit_enableAll(uint8_t enabled)
{
	// Enable or disable all body parts
	ledSuit_enableLeftArm(enabled);
	ledSuit_enableRightArm(enabled);
}


// Colors the left arm with an RGB value
void ledSuit_colorLeftArmRgb(uint8_t red, uint8_t green, uint8_t blue)
{
	// Update the color values in the _leftArm structure
	for (int i = 0; i < ARM_LENGTH; i++)
	{
		_leftArm.leds[i].r = red;
		_leftArm.leds[i].g = green;
		_leftArm.leds[i].b = blue;
	}

	// Write the color values in the _leftArm structure to the LED strip
	_updateLeftArm();
}

// Colors the right arm with an RGB value
void ledSuit_colorRightArmRgb(uint8_t red, uint8_t green, uint8_t blue)
{
	// Update the color values in the _rightArm structure
	for (int i = 0; i < ARM_LENGTH; i++)
	{
		_rightArm.leds[i].r = red;
		_rightArm.leds[i].g = green;
		_rightArm.leds[i].b = blue;
	}

	// Write the color values in the _rightArm structure to the LED strip
	_updateRightArm();
}


// Colors the whole suit with an RGB value
void ledSuit_colorAllRgb(uint8_t red, uint8_t green, uint8_t blue)
{
	// Color all body parts
	ledSuit_colorLeftArmRgb(red, green, blue);
	ledSuit_colorRightArmRgb(red, green, blue);
}


// Colors the left arm with a color
void ledSuit_colorLeftArm(ledColor color)
{
	// Update the color values in the _leftArm structure
	for (int i = 0; i < ARM_LENGTH; i++)
	{
			_leftArm.leds[i] = _colorLut[color];
	}

	// Write the color values in the _leftArm structure to the LED strip
	_updateLeftArm();
}

// Colors the right arm with a color
void ledSuit_colorRightArm(ledColor color)
{
	// Update the color values in the _rightArm structure
	for (int i = 0; i < ARM_LENGTH; i++)
	{
		_rightArm.leds[i] = _colorLut[color];
	}

	// Write the color values in the _rightArm structure to the LED strip
	_updateRightArm();
}

// Colors the whole suit with an RGB value
void ledSuit_colorAll(ledColor color)
{
	// Color all body parts
	ledSuit_colorLeftArm(color);
	ledSuit_colorRightArm(color);
}
