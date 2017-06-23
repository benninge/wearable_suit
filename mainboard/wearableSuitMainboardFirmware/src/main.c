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

#include "lib/ledSuit.h"


void Delay(uint32_t time)
{
	time *= 10000;
	while(time--);
}

int main(void)
{
	SystemInit();


	ledSuit_init();
	ledSuit_setAllBrightness(50, 0);

	rgbLed colors[4] = {
			{ .r = 255, .g = 0, .b = 0 },
			{ .r = 0, .g = 255, .b = 0 },
			{ .r = 0, .g = 0, .b = 255 },
			{ .r = 255, .g = 0, .b = 0 } };

	ledSuit_colorAllColorFade(4, colors, 1);

	ledSuit_enableAllAutoRotate(1);
	//ledSuit_enableAllStrobe(1);

	while(1);
}


