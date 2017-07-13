/*
 * ledSuit.c
 *
 *  Created on: 17.06.2017
 *      Author: kekse
 */

#include "ledSuit.h"


// Channel and start index of the LED strips of the left arm
#define LEFT_ARM_CHANNEL 1
#define LEFT_ARM_START 100
// Channel and start index of the LED strips of the right arm
#define RIGHT_ARM_CHANNEL 1
#define RIGHT_ARM_START 200
// Channel and start index of the LED strips of the left leg
#define LEFT_LEG_CHANNEL 2
#define LEFT_LEG_START 0
// Channel and start index of the LED strips of the right leg
#define RIGHT_LEG_CHANNEL 2
#define RIGHT_LEG_START 3
// Channel and start index of the LED strips of the chest
#define CHEST_CHANNEL 1
#define CHEST_START 0


// Auto rotate structure
typedef struct
{
	uint8_t enabled;
	direction direction;
	uint8_t speed;
} autoRotateStruct;

// Auto color fade structure
typedef struct
{
	uint8_t enabled;
	uint8_t colorCount;
	rgbLed colors[10];
	uint8_t speed;
} autoColorFadeStruct;

// Arm structure
typedef struct
{
	uint8_t enabled;
	rgbLed leds[ARM_LENGTH];
	uint8_t brightness;
	uint8_t strobeEnabled;
	autoRotateStruct autoRotateState;
	autoColorFadeStruct autoColorFadeState;
} arm;

// Leg structure
typedef struct
{
	uint8_t enabled;
	rgbLed leds[LEG_LENGTH];
	uint8_t brightness;
	uint8_t strobeEnabled;
	autoRotateStruct autoRotateState;
	autoColorFadeStruct autoColorFadeState;
} leg;

// Chest structure
typedef struct
{
	uint8_t enabled;
	rgbLed leds[CHEST_WIDTH][CHEST_HEIGHT];
	uint8_t brightness;
	uint8_t strobeEnabled;
	autoRotateStruct autoRotateState;
	autoColorFadeStruct autoColorFadeState;
} chest;


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
chest _chest;
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

// Writes the configuration in the _rightLeg structure to the LED strip
void _updateChest()
{
	if (_chest.enabled)
	{
		for (uint8_t y = 0; y < CHEST_HEIGHT; y++)
		{
			for (uint8_t x = 0; x < CHEST_WIDTH; x++)
			{
				uint8_t red = (uint16_t)_chest.leds[x][y].r * _chest.brightness / 255;
				uint8_t green = (uint16_t)_chest.leds[x][y].g * _chest.brightness / 255;
				uint8_t blue = (uint16_t)_chest.leds[x][y].b * _chest.brightness / 255;

				uint16_t localIndex = 0;
				if (y % 2) // Uneven row
				{
					localIndex = (CHEST_WIDTH * (CHEST_HEIGHT - 1 - y)) + (x);
				}
				else // Even row
				{
					localIndex = (CHEST_WIDTH * (CHEST_HEIGHT - 1 - y)) + (CHEST_WIDTH - 1 - x);
				}
				ws2812_setLedsRGB(CHEST_CHANNEL, CHEST_START + localIndex, 1, red, green, blue); // Set LED color
			}
		}
	}
	else
	{
		ws2812_switchLedsOff(CHEST_CHANNEL, CHEST_START, CHEST_HEIGHT * CHEST_WIDTH);  // switch chest LEDs off
	}
}


// Initializes the LED suit with all LEDs switched off (all LEDs are enabled with color (0, 0, 0))
void ledSuit_init(void)
{
	// Initialize WS2811 library
	ws2812_init();

	// Initialize suit
	ledSuit_enable(WHOLE_SUIT, 1, 0); // Enable all body parts, do not update the LED strips
	ledSuit_color(WHOLE_SUIT, 0, 0, black, 0); // Initialize all body parts with color (0, 0, 0), do not update the LED strips
	ledSuit_setBrightness(WHOLE_SUIT, 50, 0); // Initialize the brightness of all body parts with 50
	// Initialize strobe
	ledSuit_enableStrobe(WHOLE_SUIT, 0); // Initialize all body parts with strobe switched off
	_strobePeriod = 20; // Initialize strobe period
	// Initialize auto rotate
	ledSuit_enableAutoRotate(WHOLE_SUIT, 0); // Initialize all body parts with auto rotate switched off
	ledSuit_configureAutoRotate(WHOLE_SUIT, forwards, 150); // Initialize auto rotate
	// Initialize auto color fade
	ledSuit_enableAutoColorFade(WHOLE_SUIT, 0); // Initialize all body parts with auto color fade switched off
	ledSuit_configureAutoColorFade(WHOLE_SUIT, 1, &_colorLut[black], 150); // Initialize auto color fade

	// Initialize timer for automatic coloring functions
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // Enable clock for timer
	TIM_TimeBaseInitTypeDef  timerInitStructure;
	TIM_TimeBaseStructInit(&timerInitStructure); // Initialize timer initialization structure with default values
	timerInitStructure.TIM_Period = SystemCoreClock / 50 - 1;  // Timer period 20ms
	TIM_TimeBaseInit(TIM2, &timerInitStructure); // Initialize timer
	// Initialize timer interrupt
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; // Timer 2 interrupt
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10; // Low priority
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 10; // Low priority
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // Enable interrupt
	NVIC_Init(&NVIC_InitStructure); // Initialize timer interrupt
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // Clear interrupt flag
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // Enable timer update interrupt

	// Start timer for automatic coloring functions
	TIM_Cmd(TIM2, ENABLE);
}

/******************************************************************************
 * 																			  *
 *		Manual suit coloring functions:										  *
 * 																			  *
 ******************************************************************************/

// Writes the configuration of a body part to the LED strip
void ledSuit_update(uint8_t bodyPart)
{
	if (bodyPart & LEFT_ARM) _updateLeftArm(); // Write the configuration in the _leftArm structure to the LED strip
	if (bodyPart & RIGHT_ARM) _updateRightArm(); // Write the configuration in the _rightArm structure to the LED strip
	if (bodyPart & LEFT_LEG) _updateLeftLeg(); // Write the configuration in the _leftLeg structure to the LED strip
	if (bodyPart & RIGHT_LEG) _updateRightLeg(); // Write the configuration in the _rightLeg structure to the LED strip
	if (bodyPart & CHEST) _updateChest(); // Write the configuration in the _chest structure to the LED strip
}

// Enables (enabled != 0) or disables (enabled == 0) the LEDs of a body part
void ledSuit_enable(uint8_t bodyPart, uint8_t enabled, uint8_t update)
{
	if (bodyPart & LEFT_ARM) _leftArm.enabled = enabled; // Update the enabled value in the _leftArm structure
	if (bodyPart & RIGHT_ARM) _rightArm.enabled = enabled; // Update the enabled value in the _rightArm structure
	if (bodyPart & LEFT_LEG) _leftLeg.enabled = enabled; // Update the enabled value in the _leftLeg structure
	if (bodyPart & RIGHT_LEG) _rightLeg.enabled = enabled; // Update the enabled value in the _rightLeg structure
	if (bodyPart & CHEST) _chest.enabled = enabled; // Update the enabled value in the _chest structure

	if (update) ledSuit_update(bodyPart); // Write the configuration of the body part to the LED strip
}

// Returns the enabled state of the body part (for multiple body parts, the first in the list above is selected)
uint8_t ledSuit_getEnabled(uint8_t bodyPart)
{
	if (bodyPart & LEFT_ARM) return _leftArm.enabled;
	if (bodyPart & RIGHT_ARM) return _rightArm.enabled;
	if (bodyPart & LEFT_LEG) return _leftLeg.enabled;
	if (bodyPart & RIGHT_LEG) return _rightLeg.enabled;
	if (bodyPart & CHEST) return _chest.enabled;
	return 0; // Body part doesn't exist
}

// Sets the brightness of a body part
void ledSuit_setBrightness(uint8_t bodyPart, uint8_t brightness, uint8_t update)
{
	if (bodyPart & LEFT_ARM) _leftArm.brightness = brightness; // Update the brightness value in the _leftArm structure
	if (bodyPart & RIGHT_ARM) _rightArm.brightness = brightness; // Update the brightness value in the _rightArm structure
	if (bodyPart & LEFT_LEG) _leftLeg.brightness = brightness; // Update the brightness value in the _leftLeg structure
	if (bodyPart & RIGHT_LEG) _rightLeg.brightness = brightness; // Update the brightness value in the _rightLeg structure
	if (bodyPart & CHEST) _chest.brightness = brightness; // Update the brightness value in the _chest structure

	if (update) ledSuit_update(bodyPart); // Write the configuration of the body part to the LED strip
}

// Returns the brightness of the body part
uint8_t ledSuit_getBrightness(uint8_t bodyPart)
{
	if (bodyPart & LEFT_ARM) return _leftArm.brightness;
	if (bodyPart & RIGHT_ARM) return _rightArm.brightness;
	if (bodyPart & LEFT_LEG) return _leftLeg.brightness;
	if (bodyPart & RIGHT_LEG) return _rightLeg.brightness;
	if (bodyPart & CHEST) return _chest.brightness;
	return 0; // Body part doesn't exist
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

// Colors rows of the chest with an RGB value
void _colorChestArrayRGB(uint16_t length, uint16_t startIndex, uint8_t red, uint8_t green, uint8_t blue)
{
	// Update the color values in the array
	for (uint16_t i = 0; i < length; i++)
	{
		for (uint8_t x = 0; x < CHEST_WIDTH; x++)
		{
			_chest.leds[x][i + startIndex].r = red;
			_chest.leds[x][i + startIndex].g = green;
			_chest.leds[x][i + startIndex].b = blue;
		}
	}
}

// Colors a number of LEDs with an RGB value (ledCount == 0 colors the whole body part)
void ledSuit_colorRgb(uint8_t bodyPart, uint16_t startIndex, uint16_t ledCount, uint8_t red, uint8_t green, uint8_t blue, uint8_t update)
{
	if (ledCount)
	{
		if (bodyPart & LEFT_ARM) _colorArrayRGB(ledCount, &_leftArm.leds[startIndex], red, green, blue); // Update the color values in the _leftArm structure
		if (bodyPart & RIGHT_ARM) _colorArrayRGB(ledCount, &_rightArm.leds[startIndex], red, green, blue); // Update the color values in the _rightArm structure
		if (bodyPart & LEFT_LEG) _colorArrayRGB(ledCount, &_leftLeg.leds[startIndex], red, green, blue); // Update the color values in the _leftLeg structure
		if (bodyPart & RIGHT_LEG) _colorArrayRGB(ledCount, &_rightLeg.leds[startIndex], red, green, blue); // Update the color values in the _rightLeg structure
		if (bodyPart & CHEST) _colorChestArrayRGB(ledCount, startIndex, red, green, blue); // Update the color values in the _chest structure
	}
	else // Color the whole body part
	{
		if (bodyPart & LEFT_ARM) _colorArrayRGB(LEFT_ARM_LENGTH, _leftArm.leds, red, green, blue); // Update the color values in the _leftArm structure
		if (bodyPart & RIGHT_ARM) _colorArrayRGB(RIGHT_ARM_LENGTH, _rightArm.leds, red, green, blue); // Update the color values in the _rightArm structure
		if (bodyPart & LEFT_LEG) _colorArrayRGB(LEFT_LEG_LENGTH, _leftLeg.leds, red, green, blue); // Update the color values in the _leftLeg structure
		if (bodyPart & RIGHT_LEG) _colorArrayRGB(RIGHT_LEG_LENGTH, _rightLeg.leds, red, green, blue); // Update the color values in the _rightLeg structure
		if (bodyPart & CHEST) _colorChestArrayRGB(CHEST_HEIGHT, 0, red, green, blue); // Update the color values in the _chest structure
	}

	if (update) ledSuit_update(bodyPart); // Write the configuration of the body part to the LED strip
}

// Colors a number of LEDs with a color (ledCount == 0 colors the whole body part)
void ledSuit_color(uint8_t bodyPart, uint16_t startIndex, uint16_t ledCount, ledColor color, uint8_t update)
{
	ledSuit_colorRgb(bodyPart, startIndex, ledCount, _colorLut[color].r, _colorLut[color].g, _colorLut[color].b, update);
}

// Colors a number of LEDs with an rgbLed value (ledCount == 0 colors the whole body part)
void ledSut_colorRgbLed(uint8_t bodyPart, uint16_t startIndex, uint16_t ledCount, rgbLed rgb, uint8_t update)
{
	ledSuit_colorRgb(bodyPart, startIndex, ledCount, rgb.r, rgb.g, rgb.b, update);
}

// Colors a number of LEDs with the values of an LED array
void ledSut_colorArray(uint8_t bodyPart, uint16_t startIndex, uint16_t ledCount, rgbLed * leds, uint8_t update)
{
	// Color each LED individually
	for (uint16_t i = 0; i < ledCount; i++)
	{
		ledSut_colorRgbLed(bodyPart, startIndex + i, 1, leds[i], update);
	}

	if (update) ledSuit_update(bodyPart); // Write the configuration of the body part to the LED strip
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
void ledSuit_colorFade(uint8_t bodyPart, uint8_t colorCount, rgbLed * colors, uint8_t update)
{
	if (bodyPart & LEFT_ARM) _colorLedArrayPartMultipleColorFade(LEFT_ARM_LENGTH, _leftArm.leds, colorCount, colors); // Update the color values in the _leftArm structure
	if (bodyPart & RIGHT_ARM) _colorLedArrayPartMultipleColorFade(RIGHT_ARM_LENGTH, _rightArm.leds, colorCount, colors); // Update the color values in the _rightArm structure
	if (bodyPart & LEFT_LEG) _colorLedArrayPartMultipleColorFade(LEFT_LEG_LENGTH, _leftLeg.leds, colorCount, colors); // Update the color values in the _leftLeg structure
	if (bodyPart & RIGHT_LEG) _colorLedArrayPartMultipleColorFade(RIGHT_LEG_LENGTH, _rightLeg.leds, colorCount, colors); // Update the color values in the _rightLeg structure
	if (bodyPart & CHEST)
	{
		for (uint8_t i = 0; i < CHEST_WIDTH; i++) // Loop through all rows
		{
			_colorLedArrayPartMultipleColorFade(CHEST_HEIGHT, &_chest.leds[i][0], colorCount, colors); // Update the color values for a row in the _chest structure
		}
	}

	if (update) ledSuit_update(bodyPart); // Write the configuration of the body part to the LED strip
}

// Colors a pixel of the chest display with an RGB value
void ledSuit_colorChestPixelRgb(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue, uint8_t update)
{
	_chest.leds[x][y].r = red;
	_chest.leds[x][y].g = green;
	_chest.leds[x][y].b = blue;

	if (update) _updateChest(); // Write the configuration in the _chest structure to the LED strip
}

// Displays a spectrum on the chest
void ledSuit_displaySpectrum(uint8_t * spectrum, uint8_t update)
{
	for (uint8_t x = 0; x < CHEST_WIDTH; x++)
	{
		for (uint8_t y = 0; y < CHEST_HEIGHT; y++)
		{
			if (spectrum[x] > (250 / CHEST_HEIGHT) * (CHEST_HEIGHT - y))
			{
				ledSuit_colorChestPixelRgb(x, y, spectrum[x], spectrum[x], 255 - spectrum[x], update);
			}
			else
			{
				ledSuit_colorChestPixelRgb(x, y, 0, 0, 0, update);
			}
		}
	}
}

// Shifts (rotate == 0) or rotates (rotate != 0) an array (For a shift operation shiftColor is used as new first/last led color)
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

// Rotates the colors of a body part in the given direction
void ledSuit_Rotate(uint8_t bodyPart, direction direction, uint8_t update)
{
	if (bodyPart & LEFT_ARM) _shiftRotateLedArray(LEFT_ARM_LENGTH, _leftArm.leds, direction, 1, _colorLut[black]); // Update the color values in the _leftArm structure
	if (bodyPart & RIGHT_ARM) _shiftRotateLedArray(RIGHT_ARM_LENGTH, _rightArm.leds, direction, 1, _colorLut[black]); // Update the color values in the _rightArm structure
	if (bodyPart & LEFT_LEG) _shiftRotateLedArray(LEFT_LEG_LENGTH, _leftLeg.leds, direction, 1, _colorLut[black]); // Update the color values in the _leftLeg structure
	if (bodyPart & RIGHT_LEG) _shiftRotateLedArray(RIGHT_LEG_LENGTH, _rightLeg.leds, direction, 1, _colorLut[black]); // Update the color values in the _rightLeg structure
	if (bodyPart & CHEST)
	{
		for (uint8_t i = 0; i < CHEST_WIDTH; i++) // Loop through all rows
		{
			_shiftRotateLedArray(CHEST_HEIGHT, &_chest.leds[i][0], direction, 1, _colorLut[black]); // Update the color values for a row in the _chest structure
		}
	}

	if (update) ledSuit_update(bodyPart); // Write the configuration of the body part to the LED strip
}

// Shifts the colors of a body part in the given direction, shiftColor is the new color of the first/last LED
void ledSuit_Shift(uint8_t bodyPart, direction direction, rgbLed shiftColor, uint8_t update)
{
	if (bodyPart & LEFT_ARM) _shiftRotateLedArray(LEFT_ARM_LENGTH, _leftArm.leds, direction, 0, shiftColor); // Update the color values in the _leftArm structure
	if (bodyPart & RIGHT_ARM) _shiftRotateLedArray(RIGHT_ARM_LENGTH, _rightArm.leds, direction, 0, shiftColor); // Update the color values in the _rightArm structure
	if (bodyPart & LEFT_LEG) _shiftRotateLedArray(LEFT_LEG_LENGTH, _leftLeg.leds, direction, 0, shiftColor); // Update the color values in the _leftLeg structure
	if (bodyPart & RIGHT_LEG) _shiftRotateLedArray(RIGHT_LEG_LENGTH, _rightLeg.leds, direction, 0, shiftColor); // Update the color values in the _rightLeg structure
	if (bodyPart & CHEST)
	{
		for (uint8_t i = 0; i < CHEST_WIDTH; i++) // Loop through all rows
		{
			_shiftRotateLedArray(CHEST_HEIGHT, &_chest.leds[i][0], direction, 0, shiftColor); // Update the color values for a row in the _chest structure
		}
	}

	if (update) ledSuit_update(bodyPart); // Write the configuration of the body part to the LED strip
}

/******************************************************************************
 * 																			  *
 *		Automatic suit coloring functions:									  *
 * 																			  *
 ******************************************************************************/

// Enables (enabled != 0) or disables (enabled == 0) the strobe function of a body part
void ledSuit_enableStrobe(uint8_t bodyPart, uint8_t enabled)
{
	if (bodyPart & LEFT_ARM) _leftArm.strobeEnabled = enabled; // Update the strobe enabled value in the _leftArm structure
	if (bodyPart & RIGHT_ARM) _rightArm.strobeEnabled = enabled; // Update the strobe enabled value in the _rightArm structure
	if (bodyPart & LEFT_LEG) _leftLeg.strobeEnabled = enabled; // Update the strobe enabled value in the _leftLeg structure
	if (bodyPart & RIGHT_LEG) _rightLeg.strobeEnabled = enabled; // Update the strobe enabled value in the _rightLeg structure
	if (bodyPart & CHEST) _chest.strobeEnabled = enabled; // Update the strobe enabled value in the _chest structure
}

// Returns the enabled state (enabled != 0) of the body parts strobe function (for multiple body parts, the first in the list above is selected)
uint8_t ledSuit_getStrobeEnabledState(uint8_t bodyPart)
{
	if (bodyPart & LEFT_ARM) return _leftArm.strobeEnabled;
	if (bodyPart & RIGHT_ARM) return _rightArm.strobeEnabled;
	if (bodyPart & LEFT_LEG) return _leftLeg.strobeEnabled;
	if (bodyPart & RIGHT_LEG) return _rightLeg.strobeEnabled;
	if (bodyPart & CHEST) return _chest.strobeEnabled;
	return 0; // Body part doesn't exist
}

// Sets the strobe period in 20ms steps (starting with 0)
void ledSuit_setStrobePeriod(uint8_t time)
{
	_strobePeriod = time;
}

// Enables (enabled != 0) or disables (enabled == 0) the auto rotate function of a body part
void ledSuit_enableAutoRotate(uint8_t bodyPart, uint8_t enabled)
{
	if (bodyPart & LEFT_ARM) _leftArm.autoRotateState.enabled = enabled; // Update the auto rotate enabled value in the _leftArm structure
	if (bodyPart & RIGHT_ARM) _rightArm.autoRotateState.enabled = enabled; // Update the auto rotate enabled value in the _rightArm structure
	if (bodyPart & LEFT_LEG) _leftLeg.autoRotateState.enabled = enabled; // Update the auto rotate enabled value in the _leftLeg structure
	if (bodyPart & RIGHT_LEG) _rightLeg.autoRotateState.enabled = enabled; // Update the auto rotate enabled value in the _rightLeg structure
	if (bodyPart & CHEST) _chest.autoRotateState.enabled = enabled; // Update the auto rotate enabled value in the _chest structure
}

// Returns the enabled state (enabled != 0) of the body parts auto rotate function (for multiple body parts, the first in the list above is selected)
uint8_t ledSuit_getAutoRotateEnabledState(uint8_t bodyPart)
{
	if (bodyPart & LEFT_ARM) return _leftArm.autoRotateState.enabled;
	if (bodyPart & RIGHT_ARM) return _rightArm.autoRotateState.enabled;
	if (bodyPart & LEFT_LEG) return _leftLeg.autoRotateState.enabled;
	if (bodyPart & RIGHT_LEG) return _rightLeg.autoRotateState.enabled;
	if (bodyPart & CHEST) return _chest.autoRotateState.enabled;
	return 0; // Body part doesn't exist
}

// Configures the auto rotate function of a body part
void ledSuit_configureAutoRotate(uint8_t bodyPart, direction direction, uint8_t speed)
{
	if (bodyPart & LEFT_ARM)
	{
		_leftArm.autoRotateState.direction = direction; // Update the auto rotate direction value in the _leftArm structure
		_leftArm.autoRotateState.speed = speed; // Update the auto rotate speed value in the _leftArm structure
	}
	if (bodyPart & RIGHT_ARM)
	{
		_rightArm.autoRotateState.direction = direction; // Update the auto rotate direction value in the _rightArm structure
		_rightArm.autoRotateState.speed = speed; // Update the auto rotate speed value in the _rightArm structure
	}
	if (bodyPart & LEFT_LEG)
	{
		_leftLeg.autoRotateState.direction = direction; // Update the auto rotate direction value in the _leftLeg structure
		_leftLeg.autoRotateState.speed = speed; // Update the auto rotate speed value in the _leftLeg structure
	}
	if (bodyPart & RIGHT_LEG)
	{
		_rightLeg.autoRotateState.direction = direction; // Update the auto rotate direction value in the _rightLeg structure
		_rightLeg.autoRotateState.speed = speed; // Update the auto rotate speed value in the _rightLeg structure
	}
	if (bodyPart & CHEST)
	{
		_chest.autoRotateState.direction = direction; // Update the auto rotate direction value in the _chest structure
		_chest.autoRotateState.speed = speed; // Update the auto rotate speed value in the _chest structure
	}
}

// Enables ((enabled != 0) or disables (enabled == 0) the auto color fade function of a body part
void ledSuit_enableAutoColorFade(uint8_t bodyPart, uint8_t enabled)
{
	if (bodyPart & LEFT_ARM) _leftArm.autoColorFadeState.enabled = enabled; // Update the auto color fade enabled value in the _leftArm structure
	if (bodyPart & RIGHT_ARM) _rightArm.autoColorFadeState.enabled = enabled; // Update the auto color fade enabled value in the _rightArm structure
	if (bodyPart & LEFT_LEG) _leftLeg.autoColorFadeState.enabled = enabled; // Update the auto color fade enabled value in the _leftLeg structure
	if (bodyPart & RIGHT_LEG) _rightLeg.autoColorFadeState.enabled = enabled; // Update the auto color fade enabled value in the _rightLeg structure
	if (bodyPart & CHEST) _chest.autoColorFadeState.enabled = enabled; // Update the auto color fade enabled value in the _chest structure
}

// Returns the enabled state (enabled != 0) of the body parts auto color fade function (for multiple body parts, the first in the list above is selected)
uint8_t ledSuit_getAutoColorFadeEnabledState(uint8_t bodyPart)
{
	if (bodyPart & LEFT_ARM) return _leftArm.autoColorFadeState.enabled;
	if (bodyPart & RIGHT_ARM) return _rightArm.autoColorFadeState.enabled;
	if (bodyPart & LEFT_LEG) return _leftLeg.autoColorFadeState.enabled;
	if (bodyPart & RIGHT_LEG) return _rightLeg.autoColorFadeState.enabled;
	if (bodyPart & CHEST) return _chest.autoColorFadeState.enabled;
	return 0; // Body part doesn't exist
}

// Sets the auto color fade colors of a auto color fade structure
void _setAutoColorFadeStructureColorValues(autoColorFadeStruct * structurePointer, uint8_t colorCount, rgbLed * colors)
{
	// Set color count
	structurePointer->colorCount = colorCount;
	// Set individual color values
	for (uint8_t i = 0; i < colorCount; i++)
	{
		structurePointer->colors[i]=colors[i];
	}
}

// Configures the auto color fade function of a body part
void ledSuit_configureAutoColorFade(uint8_t bodyPart, uint8_t colorCount, rgbLed * colors, uint8_t speed)
{
	if (bodyPart & LEFT_ARM)
	{
		_setAutoColorFadeStructureColorValues(&_leftArm.autoColorFadeState, colorCount, colors); // Update the auto color fade colors in the _leftArm structure
		_leftArm.autoColorFadeState.speed = speed; // Update the auto color fade speed value in the _leftArm structure
	}
	if (bodyPart & RIGHT_ARM)
	{
		_setAutoColorFadeStructureColorValues(&_rightArm.autoColorFadeState, colorCount, colors); // Update the auto color fade colors in the _rightArm structure
		_rightArm.autoColorFadeState.speed = speed; // Update the auto color fade speed value in the _rightArm structure
	}
	if (bodyPart & LEFT_LEG)
	{
		_setAutoColorFadeStructureColorValues(&_leftLeg.autoColorFadeState, colorCount, colors); // Update the auto color fade colors in the _leftLeg structure
		_leftLeg.autoColorFadeState.speed = speed; // Update the auto color fade speed value in the _leftLeg structure
	}
	if (bodyPart & RIGHT_LEG)
	{
		_setAutoColorFadeStructureColorValues(&_rightLeg.autoColorFadeState, colorCount, colors); // Update the auto color fade colors in the _rightLeg structure
		_rightLeg.autoColorFadeState.speed = speed; // Update the auto color fade speed value in the _rightLeg structure
	}
	if (bodyPart & CHEST)
	{
		_setAutoColorFadeStructureColorValues(&_chest.autoColorFadeState, colorCount, colors); // Update the auto color fade colors in the _chest structure
		_chest.autoColorFadeState.speed = speed; // Update the auto color fade speed value in the _chest structure
	}
}

// Synchronizes the auto color fade functions of all body parts (for a synchronous operation, all body parts have to be configured with the same speed)
void ledSuit_synchronizeAutoColorFade()
{
	_autoColorFadeSyncFlag = 1;
}


#define BODY_PART_COUNT 5 // Total number of body parts (used for looping through all body parts)

// Returns the body part corresponding to an index (used for looping through all body parts)
uint8_t _indexToBodyPart(uint8_t index)
{
	switch (index)
	{
	case 0: return LEFT_ARM;
	case 1: return RIGHT_ARM;
	case 2: return LEFT_LEG;
	case 3: return RIGHT_LEG;
	case 4: return CHEST;
	default: return 0; // body part doesn't exist
	}
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
		if (_leftArm.strobeEnabled) ledSuit_enable(LEFT_ARM, !ledSuit_getEnabled(LEFT_ARM), 1);
		if (_rightArm.strobeEnabled) ledSuit_enable(RIGHT_ARM, !ledSuit_getEnabled(RIGHT_ARM), 1);
		if (_leftLeg.strobeEnabled) ledSuit_enable(LEFT_LEG, !ledSuit_getEnabled(LEFT_LEG), 1);
		if (_rightLeg.strobeEnabled) ledSuit_enable(RIGHT_LEG, !ledSuit_getEnabled(RIGHT_LEG), 1);
		if (_chest.strobeEnabled) ledSuit_enable(CHEST, !ledSuit_getEnabled(CHEST), 1);

		strobeCounter = 0; // Reset strobe counter
	}
}

// Returns the auto rotate structure of the body part
autoRotateStruct _getAutoRotateStruct(uint8_t bodyPart)
{
	// Return body part auto rotate enabled value
	switch (bodyPart)
	{
	default: // body part doesn't exist
	case LEFT_ARM: return _leftArm.autoRotateState;
	case RIGHT_ARM: return _rightArm.autoRotateState;
	case LEFT_LEG: return _leftLeg.autoRotateState;
	case RIGHT_LEG: return _rightLeg.autoRotateState;
	case CHEST: return _chest.autoRotateState;
	}
}

// Executes all auto rotate actions
void _autoRotate()
{
	static uint8_t autoRotateCounter[BODY_PART_COUNT] = {255};

	for (uint8_t i = 0; i < BODY_PART_COUNT; i++)
	{
		autoRotateStruct bodyPartAutoRotateStruct = _getAutoRotateStruct(_indexToBodyPart(i)); // Auto rotate structure of the current body part

		if (bodyPartAutoRotateStruct.enabled) // Auto rotate enabled
		{
			if (autoRotateCounter[i] > bodyPartAutoRotateStruct.speed)
			{
				autoRotateCounter[i]--; // Decrement auto rotate counter
			}
			else
			{
				ledSuit_Rotate(_indexToBodyPart(i), bodyPartAutoRotateStruct.direction, 1); // Rotate body part
				autoRotateCounter[i] = 255; // Reset auto rotate counter
			}
		}
	}
}

// Returns the auto color fade structure of the body part
autoColorFadeStruct _getBodyPartAutoColorFadeStruct(uint8_t bodyPart)
{
	// Return body part auto color fade structure
	switch (bodyPart)
	{
	default: // body part doesn't exist
	case LEFT_ARM: return _leftArm.autoColorFadeState;
	case RIGHT_ARM: return _rightArm.autoColorFadeState;
	case LEFT_LEG: return _leftLeg.autoColorFadeState;
	case RIGHT_LEG: return _rightLeg.autoColorFadeState;
	case CHEST: return _chest.autoColorFadeState;
	}
}

// Executes an auto color fade step of the body part
void _autoColorFadeStep(uint8_t bodyPartIndex)
{
	autoColorFadeStruct bodyPartAutoColorFadeStruct = _getBodyPartAutoColorFadeStruct(_indexToBodyPart(bodyPartIndex)); // Auto color fade structure of the current body part

	static uint8_t colorFadeColorCounter[BODY_PART_COUNT] = {0};
	static uint8_t colorFadeCounter[BODY_PART_COUNT] = {0};

	if(_autoColorFadeSyncFlag) // Auto color fade has to be synchronized
	{
		// Reset all auto color fade counters
		for (uint8_t i = 0; i < BODY_PART_COUNT; i++)
		{
			colorFadeColorCounter[i] = 0;
			colorFadeCounter[i] = 0;
		}

		_autoColorFadeSyncFlag = 0; // Reset auto color fade sync flag
	}

	rgbLed currentColor, nextColor;

	currentColor = bodyPartAutoColorFadeStruct.colors[colorFadeColorCounter[bodyPartIndex]];

	if (colorFadeColorCounter[bodyPartIndex] < (bodyPartAutoColorFadeStruct.colorCount - 1))
	{
		nextColor = bodyPartAutoColorFadeStruct.colors[colorFadeColorCounter[bodyPartIndex] + 1]; // Fade to next color
	}
	else // Last color reached
	{
		nextColor = bodyPartAutoColorFadeStruct.colors[0]; // Fade back to first color
	}

	// Calculate a weighted average of the colors
	uint8_t red = (currentColor.r * (255 - colorFadeCounter[bodyPartIndex]) / 255)
			+ (nextColor.r * colorFadeCounter[bodyPartIndex] / 255);
	uint8_t green = (currentColor.g * (255 - colorFadeCounter[bodyPartIndex]) / 255)
			+ (nextColor.g * colorFadeCounter[bodyPartIndex] / 255);
	uint8_t blue = (currentColor.b * (255 - colorFadeCounter[bodyPartIndex]) / 255)
			+ (nextColor.b * colorFadeCounter[bodyPartIndex] / 255);

	ledSuit_colorRgb(_indexToBodyPart(bodyPartIndex), 0, 0, red, green, blue, 1); // Update body part color

	if (colorFadeCounter[bodyPartIndex] < 254)
	{
		colorFadeCounter[bodyPartIndex]++; // Increment color fade counter
	}
	else
	{
		if (colorFadeColorCounter[bodyPartIndex] < (bodyPartAutoColorFadeStruct.colorCount - 1))
		{
			colorFadeColorCounter[bodyPartIndex]++; // Increment color fade color counter
		}
		else
		{
			colorFadeColorCounter[bodyPartIndex] = 0; // Reset color fade color counter
		}
		colorFadeCounter[bodyPartIndex] = 0; // Reset color fade counter
	}
}

// Executes all auto color fade actions
void _autoColorFade()
{
	static uint8_t autoColorFadeCounter[BODY_PART_COUNT] = {255};

	for (uint8_t i = 0; i < BODY_PART_COUNT; i++)
	{
		autoColorFadeStruct bodyPartAutoColorFadeStruct = _getBodyPartAutoColorFadeStruct(_indexToBodyPart(i)); // Auto color fade structure of the current body part

		if(bodyPartAutoColorFadeStruct.enabled) // Auto color fade enabled
		{
			if (autoColorFadeCounter[i] > bodyPartAutoColorFadeStruct.speed)
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

// Timer 2 interrupt handler
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update)) // Timer update interrupt
  {
	_strobe();
	_autoRotate();
	_autoColorFade();
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // Clear interrupt flag
  }
}
