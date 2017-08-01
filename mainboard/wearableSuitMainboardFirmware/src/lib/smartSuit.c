/*
 * smartSuit.c
 *
 *  Created on: 01.08.2017
 *      Author: kekse
 */

#include "smartSuit.h"

#include "ledSuit.h"
#include "rs485.h"
#include "mic.h"
#include "simonSays.h"

// Initializes the smart dancing suit
void smartSuit_init(void)
{
	mic_init();
	ledSuit_init();
	rs485_init(57600);
}

// Arms and legs are enabled if they are moving (if strobe is != 0, they will use strobe)
void smartSuit_enableMoving(uint8_t strobe)
{
	// Get current IMU sensor data
	uint8_t leftArmMoving = rs485_getMoving(leftArmSensor);
	uint8_t rightArmMoving = rs485_getMoving(rightArmSensor);
	uint8_t leftLegMoving = rs485_getMoving(leftLegSensor);
	uint8_t rightLegMoving = rs485_getMoving(rightLegSensor);

	if (strobe)
	{
		// Enable strobe for moving body parts
		ledSuit_enableStrobe(LEFT_ARM, leftArmMoving);
		ledSuit_enableStrobe(RIGHT_ARM, rightArmMoving);
		ledSuit_enableStrobe(LEFT_LEG, leftLegMoving);
		ledSuit_enableStrobe(RIGHT_LEG, rightLegMoving);
		// Switch off not moving body parts
		if (!leftArmMoving) ledSuit_enable(LEFT_ARM, 0, 1);
		if (!rightArmMoving) ledSuit_enable(RIGHT_ARM, 0, 1);
		if (!leftLegMoving) ledSuit_enable(LEFT_LEG, 0, 1);
		if (!rightLegMoving) ledSuit_enable(RIGHT_LEG, 0, 1);
	}
	else
	{
		ledSuit_enableStrobe(WHOLE_SUIT & ~CHEST, 0); // Disable strobe for arms and legs
		// Enable moving body parts
		ledSuit_enable(LEFT_ARM, leftArmMoving, 1);
		ledSuit_enable(RIGHT_ARM, rightArmMoving, 1);
		ledSuit_enable(LEFT_LEG, leftLegMoving, 1);
		ledSuit_enable(RIGHT_LEG, rightLegMoving, 1);
	}
}

// Sets the body part brightness according to the music sound level
void smartSuit_setMusicBrightness(uint8_t bodyPart)
{
	// Get current audio level and scale it to a suitable brightness value
	uint16_t audioLevel = mic_getAudioLevel() / 100;
	if (audioLevel < 10) audioLevel = 0;
	else audioLevel -= 10;
	// Set body part brightness
	ledSuit_setBrightness(bodyPart, audioLevel, 1);
}

// Displays the current music spectrum on the chest
void smartSuit_displayMusicSpectrum()
{
	uint8_t spectrum[10];
	mic_getSpectrum(spectrum, 230); // Get current music spectrum
	ledSuit_displaySpectrum(spectrum, 1); // Display spectrum
}

// Colors the chest with a smiley
void _colorChestSmiley()
{
	ledSuit_color(CHEST, 0, 0, yellow, 0);
	ledSuit_colorChestPixelRgb(0, 0, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(0, 1, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(0, 2, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(0, 7, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(0, 8, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(0, 9, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(1, 0, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(1, 9, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(2, 0, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(2, 9, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(7, 0, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(7, 9, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(8, 0, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(8, 9, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(9, 0, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(9, 1, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(9, 2, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(9, 7, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(9, 8, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(9, 9, 0, 0, 0, 0);
	ledSuit_colorChestPixelRgb(3, 2, 255, 255, 255, 0);
	ledSuit_colorChestPixelRgb(6, 2, 255, 255, 255, 0);
	ledSuit_colorChestPixelRgb(3, 3, 255, 255, 255, 0);
	ledSuit_colorChestPixelRgb(6, 3, 255, 255, 255, 0);
	ledSuit_colorChestPixelRgb(2, 6, 255, 255, 255, 0);
	ledSuit_colorChestPixelRgb(7, 6, 255, 255, 255, 0);
	ledSuit_colorChestPixelRgb(3, 7, 255, 255, 255, 0);
	ledSuit_colorChestPixelRgb(4, 7, 255, 255, 255, 0);
	ledSuit_colorChestPixelRgb(5, 7, 255, 255, 255, 0);
	ledSuit_colorChestPixelRgb(6, 7, 255, 255, 255, 0);
	ledSuit_update(CHEST);
}

// Runs a demo from the list above (this function does not return)
void smartSuit_demo(int demoNumber)
{
	rgbLed rgbFadeColors[4] = {
				{ .r = 255, .g = 0, .b = 0 },
				{ .r = 0, .g = 255, .b = 0 },
				{ .r = 0, .g = 0, .b = 255 },
				{ .r = 255, .g = 0, .b = 0 } };

	rgbLed pulseColors[5] = {
			{ .r = 20, .g = 0, .b = 0 },
			{ .r = 90, .g = 0, .b = 0 },
			{ .r = 255, .g = 0, .b = 0 },
			{ .r = 90, .g = 0, .b = 0 },
			{ .r = 20, .g = 0, .b = 0} };

	switch (demoNumber)
	{
		case 1:
			// Color arms and legs in an automatically rotating RGB color fade
			ledSuit_colorFade(WHOLE_SUIT & ~CHEST, 4, rgbFadeColors, 1);
			ledSuit_configureAutoRotate(WHOLE_SUIT & ~CHEST, forwards, 245);
			ledSuit_enableAutoRotate(WHOLE_SUIT & ~CHEST, 1);

			while (1)
			{
				smartSuit_displayMusicSpectrum(); // Display the current music spectrum on the chest
			}
			break;
		case 2:
			// Color the whole suit in an automatically rotating RGB color fade
			ledSuit_colorFade(WHOLE_SUIT, 4, rgbFadeColors, 1);
			ledSuit_configureAutoRotate(WHOLE_SUIT, forwards, 240);
			ledSuit_enableAutoRotate(WHOLE_SUIT, 1);

			while (1)
			{
				smartSuit_setMusicBrightness(WHOLE_SUIT); // Set the whole suits brightness according to the music sound level
				smartSuit_enableMoving(0); // Arms and legs are enabled if they are moving
			}
			break;
		case 3:
			ledSuit_color(WHOLE_SUIT & ~CHEST, 0, 0, white, 1); // Color arms and legs in white

			while (1)
			{
				smartSuit_displayMusicSpectrum(); // Display the current music spectrum on the chest
				smartSuit_enableMoving(1); // Arms and legs strobes are enabled if they are moving
			}
			break;
		case 4:
			// Color whole suit in RGB auto color fade
			ledSuit_configureAutoColorFade (WHOLE_SUIT, 3, rgbFadeColors, 254);
			ledSuit_enableAutoColorFade (WHOLE_SUIT, 1);

			while (1)
			{
				smartSuit_enableMoving(0); // Arms and legs are enabled if they are moving
			}
			break;
		case 5:
			// Color arms and legs with an auto rotating red pulse
			ledSuit_colorArray(WHOLE_SUIT & ~CHEST, 0, 5, pulseColors, 1);
			ledSuit_colorArray(LEFT_ARM | RIGHT_ARM, 15, 5, pulseColors, 1);
			ledSuit_colorArray(LEFT_LEG | RIGHT_LEG, 20, 5, pulseColors, 1);
			ledSuit_configureAutoRotate(WHOLE_SUIT & ~CHEST, forwards, 255);
			ledSuit_enableAutoRotate(WHOLE_SUIT & ~CHEST, 1);

			// Color the chest with a smiley
			_colorChestSmiley();
			while (1);
			break;
		case 6:
			while (1)
			{
				simonSays_play(); // Play Simon says
			}
			break;
		default:
			while (1);
	}
}
