/*
 * mic.c
 *
 *  Created on: 04.07.2017
 *      Author: kekse
 */


#include "mic.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"

#include "arm_math.h"
#include "arm_common_tables.h"


#define DMA_BUFFER_LENGTH 128

// Global variables
uint16_t dmaBuffer[DMA_BUFFER_LENGTH]; // Array containing a stream of ADC samples


// Initializes the microphone library
void mic_init(void)
{
	// GPIO initialization
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); // Enable clock for GPIO C
	GPIO_InitTypeDef gpioInitStructure;
	GPIO_StructInit(&gpioInitStructure); // Initialize GPIO initialization structure with default values
	// Analog input initialization
	gpioInitStructure.GPIO_Pin = GPIO_Pin_0; // Pin 0
	gpioInitStructure.GPIO_Mode = GPIO_Mode_AN; // GPIO in analog mode
	GPIO_Init(GPIOC, &gpioInitStructure); // Initialize GPIO C
	// Gain and A/R ratio output initialization
	gpioInitStructure.GPIO_Pin = GPIO_Pin_1 & GPIO_Pin_2; // Pin 1 and 2
	gpioInitStructure.GPIO_Mode = GPIO_Mode_OUT; // GPIO as output
	GPIO_Init(GPIOC, &gpioInitStructure); // Initialize GPIO C

	GPIO_SetBits(GPIOC, GPIO_Pin_1 & GPIO_Pin_2); // 1:2000 A/R ratio , 40dB gain

	// ADC initialization
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // Enable clock for ADC
	ADC_InitTypeDef adcInitStructure;
	ADC_StructInit(&adcInitStructure); // Initialize ADC initialization structure with default values
	adcInitStructure.ADC_ContinuousConvMode = ENABLE; // Continuous conversion
	ADC_Init(ADC1, &adcInitStructure); // Initialize ADC
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_480Cycles); // Configure ADC channel
	ADC_Cmd(ADC1, ENABLE); // Enable ADC

	// DMA initialization
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); // Enable clock for DMA
	DMA_InitTypeDef dmaInitStructure;
	DMA_StructInit(&dmaInitStructure); // Initialize DMA initialization structure with default values
	dmaInitStructure.DMA_Channel = DMA_Channel_0; // Use DMA channel 0
	dmaInitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR; // Store data from ADC 1 data register
	dmaInitStructure.DMA_Memory0BaseAddr = (uint32_t)dmaBuffer; // Write data to DMA buffer
	dmaInitStructure.DMA_BufferSize = (uint32_t)DMA_BUFFER_LENGTH; // DMA buffer size = length of DMA buffer
	dmaInitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // Auto increment memory address
	dmaInitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 16 bit DMA data size
	dmaInitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; // 16 bit memory data size
	dmaInitStructure.DMA_Mode = DMA_Mode_Circular; // Circular buffer mode
	//dmaInitStructure.DMA_Priority = DMA_Priority_High; // High DMA priority
	DMA_Init(DMA2_Stream0, &dmaInitStructure); // Initialize DMA stream 0
	DMA_Cmd(DMA2_Stream0, ENABLE); // Enable DMA stream 0
	while (DMA_GetCmdStatus(DMA2_Stream0) != ENABLE); // Wait for DMA to become enabled
	ADC_DMACmd(ADC1, ENABLE); // Enable ADC DMA request

	ADC_SoftwareStartConv(ADC1); // Start ADC conversion
}

const arm_cfft_instance_f32 CFFT_Instances[] = {
	{16, twiddleCoef_16, armBitRevIndexTable16, ARMBITREVINDEXTABLE__16_TABLE_LENGTH},
	{32, twiddleCoef_32, armBitRevIndexTable32, ARMBITREVINDEXTABLE__32_TABLE_LENGTH},
	{64, twiddleCoef_64, armBitRevIndexTable64, ARMBITREVINDEXTABLE__64_TABLE_LENGTH},
	{128, twiddleCoef_128, armBitRevIndexTable128, ARMBITREVINDEXTABLE_128_TABLE_LENGTH},
	{256, twiddleCoef_256, armBitRevIndexTable256, ARMBITREVINDEXTABLE_256_TABLE_LENGTH},
	{512, twiddleCoef_512, armBitRevIndexTable512, ARMBITREVINDEXTABLE_512_TABLE_LENGTH},
	{1024, twiddleCoef_1024, armBitRevIndexTable1024, ARMBITREVINDEXTABLE1024_TABLE_LENGTH},
	{2048, twiddleCoef_2048, armBitRevIndexTable2048, ARMBITREVINDEXTABLE2048_TABLE_LENGTH},
	{4096, twiddleCoef_4096, armBitRevIndexTable4096, ARMBITREVINDEXTABLE4096_TABLE_LENGTH}
};

// Only for testing purposes
void mic_test(void)
{
	const arm_cfft_instance_f32 * fft = &CFFT_Instances[2];

	float32_t Input[DMA_BUFFER_LENGTH];   /*!< Input buffer is always 2 * FFT_SIZE */
	float32_t Output[DMA_BUFFER_LENGTH / 2]; /*!< Output buffer is always FFT_SIZE */

	for (int i = 0; i < DMA_BUFFER_LENGTH; i++)
	{
		Input[i] = (float32_t)dmaBuffer[i] - 1750;
	}

	float32_t MaxValue;
	uint32_t MaxIndex;

	arm_cfft_f32(fft, Input, 0, 1);
	arm_cmplx_mag_f32(Input, Output, DMA_BUFFER_LENGTH / 2);
	arm_max_f32(Output, DMA_BUFFER_LENGTH / 2, &MaxValue, &MaxIndex);


	//uint16_t value = ADC_GetConversionValue(ADC1);
	//DMA_Cmd(DMA2_Stream0, DISABLE); // Enable DMA stream 0
	//DMA_Cmd(DMA2_Stream0, ENABLE); // Enable DMA stream 0
	//ADC_DMACmd(ADC1, ENABLE); // Enable ADC DMA request
	//ADC_SoftwareStartConv(ADC1); // Start ADC conversion
	return;
}
