#include <colour_sensor.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <main.h>

// Test with right
// Right Colour Sensor
// S2 = PC0
// S3 = PC1
// OUT = PB7 TIM4_CH2

// Left Colour Sensor
// S2 = PC3
// S3 = PB0
// OUT = PB9 TIM4_CH4

TIM_HandleTypeDef *tim4;

Frequency freqWBRight;
Frequency freqDCRight;

volatile int startCaptureRight = false;
volatile int isFirstCapturedRight = false;
volatile int captureDoneRight = false;

volatile uint32_t capturesRight[2] = {0};
volatile uint32_t diffCaptureRight = 0;
volatile float frequencyRight = 0;

Frequency freqWBLeft;
Frequency freqDCLeft;

volatile int startCaptureLeft = false;
volatile int isFirstCapturedLeft = false;
volatile int captureDoneLeft = false;

volatile uint32_t capturesLeft[2] = {0};
volatile uint32_t diffCaptureLeft = 0;
volatile float frequencyLeft = 0;

volatile bool whiteBalance = false;
volatile bool darkColour = false;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == tim4->Instance && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2 && startCaptureRight) {
		if (!isFirstCapturedRight) {
			capturesRight[0] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			isFirstCapturedRight = true;
		} else {
			capturesRight[1] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);

			if (capturesRight[1] >= capturesRight[0]) {
				diffCaptureRight = capturesRight[1] - capturesRight[0];
			} else {
				diffCaptureRight = (htim->Instance->ARR - capturesRight[0]) + capturesRight[1] + 1;
			}

			frequencyRight = HAL_RCC_GetPCLK1Freq() / (tim4->Instance->PSC + 1.0);
			frequencyRight = (float) frequencyRight / (float) diffCaptureRight;

			__HAL_TIM_SET_COUNTER(htim, 0);

			startCaptureRight = false;
			isFirstCapturedRight = false;
			captureDoneRight = true;

		}
	}
	if (htim->Instance == tim4->Instance && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4 && startCaptureLeft) {
		if (!isFirstCapturedLeft) {
			capturesLeft[0] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
			isFirstCapturedLeft = true;
		} else {
			capturesLeft[1] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);

			if (capturesLeft[1] >= capturesLeft[0]) {
				diffCaptureLeft = capturesLeft[1] - capturesLeft[0];
			} else {
				diffCaptureLeft = (htim->Instance->ARR - capturesLeft[0]) + capturesLeft[1] + 1;
			}

			frequencyLeft = HAL_RCC_GetPCLK1Freq() / (tim4->Instance->PSC + 1.0);
			frequencyLeft = (float) frequencyLeft / (float) diffCaptureLeft;

			__HAL_TIM_SET_COUNTER(htim, 0);

			startCaptureLeft = false;
			isFirstCapturedLeft = false;
			captureDoneLeft = true;

		}
	}
}

// Initialize and calibrate colour sensors
void initColourSensors(TIM_HandleTypeDef* htim4) {
	tim4 = htim4;
	HAL_TIM_IC_Start_IT(tim4, TIM_CHANNEL_2);
	HAL_TIM_IC_Start_IT(tim4, TIM_CHANNEL_4);

	// Give 5 seconds to place white sheet in front of sensors
	HAL_Delay(5000);
	getRightColourIntensities(&freqWBRight);
	getLeftColourIntensities(&freqWBLeft);
	whiteBalance = true;
	// Give 5 seconds to place black sheet in front of sensors
	HAL_Delay(5000);
	getRightColourIntensities(&freqDCRight);
	getLeftColourIntensities(&freqDCLeft);
	darkColour = true;

	HAL_Delay(10);

}

float getRightColourFrequency() {
	captureDoneRight = false;
	startCaptureRight = true;
	isFirstCapturedRight = false;
	while (!captureDoneRight) {}
	return frequencyRight;
}

float getLeftColourFrequency() {
	captureDoneLeft = false;
	startCaptureLeft = true;
	isFirstCapturedLeft = false;
	while (!captureDoneLeft) {}
	return frequencyLeft;
}

void getRightColourIntensities(Frequency *freq) {
	setRightColour(RED);
	freq->red = getRightColourFrequency();
	setRightColour(GREEN);
	freq->green = getRightColourFrequency();
	setRightColour(BLUE);
	freq->blue = getRightColourFrequency();
	setRightColour(CLEAR);
	freq->clear = getRightColourFrequency();
}

void getLeftColourIntensities(Frequency *freq) {
	setLeftColour(RED);
	freq->red = getLeftColourFrequency();
	setLeftColour(GREEN);
	freq->green = getLeftColourFrequency();
	setLeftColour(BLUE);
	freq->blue = getLeftColourFrequency();
	setLeftColour(CLEAR);
	freq->clear = getLeftColourFrequency();
}

void getRightRGB(RGB *rgb) {
	Frequency freq;
	getRightColourIntensities(&freq);

	float ared = (freq.red - freqDCRight.red) / (freqWBRight.red - freqDCRight.red);
	float agreen = (freq.green - freqDCRight.green) / (freqWBRight.green - freqDCRight.green);
	float ablue = (freq.blue - freqDCRight.blue) / (freqWBRight.blue - freqDCRight.blue);

	float amax = ared;
	if (agreen > amax) {
		amax = agreen;
	}
	if (ablue > amax) {
		amax = ablue;
	}
	if (amax < 1.0) {
		amax = 1.0;
	}

	rgb->red = (uint8_t) (255 * ared / amax);
	rgb->green = (uint8_t) (255 * agreen / amax);
	rgb->blue = (uint8_t) (255 * ablue / amax);
}

void getLeftRGB(RGB *rgb) {
	Frequency freq;
	getLeftColourIntensities(&freq);

	float ared = (freq.red - freqDCLeft.red) / (freqWBLeft.red - freqDCLeft.red);
	float agreen = (freq.green - freqDCLeft.green) / (freqWBLeft.green - freqDCLeft.green);
	float ablue = (freq.blue - freqDCLeft.blue) / (freqWBLeft.blue - freqDCLeft.blue);

	float amax = ared;
	if (agreen > amax) {
		amax = agreen;
	}
	if (ablue > amax) {
		amax = ablue;
	}
	if (amax < 1.0) {
		amax = 1.0;
	}

	rgb->red = (uint8_t) (255 * ared / amax);
	rgb->green = (uint8_t) (255 * agreen / amax);
	rgb->blue = (uint8_t) (255 * ablue / amax);
}

Colour getRightColour() {
	RGB rgb;
	getRightRGB(&rgb);
	if (rgb.red >= 200 && rgb.green >= 200 && rgb.blue >= 200) {
		return NO_COLOUR;
	} else if (rgb.red >= rgb.green && rgb.red >= rgb.blue) {
		return RED;
	} else if (rgb.green >= rgb.red && rgb.green >= rgb.blue) {
		return GREEN;
	}
	return BLUE;
}


Colour getLeftColour() {
	RGB rgb;
	getLeftRGB(&rgb);
	if (rgb.red >= 200 && rgb.green >= 200 && rgb.blue >= 200) {
		return NO_COLOUR;
	} else if (rgb.red >= rgb.green && rgb.red >= rgb.blue) {
		return RED;
	} else if (rgb.green >= rgb.red && rgb.green >= rgb.blue) {
		return GREEN;
	}
	return BLUE;
}

void setRightColour(Colour colour) {
	if (colour == RED) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	} else if (colour == BLUE) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	} else if (colour == CLEAR) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	} else if (colour == GREEN) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	}
	HAL_Delay(3);
}

void setLeftColour(Colour colour) {
	if (colour == RED) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	} else if (colour == BLUE) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	} else if (colour == CLEAR) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	} else if (colour == GREEN) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	}
	HAL_Delay(3);
}
