/*
 * ledSuit.c
 *
 *  Created on: 17.06.2017
 *      Author: kekse
 */

#include "ledSuit.h"


// Length of arms and legs
#define ARM_LENGTH 10
#define LEG_LENGTH 3
// Length, channel and start index of the LED strips of the left arm
#define LEFT_ARM_CHANNEL 1
#define LEFT_ARM_START 0
#define LEFT_ARM_LENGTH ARM_LENGTH
// Length, channel and start index of the LED strips of the right arm
#define RIGHT_ARM_CHANNEL 1
#define RIGHT_ARM_START 10
#define RIGHT_ARM_LENGTH ARM_LENGTH
// Length, channel and start index of the LED strips of the left leg
#define LEFT_LEG_CHANNEL 2
#define LEFT_LEG_START 0
#define LEFT_LEG_LENGTH LEG_LENGTH
// Length, channel and start index of the LED strips of the right leg
#define RIGHT_LEG_CHANNEL 2
#define RIGHT_LEG_START 3
#define RIGHT_LEG_LENGTH LEG_LENGTH


// Arm structure
typedef struct
{
	uint8_t enabled;
	rgbLed leds[ARM_LENGTH];
	uint8_t brightness;
	uint8_t strobeEnabled;
} arm;

// Leg structure
typedef struct
{
	uint8_t enabled;
	rgbLed leds[LEG_LENGTH];
	uint8_t brightness;
	uint8_t strobeEnabled;
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
uint8_t _strobeToggleTime = 2; // in 10ms (starting with 0)


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
	ledSuit_enableAllStrobe(0); // Initialize all body parts with strobe switched off

	// Initialize system tick timer
	SysTick_Config(SystemCoreClock/100); // system tick timer 1/100 second
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

// Colors a body part with an RGB value
// Updates the LED strips only if (update != 0)
void ledSuit_colorBodyPartRgb(bodyPart bodyPart, uint8_t red, uint8_t green, uint8_t blue, uint8_t update)
{
	switch (bodyPart)
	{
	case leftArm:
		// Update the color values in the _leftArm structure
		for (uint16_t i = 0; i < LEFT_ARM_LENGTH; i++)
		{
			_leftArm.leds[i].r = red;
			_leftArm.leds[i].g = green;
			_leftArm.leds[i].b = blue;
		}
		break;
	case rightArm:
		// Update the color values in the _rightArm structure
		for (uint16_t i = 0; i < RIGHT_ARM_LENGTH; i++)
		{
			_rightArm.leds[i].r = red;
			_rightArm.leds[i].g = green;
			_rightArm.leds[i].b = blue;
		}
		break;
	case leftLeg:
		// Update the color values in the _leftLeg structure
		for (uint16_t i = 0; i < LEFT_LEG_LENGTH; i++)
		{
			_leftLeg.leds[i].r = red;
			_leftLeg.leds[i].g = green;
			_leftLeg.leds[i].b = blue;
		}
		break;
	case rightLeg:
		// Update the color values in the _rightLeg structure
		for (uint16_t i = 0; i < RIGHT_LEG_LENGTH; i++)
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
	for (uint8_t i = 0; i < bodyPartEnumSize; i++)
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

// Sets the strobe toggle time in 10ms (starting with 0)
void ledSuit_setStrobeToggleTime(uint8_t time)
{
	_strobeToggleTime = time;
}

// Returns the strobe toggle time in 10ms (starting with 0)
uint8_t ledSuit_getStrobeToggleTime(void)
{
	return _strobeToggleTime;
}


// Executes all strobe action, should be called every 10ms
void _strobe()
{
	static uint8_t strobeCounter = 0;
	if (strobeCounter < _strobeToggleTime)
	{
		strobeCounter++; // Increment strobe counter
	}
	else
	{
		for (uint8_t i = 0; i < bodyPartEnumSize; i++)
		{
			ledSuit_enableBodyPart(i, !ledSuit_getBodyPartEnabledState(i), 1);
		}
		strobeCounter = 0; // Reset strobe counter
	}
}

// System tick timer interrupt handler
void SysTick_Handler(void)
{
	_strobe();
}
