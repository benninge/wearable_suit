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

	while (1)
	{
		ledSuit_colorBodyPart(leftArm, red, 1);
		ledSuit_colorBodyPart(rightArm, green, 1);
		ledSuit_colorBodyPart(leftLeg, blue, 1);
		ledSuit_colorBodyPart(rightLeg, yellow, 1);
		Delay(1000);
		ledSuit_colorBodyPartRgb(leftArm, 50, 50, 50, 1);
		ledSuit_colorBodyPartRgb(rightArm, 50, 50, 50, 0);
		Delay(1000);
		ledSuit_updateAll();
		Delay(1000);
		ledSuit_colorAll(white, 1);
		Delay(1000);
		ledSuit_enableAll(0, 1);
		Delay(1000);
		ledSuit_enableAll(1, 1);
		Delay(1000);
	}
}
