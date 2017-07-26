/*
 * ws2812.h
 *
 *  Created on: 22.06.2017
 *      Author: kekse
 */

#ifndef WS2812_H
#define WS2812_H

#include "stm32f4xx.h"


#define ENABLE_CHANNEL_1 // Enable ws2812 channel 1 on pin A6
#define ENABLE_CHANNEL_2 // Enable ws2812 channel 2 on pin A7
#define ENABLE_CHANNEL_3 // Enable ws2812 channel 3 on pin B0
#define ENABLE_CHANNEL_4 // Enable ws2812 channel 4 on pin B1

#define LED_COUNT_CH1 41 // Number of LEDs in channel 1
#define LED_COUNT_CH2 41 // Number of LEDs in channel 2
#define LED_COUNT_CH3 32 // Number of LEDs in channel 3
#define LED_COUNT_CH4 132 // Number of LEDs in channel 4


// RGB LED structure
typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} rgbLed;


// Initializes the ws2812 (all LEDs switched off)
void ws2812_init(void);

// Sets a number of LEDs of a channel beginning at the start address
void ws2812_setLeds(uint8_t channel, uint16_t startAddress, uint16_t ledCount, rgbLed * ledData);

// Sets a number of LEDs of a channel to RGB value beginning at the start address
void ws2812_setLedsRGB(uint8_t channel, uint16_t startAddress, uint16_t ledCount, uint8_t r, uint8_t g, uint8_t b);
// Sets all LEDs to RGB value
void ws2812_setAllLedsRGB(uint8_t r, uint8_t g, uint8_t b);

// Sets a number of LEDs of a channel to a color beginning at the start address
void ws2812_setLedsToColor(uint8_t channel, uint16_t startAddress, uint16_t ledCount, rgbLed color);
// Sets all LEDs to a color
void ws2812_setAllLedsToColor(rgbLed color);

// switches a number of LEDs of a channel off beginning at the start address
void ws2812_switchLedsOff(uint8_t channel, uint16_t startAddress, uint16_t ledCount);
// switches all LEDs off
void ws2812_switchAllLedsOff(uint16_t startAddress, uint16_t ledCount);

#endif /* LIB_WS2812_H_ */
