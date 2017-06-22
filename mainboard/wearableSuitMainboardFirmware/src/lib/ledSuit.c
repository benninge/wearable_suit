/*
 * ledSuit.c
 *
 *  Created on: 17.06.2017
 *      Author: kekse
 */

#include "ledSuit.h"
#include "ws2812.h"


// Length of arms and legs
#define ARM_LENGTH 2
#define LEG_LENGTH 1
// Length, channel and start index of the LED strips of the left arm
#define LEFT_ARM_CHANNEL 1
#define LEFT_ARM_START 0
#define LEFT_ARM_LENGTH ARM_LENGTH
// Length, channel and start index of the LED strips of the right arm
#define RIGHT_ARM_CHANNEL 1
#define RIGHT_ARM_START 3
#define RIGHT_ARM_LENGTH ARM_LENGTH
// Length, channel and start index of the LED strips of the left leg
#define LEFT_LEG_CHANNEL 1
#define LEFT_LEG_START 2
#define LEFT_LEG_LENGTH LEG_LENGTH
// Length, channel and start index of the LED strips of the right leg
#define RIGHT_LEG_CHANNEL 1
#define RIGHT_LEG_START 5
#define RIGHT_LEG_LENGTH LEG_LENGTH


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
		ws2812_updateLeds(LEFT_ARM_CHANNEL, LEFT_ARM_START, LEFT_ARM_LENGTH, _leftArm.leds);
	}
	else
	{
		ws2812_switchLedsOff(LEFT_ARM_CHANNEL, LEFT_ARM_START, LEFT_ARM_LENGTH);
	}
}

// Writes the configuration in the _rightArm structure to the LED strip
void _updateRightArm()
{
	if (_rightArm.enabled)
	{
		ws2812_updateLeds(RIGHT_ARM_CHANNEL, RIGHT_ARM_START, RIGHT_ARM_LENGTH, _rightArm.leds);
	}
	else
	{
		ws2812_switchLedsOff(RIGHT_ARM_CHANNEL, RIGHT_ARM_START, RIGHT_ARM_LENGTH);
	}
}

// Writes the configuration in the _leftLeg structure to the LED strip
void _updateLeftLeg()
{
	if (_leftLeg.enabled)
	{
		ws2812_updateLeds(LEFT_LEG_CHANNEL, LEFT_LEG_START, LEFT_LEG_LENGTH, _leftLeg.leds);
	}
	else
	{
		ws2812_switchLedsOff(LEFT_LEG_CHANNEL, LEFT_LEG_START, LEFT_LEG_LENGTH);
	}
}

// Writes the configuration in the _rightLeg structure to the LED strip
void _updateRightLeg()
{
	if (_rightLeg.enabled)
	{
		ws2812_updateLeds(RIGHT_LEG_CHANNEL, RIGHT_LEG_START, RIGHT_LEG_LENGTH, _rightLeg.leds);
	}
	else
	{
		ws2812_switchLedsOff(RIGHT_LEG_CHANNEL, RIGHT_LEG_START, RIGHT_LEG_LENGTH);
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
}

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
	for (int i = 0; i < bodyPartEnumSize; i++)
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
	for (int i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_enableBodyPart(i, enabled, update);
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
		for (int i = 0; i < LEFT_ARM_LENGTH; i++)
		{
			_leftArm.leds[i].r = red;
			_leftArm.leds[i].g = green;
			_leftArm.leds[i].b = blue;
		}
		break;
	case rightArm:
		// Update the color values in the _rightArm structure
		for (int i = 0; i < RIGHT_ARM_LENGTH; i++)
		{
			_rightArm.leds[i].r = red;
			_rightArm.leds[i].g = green;
			_rightArm.leds[i].b = blue;
		}
		break;
	case leftLeg:
		// Update the color values in the _leftLeg structure
		for (int i = 0; i < LEFT_LEG_LENGTH; i++)
		{
			_leftLeg.leds[i].r = red;
			_leftLeg.leds[i].g = green;
			_leftLeg.leds[i].b = blue;
		}
		break;
	case rightLeg:
		// Update the color values in the _rightLeg structure
		for (int i = 0; i < RIGHT_LEG_LENGTH; i++)
		{
			_rightLeg.leds[i].r = red;
			_rightLeg.leds[i].g = green;
			_rightLeg.leds[i].b = blue;
		}
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
	for (int i = 0; i < bodyPartEnumSize; i++)
	{
		ledSuit_colorBodyPartRgb(i, red, green, blue, update);
	}
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
