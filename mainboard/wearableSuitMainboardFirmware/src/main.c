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
#include "lib/bluetooth.h"
#include "lib/mic.h"


void Delay2(uint32_t time)
{
	time *= 10000;
	while(time--);
}


int main(void)
{
	SystemInit();

	mic_init();
	ledSuit_init();
	rs485_init(57600);

	rgbLed fadeColors[4] = {
			{ .r = 255, .g = 0, .b = 0 },
			{ .r = 0, .g = 255, .b = 0 },
			{ .r = 0, .g = 0, .b = 255 },
			{ .r = 255, .g = 0, .b = 0 } };

	//ledSuit_colorFade(WHOLE_SUIT & ~CHEST, 4, fadeColors, 1);
	//ledSuit_configureAutoRotate(WHOLE_SUIT & ~CHEST, forwards, 240);
	//ledSuit_enableAutoRotate(WHOLE_SUIT & ~CHEST, 1);

	ledSuit_colorFade(WHOLE_SUIT, 4, fadeColors, 1);
	ledSuit_configureAutoRotate(WHOLE_SUIT, forwards, 240);
	ledSuit_enableAutoRotate(WHOLE_SUIT, 1);

	while (1);
	{
		//Delay2(100);

		//uint8_t spectrum[10];
		//mic_getSpectrum(spectrum, 230);
		/*uint16_t audioLevel = mic_getAudioLevel();
		audioLevel /= 100;
		if (audioLevel < 10) audioLevel = 0;
		else audioLevel -= 10;*/

		//rs485_updateSensorData();

		uint8_t leftArmMoving = rs485_getMoving(leftArmSensor);
		uint8_t rightArmMoving = rs485_getMoving(rightArmSensor);
		uint8_t leftLegMoving = rs485_getMoving(leftLegSensor);
		uint8_t rightLegMoving = rs485_getMoving(rightLegSensor);

		ledSuit_enable(LEFT_ARM, leftArmMoving, 1);
		ledSuit_enable(RIGHT_ARM, rightArmMoving, 1);
		ledSuit_enable(LEFT_LEG, leftLegMoving, 1);
		ledSuit_enable(RIGHT_LEG, rightLegMoving, 1);

		//ledSuit_setBrightness(WHOLE_SUIT, audioLevel, 1);
		//ledSuit_displaySpectrum(spectrum, 1);
	}

	//rs485_init(38400);

	//while(1) {
		//rs485_requestSensorData(leftArmSensor);
		//Delay2(100);
		//rs485_updateSensorData(leftArmSensor);
		//Delay(33);
	//}
}


