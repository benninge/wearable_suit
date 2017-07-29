/*
 * mic.h
 *
 *  Created on: 04.07.2017
 *      Author: kekse
 */

#ifndef LIB_MIC_H_
#define LIB_MIC_H_

#include "stm32f4xx.h"


// Microphone output pin connected to pin C0
// Microphone AR pin connected to pin C1
// Microphone gain pin connected to pin C2


// Initializes the microphone library
void mic_init(void);

// Gets the current audio level as a value between 0 and 4095
uint16_t mic_getAudioLevel();

// Gets the spectrum of the current sound recorded by the microphone, The array size of "spectrum" must be 10
void mic_getSpectrum(uint8_t * spectrum, uint8_t sensitivity);


#endif /* LIB_MIC_H_ */
