/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"

#include "lib/smartSuit.h"
#include "lib/bluetooth.h"

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

int main(void)
{
	SystemInit();

	smartSuit_init(); // Initialize smart dancing suit

	smartSuit_demo(5); // Run smart dancing suit demo program
}


