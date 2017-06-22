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
	ledSuit_init();

	for(;;)
	{
		ledSuit_colorLeftArm(red);
		ledSuit_colorRightArm(white);
		Delay(1000);
		ledSuit_colorLeftArm(orange);
		Delay(1000);
		ledSuit_colorLeftArm(yellow);
		Delay(1000);
		ledSuit_colorLeftArm(green);
		Delay(1000);
		ledSuit_colorLeftArm(teal);
		Delay(1000);
		ledSuit_colorLeftArm(blue);
		Delay(1000);
		ledSuit_colorLeftArm(purple);
		Delay(1000);
		ledSuit_colorLeftArm(pink);
		Delay(1000);
		ledSuit_colorLeftArm(white);
		Delay(1000);
		ledSuit_colorLeftArmRgb(50, 50, 50);
		ledSuit_colorRightArmRgb(50, 50, 50);
		Delay(1000);
		ledSuit_enableLeftArm(0);
		Delay(1000);
		ledSuit_enableLeftArm(1);
		Delay(1000);
	}
}
