/*
 * ws2812.c
 *
 *  Created on: 22.06.2017
 *      Author: kekse
 */

#include "ws2812.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dma.h"


#define PWM_PERIOD 125 // Length of an PWM period for the serial LED output
#define PWM_0_VALUE 42 // Length of an PWM pulse for a zero value
#define PWM_1_VALUE 83 // Length of an PWM period for a one value

#define RESET_CYCLES 50 // 50 * 1,25us = 62,5us reset pulse (must be at least 50us)
#define DMA_BUFFER_LENGTH (LED_COUNT * 24 + RESET_CYCLES) // Length of the DMA buffer


// Global variables
uint16_t dmaBuffer[DMA_BUFFER_LENGTH]; // Array containing all PWM values


// Initializes the ws2812 (all LEDs switched off)
void ws2812_init(void)
{
	// Initialize dmaBuffer
	for (uint16_t i = 0; i < DMA_BUFFER_LENGTH; i++)
	{
		if (i < LED_COUNT * 24) // LED value
		{
			dmaBuffer[i] = PWM_0_VALUE; // Initialize LEDs with zero values
		}
		else // Reset cycle
		{
			dmaBuffer[i] = 0; // No PWM during reset cycle
		}
	}


	// GPIO initialization
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); // Enable clock for GPIO

	GPIO_InitTypeDef gpioInitStructure;
	GPIO_StructInit (&gpioInitStructure); // Initialize GPIO initialization structure with default values
	gpioInitStructure.GPIO_Pin = GPIO_Pin_0; // Pin 0
	gpioInitStructure.GPIO_Mode = GPIO_Mode_AF; // GPIO in arbitrary function mode
	gpioInitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 100MHz GPIO speed
	GPIO_Init(GPIOB, &gpioInitStructure); // Initialize GPIO

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3); // Arbitrary function select


	// Timer initialization
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // Enable clock for Timer

	TIM_TimeBaseInitTypeDef timerInitStructure;
	TIM_TimeBaseStructInit(&timerInitStructure); // Initialize timer initialization structure with default values
	timerInitStructure.TIM_Period = PWM_PERIOD; // Set timer period to PWM period
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV4; // Set clock divider to /4
	TIM_TimeBaseInit(TIM3, &timerInitStructure); // Initialize timer


	// Output compare initialization
	TIM_OCInitTypeDef outputCompareInitStructure;
	TIM_OCStructInit(&outputCompareInitStructure); // Initialize output compare initialization structure with default values
	outputCompareInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // PWM output compare mode
	outputCompareInitStructure.TIM_OutputState = TIM_OutputState_Enable; // Enable output compare
	TIM_OC3Init(TIM3, &outputCompareInitStructure); // Initialize output compare
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); // Enable timer preload register on capture compare register 3
	TIM_CCxCmd(TIM3, TIM_Channel_3, TIM_CCx_Enable); // Enable timer capture compare channel


	// DMA initialization
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE); // Enable clock for DMA
	DMA_InitTypeDef dmaInitStructure;
	DMA_StructInit(&dmaInitStructure); // Initialize DMA initialization structure with default values
	dmaInitStructure.DMA_Channel = DMA_Channel_5; // Use DMA channel 5
	dmaInitStructure.DMA_PeripheralBaseAddr = (uint32_t) &TIM3->CCR3; // Load data into capture compare register
	dmaInitStructure.DMA_Memory0BaseAddr = (uint32_t) dmaBuffer; // Use DMA buffer as data source
	dmaInitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; // Transfer data from memory to peripheral
	dmaInitStructure.DMA_BufferSize = DMA_BUFFER_LENGTH; // DMA buffer size = length of DMA buffer
	dmaInitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // Auto increment memory address
	dmaInitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 16 bit DMA data size
	dmaInitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; // 16 bit memory data size
	dmaInitStructure.DMA_Mode = DMA_Mode_Circular; // Circular buffer mode
	dmaInitStructure.DMA_Priority = DMA_Priority_High; // High DMA priority
	DMA_Init(DMA1_Stream7, &dmaInitStructure); // Initialize DMA
	DMA_Cmd(DMA1_Stream7, ENABLE); // Enable DMA stream

	TIM_DMACmd(TIM3, TIM_DMA_CC3, ENABLE); // Enable timer DMA request


	TIM_Cmd(TIM3, ENABLE); // Enable timer
}

// Updates a number of LEDs beginning at the start address
void ws2812_updateLeds(uint16_t startAddress, uint16_t ledCount, rgbLed * ledData)
{
	// Update dmaBuffer
	for (uint16_t i = startAddress; i < startAddress + ledCount; i++)
	{
		for (uint8_t j = 0; j < 8; j++)
		{
			dmaBuffer[i * 24 + j + 8] = (ledData->r & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
			dmaBuffer[i * 24 + j] = (ledData->g & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
			dmaBuffer[i * 24 + j + 16] = (ledData->b & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
		}
		ledData++; // Increment LED data pointer
	}
}

// Sets a number of LEDs to RGB value beginning at the start address
void ws2812_setLedsRGB(uint16_t startAddress, uint16_t ledCount, uint8_t r, uint8_t g, uint8_t b)
{
	rgbLed led = {.r = r, .g = g, .b = b};
	for (uint16_t i = startAddress; i < startAddress + ledCount; i++)
	{
		ws2812_updateLeds(i, 1, &led);
	}
}

// Sets all LEDs to RGB value
void ws2812_setAllLedsRGB(uint8_t r, uint8_t g, uint8_t b)
{
	ws2812_setLedsRGB(0, LED_COUNT, r, g, b);
}

// Sets a number of LEDs to a color beginning at the start address
void ws2812_setLedsToColor(uint16_t startAddress, uint16_t ledCount, rgbLed color)
{
	ws2812_setLedsRGB(startAddress, ledCount, color.r, color.g, color.b);
}

// Sets all LEDs to a color
void ws2812_setAllLedsToColor(rgbLed color)
{
	ws2812_setAllLedsRGB(color.r, color.g, color.b);
}

// switches a number of LEDs off beginning at the start address
void ws2812_switchLedsOff(uint16_t startAddress, uint16_t ledCount)
{
	ws2812_setLedsRGB(startAddress, ledCount, 0, 0, 0);
}
// switches all LEDs off
void ws2812_switchAllLedsOff(uint16_t startAddress, uint16_t ledCount)
{
	ws2812_setAllLedsRGB(0, 0, 0);
}
