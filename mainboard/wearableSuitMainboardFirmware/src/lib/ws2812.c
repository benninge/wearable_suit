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
#define DMA_BUFFER1_LENGTH (LED_COUNT_CH1 * 24 + RESET_CYCLES) // Length of the DMA buffer for channel 1
#define DMA_BUFFER2_LENGTH (LED_COUNT_CH2 * 24 + RESET_CYCLES) // Length of the DMA buffer for channel 2
#define DMA_BUFFER3_LENGTH (LED_COUNT_CH3 * 24 + RESET_CYCLES) // Length of the DMA buffer for channel 3
#define DMA_BUFFER4_LENGTH (LED_COUNT_CH4 * 24 + RESET_CYCLES) // Length of the DMA buffer for channel 4


// Global variables
#ifdef ENABLE_CHANNEL_1
uint16_t dmaBuffer1[DMA_BUFFER1_LENGTH]; // Array containing all PWM values of channel 1
#endif
#ifdef ENABLE_CHANNEL_2
uint16_t dmaBuffer2[DMA_BUFFER2_LENGTH]; // Array containing all PWM values of channel 2
#endif
#ifdef ENABLE_CHANNEL_3
uint16_t dmaBuffer3[DMA_BUFFER3_LENGTH]; // Array containing all PWM values of channel 3
#endif
#ifdef ENABLE_CHANNEL_4
uint16_t dmaBuffer4[DMA_BUFFER4_LENGTH]; // Array containing all PWM values of channel 4
#endif


// Initializes the ws2812 (all LEDs switched off)
void ws2812_init(void)
{
#ifdef ENABLE_CHANNEL_1
	// Initialize DMA buffer 1
	for (uint16_t i = 0; i < DMA_BUFFER1_LENGTH; i++)
	{
		if (i < LED_COUNT_CH1 * 24) // LED value
		{
			dmaBuffer1[i] = PWM_0_VALUE; // Initialize LEDs with zero values
		}
		else // Reset cycle
		{
			dmaBuffer1[i] = 0; // No PWM during reset cycle
		}
	}
#endif

#ifdef ENABLE_CHANNEL_2
	// Initialize DMA buffer 2
	for (uint16_t i = 0; i < DMA_BUFFER2_LENGTH; i++)
	{
		if (i < LED_COUNT_CH2 * 24) // LED value
		{
			dmaBuffer2[i] = PWM_0_VALUE; // Initialize LEDs with zero values
		}
		else // Reset cycle
		{
			dmaBuffer2[i] = 0; // No PWM during reset cycle
		}
	}
#endif

#ifdef ENABLE_CHANNEL_3
	// Initialize DMA buffer 3
	for (uint16_t i = 0; i < DMA_BUFFER3_LENGTH; i++)
	{
		if (i < LED_COUNT_CH3 * 24) // LED value
		{
			dmaBuffer3[i] = PWM_0_VALUE; // Initialize LEDs with zero values
		}
		else // Reset cycle
		{
			dmaBuffer3[i] = 0; // No PWM during reset cycle
		}
	}
#endif

#ifdef ENABLE_CHANNEL_4
	// Initialize DMA buffer 4
	for (uint16_t i = 0; i < DMA_BUFFER4_LENGTH; i++)
	{
		if (i < LED_COUNT_CH4 * 24) // LED value
		{
			dmaBuffer4[i] = PWM_0_VALUE; // Initialize LEDs with zero values
		}
		else // Reset cycle
		{
			dmaBuffer4[i] = 0; // No PWM during reset cycle
		}
	}
#endif


	// GPIO initialization
	GPIO_InitTypeDef gpioInitStructure;
	GPIO_StructInit (&gpioInitStructure); // Initialize GPIO initialization structure with default values
	gpioInitStructure.GPIO_Mode = GPIO_Mode_AF; // GPIO in arbitrary function mode
	gpioInitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 100MHz GPIO speed

#ifdef ENABLE_CHANNEL_1
	// Initialize pin A6
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // Enable clock for GPIO A
	gpioInitStructure.GPIO_Pin = GPIO_Pin_6; // Pin 6
	GPIO_Init(GPIOA, &gpioInitStructure); // Initialize GPIO A
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3); // Pin A6 arbitrary function select
#endif

#ifdef ENABLE_CHANNEL_2
	// Initialize pin A7
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // Enable clock for GPIO A
	gpioInitStructure.GPIO_Pin = GPIO_Pin_7; // Pin 7
	GPIO_Init(GPIOA, &gpioInitStructure); // Initialize GPIO A
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3); // Pin A7 arbitrary function select
#endif

#ifdef ENABLE_CHANNEL_3
	// Initialize pin B0
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); // Enable clock for GPIO B
	gpioInitStructure.GPIO_Pin = GPIO_Pin_0; // Pin 0
	GPIO_Init(GPIOB, &gpioInitStructure); // Initialize GPIO B
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3); // Pin B0 arbitrary function select
#endif

#ifdef ENABLE_CHANNEL_4
	// Initialize pin B1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); // Enable clock for GPIO B
	gpioInitStructure.GPIO_Pin = GPIO_Pin_1; // Pin 1
	GPIO_Init(GPIOB, &gpioInitStructure); // Initialize GPIO B
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_TIM3); // Pin B1 arbitrary function select
#endif


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

#ifdef ENABLE_CHANNEL_1
	// Initialize output compare 1
	TIM_OC1Init(TIM3, &outputCompareInitStructure); // Initialize output compare 1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); // Enable timer preload register on capture compare register 1
	TIM_CCxCmd(TIM3, TIM_Channel_1, TIM_CCx_Enable); // Enable timer capture compare 1 channel
#endif

#ifdef ENABLE_CHANNEL_2
	// Initialize output compare 2
	TIM_OC2Init(TIM3, &outputCompareInitStructure); // Initialize output compare 2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); // Enable timer preload register on capture compare register 2
	TIM_CCxCmd(TIM3, TIM_Channel_2, TIM_CCx_Enable); // Enable timer capture compare 2 channel
#endif

#ifdef ENABLE_CHANNEL_3
	// Initialize output compare 3
	TIM_OC3Init(TIM3, &outputCompareInitStructure); // Initialize output compare 3
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); // Enable timer preload register on capture compare register 3
	TIM_CCxCmd(TIM3, TIM_Channel_3, TIM_CCx_Enable); // Enable timer capture compare 3 channel
#endif

#ifdef ENABLE_CHANNEL_4
	// Initialize output compare 4
	TIM_OC4Init(TIM3, &outputCompareInitStructure); // Initialize output compare 4
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); // Enable timer preload register on capture compare register 4
	TIM_CCxCmd(TIM3, TIM_Channel_4, TIM_CCx_Enable); // Enable timer capture compare 4 channel
#endif


	// DMA initialization
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE); // Enable clock for DMA
	DMA_InitTypeDef dmaInitStructure;
	DMA_StructInit(&dmaInitStructure); // Initialize DMA initialization structure with default values
	dmaInitStructure.DMA_Channel = DMA_Channel_5; // Use DMA channel 5
	dmaInitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; // Transfer data from memory to peripheral
	dmaInitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // Auto increment memory address
	dmaInitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 16 bit DMA data size
	dmaInitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; // 16 bit memory data size
	dmaInitStructure.DMA_Mode = DMA_Mode_Circular; // Circular buffer mode
	dmaInitStructure.DMA_Priority = DMA_Priority_High; // High DMA priority

#ifdef ENABLE_CHANNEL_1
	// Initialize DMA stream 4
	dmaInitStructure.DMA_PeripheralBaseAddr = (uint32_t) &TIM3->CCR1; // Load data into capture compare register 1
	dmaInitStructure.DMA_Memory0BaseAddr = (uint32_t) dmaBuffer1; // Use DMA buffer as data source
	dmaInitStructure.DMA_BufferSize = DMA_BUFFER1_LENGTH; // DMA buffer size = length of DMA buffer
	DMA_Init(DMA1_Stream4, &dmaInitStructure); // Initialize DMA stream 4
	DMA_Cmd(DMA1_Stream4, ENABLE); // Enable DMA stream 4
	TIM_DMACmd(TIM3, TIM_DMA_CC1, ENABLE); // Enable timer DMA request
#endif

#ifdef ENABLE_CHANNEL_2
	// Initialize DMA stream 5
	dmaInitStructure.DMA_PeripheralBaseAddr = (uint32_t) &TIM3->CCR2; // Load data into capture compare register 2
	dmaInitStructure.DMA_Memory0BaseAddr = (uint32_t) dmaBuffer2; // Use DMA buffer as data source
	dmaInitStructure.DMA_BufferSize = DMA_BUFFER2_LENGTH; // DMA buffer size = length of DMA buffer
	DMA_Init(DMA1_Stream5, &dmaInitStructure); // Initialize DMA stream 5
	DMA_Cmd(DMA1_Stream5, ENABLE); // Enable DMA stream 5
	TIM_DMACmd(TIM3, TIM_DMA_CC2, ENABLE); // Enable timer DMA request
#endif

#ifdef ENABLE_CHANNEL_3
	// Initialize DMA stream 7
	dmaInitStructure.DMA_PeripheralBaseAddr = (uint32_t) &TIM3->CCR3; // Load data into capture compare register 3
	dmaInitStructure.DMA_Memory0BaseAddr = (uint32_t) dmaBuffer3; // Use DMA buffer as data source
	dmaInitStructure.DMA_BufferSize = DMA_BUFFER3_LENGTH; // DMA buffer size = length of DMA buffer
	DMA_Init(DMA1_Stream7, &dmaInitStructure); // Initialize DMA stream 7
	DMA_Cmd(DMA1_Stream7, ENABLE); // Enable DMA stream 7
	TIM_DMACmd(TIM3, TIM_DMA_CC3, ENABLE); // Enable timer DMA request
#endif

#ifdef ENABLE_CHANNEL_4
	// Initialize DMA stream 2
	dmaInitStructure.DMA_PeripheralBaseAddr = (uint32_t) &TIM3->CCR4; // Load data into capture compare register 4
	dmaInitStructure.DMA_Memory0BaseAddr = (uint32_t) dmaBuffer4; // Use DMA buffer as data source
	dmaInitStructure.DMA_BufferSize = DMA_BUFFER4_LENGTH; // DMA buffer size = length of DMA buffer
	DMA_Init(DMA1_Stream2, &dmaInitStructure); // Initialize DMA stream 2
	DMA_Cmd(DMA1_Stream2, ENABLE); // Enable DMA stream 2
	TIM_DMACmd(TIM3, TIM_DMA_CC4, ENABLE); // Enable timer DMA request
#endif


	// Enable timer
	TIM_Cmd(TIM3, ENABLE);
}

// Updates a number of LEDs of a channel beginning at the start address
void ws2812_updateLeds(uint8_t channel, uint16_t startAddress, uint16_t ledCount, rgbLed * ledData)
{
	// Update dmaBuffer
	for (uint16_t i = startAddress; i < startAddress + ledCount; i++)
	{
		for (uint8_t j = 0; j < 8; j++)
		{
			switch (channel)
			{
#ifdef ENABLE_CHANNEL_1
			case 1:
				dmaBuffer1[i * 24 + j + 8] = (ledData->r & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
				dmaBuffer1[i * 24 + j] = (ledData->g & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
				dmaBuffer1[i * 24 + j + 16] = (ledData->b & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
				break;
#endif
#ifdef ENABLE_CHANNEL_2
			case 2:
				dmaBuffer2[i * 24 + j + 8] = (ledData->r & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
				dmaBuffer2[i * 24 + j] = (ledData->g & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
				dmaBuffer2[i * 24 + j + 16] = (ledData->b & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
				break;
#endif
#ifdef ENABLE_CHANNEL_3
			case 3:
				dmaBuffer3[i * 24 + j + 8] = (ledData->r & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
				dmaBuffer3[i * 24 + j] = (ledData->g & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
				dmaBuffer3[i * 24 + j + 16] = (ledData->b & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
				break;
#endif
#ifdef ENABLE_CHANNEL_4
			case 4:
				dmaBuffer4[i * 24 + j + 8] = (ledData->r & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
				dmaBuffer4[i * 24 + j] = (ledData->g & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
				dmaBuffer4[i * 24 + j + 16] = (ledData->b & (1 << j)) ? PWM_1_VALUE : PWM_0_VALUE;
				break;
#endif
			default:
				return;
			}
		}
		ledData++; // Increment LED data pointer
	}
}

// Sets a number of LEDs of a channel to RGB value beginning at the start address
void ws2812_setLedsRGB(uint8_t channel, uint16_t startAddress, uint16_t ledCount, uint8_t r, uint8_t g, uint8_t b)
{
	rgbLed led = {.r = r, .g = g, .b = b};
	for (uint16_t i = startAddress; i < startAddress + ledCount; i++)
	{
		ws2812_updateLeds(channel, i, 1, &led);
	}
}

// Sets all LEDs to RGB value
void ws2812_setAllLedsRGB(uint8_t r, uint8_t g, uint8_t b)
{
#ifdef ENABLE_CHANNEL_1
	ws2812_setLedsRGB(0, 0, LED_COUNT_CH1, r, g, b);
#endif
#ifdef ENABLE_CHANNEL_2
	ws2812_setLedsRGB(1, 0, LED_COUNT_CH2, r, g, b);
#endif
#ifdef ENABLE_CHANNEL_3
	ws2812_setLedsRGB(2, 0, LED_COUNT_CH3, r, g, b);
#endif
#ifdef ENABLE_CHANNEL_4
	ws2812_setLedsRGB(3, 0, LED_COUNT_CH4, r, g, b);
#endif
}

// Sets a number of LEDs of a channel to a color beginning at the start address
void ws2812_setLedsToColor(uint8_t channel, uint16_t startAddress, uint16_t ledCount, rgbLed color)
{
	ws2812_setLedsRGB(channel, startAddress, ledCount, color.r, color.g, color.b);
}

// Sets all LEDs to a color
void ws2812_setAllLedsToColor(rgbLed color)
{
	ws2812_setAllLedsRGB(color.r, color.g, color.b);
}

// switches a number of LEDs of a channel off beginning at the start address
void ws2812_switchLedsOff(uint8_t channel, uint16_t startAddress, uint16_t ledCount)
{
	ws2812_setLedsRGB(channel, startAddress, ledCount, 0, 0, 0);
}

// switches all LEDs off
void ws2812_switchAllLedsOff(uint16_t startAddress, uint16_t ledCount)
{
	ws2812_setAllLedsRGB(0, 0, 0);
}
