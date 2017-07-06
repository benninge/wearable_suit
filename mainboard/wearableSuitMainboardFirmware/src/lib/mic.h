/*
 * mic.h
 *
 *  Created on: 04.07.2017
 *      Author: kekse
 */

#ifndef LIB_MIC_H_
#define LIB_MIC_H_

#include "stm32f4xx.h"


// Initializes the microphone library
void mic_init(void);

// Gets the spectrum of the current sound recorded by the microphone, The array size of "spectrum" must be 10
void mic_getSpectrum(uint8_t * spectrum);


#endif /* LIB_MIC_H_ */
