/*
 * smartSuit.h
 *
 *  Created on: 01.08.2017
 *      Author: kekse
 */

#ifndef LIB_SMARTSUIT_H_
#define LIB_SMARTSUIT_H_

#include "stm32f4xx.h"

/******************************************************************************
 * 																			  *
 *		Demos:																  *
 *																			  *
 *		1:	Music spectrum and color fade auto rotate demo					  *
 *		2:	Sound level and moving demo										  *
 *		3:	Music spectrum and strobe moving demo							  *
 *		4:	Moving and auto color fade demo									  *
 *		5:	Pulse and smiley demo											  *
 *		6:	Play Simon says													  *
 * 																			  *
 ******************************************************************************/

// Initializes the smart dancing suit
void smartSuit_init(void);

// Arms and legs are enabled if they are moving (if strobe is != 0, they will use strobe)
void smartSuit_enableMoving(uint8_t strobe);

// Sets the body part brightness according to the music sound level
void smartSuit_setMusicBrightness(uint8_t bodyPart);
// Displays the current music spectrum on the chest
void smartSuit_displayMusicSpectrum();

// Runs a demo from the list above (this function does not return)
void smartSuit_demo(int demoNumber);

#endif /* LIB_SMARTSUIT_H_ */
