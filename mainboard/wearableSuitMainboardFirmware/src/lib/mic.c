/*
 * mic.c
 *
 *  Created on: 04.07.2017
 *      Author: kekse
 */

#include "mic.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "arm_math.h"
#include "arm_common_tables.h"


#define NUMBER_OF_SAMPLES 2048 // Array size of sample buffer


// FFT instance, FFT size should be half of number of samples
const arm_cfft_instance_f32 _fftInstance = {1024, twiddleCoef_1024, armBitRevIndexTable1024, ARMBITREVINDEXTABLE1024_TABLE_LENGTH};
// Indexes which are used for generating a spectrum from the FFT output
const uint16_t _spectrumIndexes[10] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 511};


// Global variables
uint16_t _sampleBuffer[NUMBER_OF_SAMPLES]; // Array containing a stream of ADC samples


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

	// Set microphone configuration pins
	GPIO_SetBits(GPIOC, GPIO_Pin_1 & GPIO_Pin_2); // 1:2000 A/R ratio , 40dB gain

	// ADC initialization
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // Enable clock for ADC
	ADC_InitTypeDef adcInitStructure;
	ADC_StructInit(&adcInitStructure); // Initialize ADC initialization structure with default values
	adcInitStructure.ADC_ContinuousConvMode = ENABLE; // Continuous conversion
	ADC_Init(ADC1, &adcInitStructure); // Initialize ADC
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_112Cycles); // Configure ADC channel
	ADC_Cmd(ADC1, ENABLE); // Enable ADC

	// Start ADC conversion
	ADC_SoftwareStartConv(ADC1);

	// Initialize timer for ADC sampling
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // Enable clock for timer
	TIM_TimeBaseInitTypeDef  timerInitStructure;
	TIM_TimeBaseStructInit(&timerInitStructure); // Initialize timer initialization structure with default values
	timerInitStructure.TIM_Period = SystemCoreClock / 40000 - 1;  // 40 kHz sampling rate = 20 kHz max frequency
	TIM_TimeBaseInit(TIM4, &timerInitStructure); // Initialize timer
	// Initialize timer interrupt
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; // Timer 4 interrupt
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5; // Medium priority
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5; // Medium priority
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // Enable interrupt
	NVIC_Init(&NVIC_InitStructure); // Initialize timer interrupt
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update); // Clear interrupt flag
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); // Enable timer update interrupt

	// Start timer for ADC sampling
	TIM_Cmd(TIM4, ENABLE);
}

// Gets the spectrum of the current sound recorded by the microphone, The array size of "spectrum" must be 10
void mic_getSpectrum(uint8_t * spectrum)
{
	const arm_cfft_instance_f32 * fft = &_fftInstance; // FFT instance pointer

	float32_t fftInput[NUMBER_OF_SAMPLES]; // FFT input array
	float32_t fftOutput[NUMBER_OF_SAMPLES / 2]; // FFT output array

	// Fill FFT input array with microphone measurements
	for (int i = 0; i < NUMBER_OF_SAMPLES; i++)
	{
		fftInput[i] = (float32_t)_sampleBuffer[i] - 1750;
	}

	// Run FFT on microphone measurement
	arm_cfft_f32(fft, fftInput, 0, 1);
	arm_cmplx_mag_f32(fftInput, fftOutput, NUMBER_OF_SAMPLES / 2);

	// Calculate the first spectrum data point from the FFT output
	if((uint16_t)(fftOutput[1] / 1000) > 255) // Amplitude of the frequency range is above the uint8 value range
	{
		spectrum[0] = 255; // Set data point to max value
	}
	else
	{
		spectrum[0] = (uint16_t)(fftOutput[1] / 1000);
	}

	// Calculate the remaining spectrum data points from the FFT output
	for (uint8_t i = 0; i < 9; i++)
	{
		// find the frequency with the highest amplitude in the frequency range
		uint16_t max = 0;
		for (uint16_t j = _spectrumIndexes[i] + 1; j <= _spectrumIndexes[i + 1]; j++)
		{
			if ((fftOutput[j] / 1000) > max)
			{
				max = (uint16_t)(fftOutput[j] / 1000);
			}
		}

		if (max > 255) // Amplitude of the frequency range is above the uint8 value range
		{
			spectrum[i + 1] = 255; // Set data point to max value
		}
		else
		{
			spectrum[i + 1] = max;
		}
	}
}


// Timer 4 interrupt handler
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update)) // Timer update interrupt
	{
		static uint16_t bufferIndex = 0;

		_sampleBuffer[bufferIndex] = ADC_GetConversionValue(ADC1); // Write current ADC sample to buffer

		if (bufferIndex >= NUMBER_OF_SAMPLES) // End of buffer reached
		{
			bufferIndex = 0; // Reset buffer index
		}
		else
		{
			bufferIndex++; // Increment buffer index
		}

	    TIM_ClearITPendingBit(TIM4, TIM_IT_Update); // Clear interrupt flag
	}
}
