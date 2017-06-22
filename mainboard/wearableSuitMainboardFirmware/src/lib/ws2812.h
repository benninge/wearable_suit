/*
 * ws2812.h
 *
 *  Created on: 22.06.2017
 *      Author: kekse
 */

#ifndef WS2812_H
#define WS2812_H

#include "stm32f4xx.h"


#define LED_COUNT 6 // Number of LEDs


// RGB LED structure
typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} rgbLed;


// Initializes the ws2812 (all LEDs switched off)
void ws2812_init(void);

// Updates a number of LEDs beginning at the start address
void ws2812_updateLeds(uint16_t startAddress, uint16_t ledCount, rgbLed * ledData);

// Sets a number of LEDs to RGB value beginning at the start address
void ws2812_setLedsRGB(uint16_t startAddress, uint16_t ledCount, uint8_t r, uint8_t g, uint8_t b);
// Sets all LEDs to RGB value
void ws2812_setAllLedsRGB(uint8_t r, uint8_t g, uint8_t b);

// Sets a number of LEDs to a color beginning at the start address
void ws2812_setLedsToColor(uint16_t startAddress, uint16_t ledCount, rgbLed color);
// Sets all LEDs to a color
void ws2812_setAllLedsToColor(rgbLed color);

// switches a number of LEDs off beginning at the start address
void ws2812_switchLedsOff(uint16_t startAddress, uint16_t ledCount);
// switches all LEDs off
void ws2812_switchAllLedsOff(uint16_t startAddress, uint16_t ledCount);

#endif /* LIB_WS2812_H_ */
