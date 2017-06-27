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
#include "lib/rs485.h"


void Delay(uint32_t time)
{
	time *= 10000;
	while(time--);
}

int main(void)
{
	SystemInit();

	ledSuit_init();
	rs485_init(38400);

	rgbLed fadeColors[4] = {
				{ .r = 255, .g = 0, .b = 0 },
				{ .r = 0, .g = 255, .b = 0 },
				{ .r = 0, .g = 0, .b = 255 },
				{ .r = 255, .g = 0, .b = 0 } };

	rgbLed pulseColors[5] = {
				{ .r = 10, .g = 0, .b = 0 },
				{ .r = 50, .g = 0, .b = 0 },
				{ .r = 255, .g = 0, .b = 0 },
				{ .r = 50, .g = 0, .b = 0 },
				{ .r = 10, .g = 0, .b = 0 } };

	ledSuit_color(LEFT_LEG, 0, 0, white, 1);
	ledSuit_setStrobePeriod(1);
	ledSuit_enableStrobe(LEFT_LEG, 1);

	ledSuit_configureAutoColorFade(RIGHT_LEG, 3, fadeColors, 255);
	ledSuit_enableAutoColorFade(RIGHT_LEG, 1);

	ledSuit_colorFade(RIGHT_ARM, 4, fadeColors, 1);
	ledSuit_color(LEFT_ARM, 0, 0, black, 0);
	ledSut_colorArray(LEFT_ARM, 0, 5, pulseColors, 1);
	ledSuit_configureAutoRotate(RIGHT_ARM + LEFT_ARM, forwards, 255);
	ledSuit_enableAutoRotate(RIGHT_ARM + LEFT_ARM, 1);

	while(1) {
		//rs485_requestSensorData(leftArmSensor);
		Delay(1000);
	}
}


