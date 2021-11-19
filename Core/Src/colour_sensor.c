#include <colour_sensor.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <main.h>

// Test with right
// Right Colour Sensor
// S2 = PC0
// S3 = PC1
// OUT = PB7 (UART1)

// Left Colour Sensor
// S2 = PC3
// S3 = PB0
// OUT = PA12 (UART6)

UART_HandleTypeDef *uart1;
UART_HandleTypeDef *uart6;
TIM_HandleTypeDef *tim4;

Frequency freq_WB;
Frequency freq_DC;

volatile int startCapture = false;
volatile int isFirstCaptured = false;
volatile int captureDone = false;

volatile uint32_t captures[2] = {0};
volatile uint32_t diffCapture = 0;
volatile float frequency = 0;

volatile bool whiteBalance = false;
volatile bool darkColour = false;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == tim4->Instance && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2 && startCapture) {
		if (!isFirstCaptured) {
			captures[0] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			isFirstCaptured = true;
		} else {
			captures[1] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);

			if (captures[1] >= captures[0]) {
				diffCapture = captures[1] - captures[0];
			} else {
				diffCapture = (htim->Instance->ARR - captures[0]) + captures[1] + 1;
			}

			frequency = HAL_RCC_GetPCLK1Freq() / (tim4->Instance->PSC + 1.0);
			frequency = (float) frequency / (float) diffCapture;

			__HAL_TIM_SET_COUNTER(htim, 0);

			startCapture = false;
			isFirstCaptured = false;
			captureDone = true;

		}
	}
}

// Initialize and calibrate colour sensors
void initColourSensors(TIM_HandleTypeDef* htim4, UART_HandleTypeDef *huart6) {
	uart6 = huart6;
	tim4 = htim4;
	HAL_TIM_IC_Start_IT(tim4, TIM_CHANNEL_2);


	// Give 5 seconds to place white sheet in front of sensors
	HAL_Delay(5000);
	getRightColourIntensities(&freq_WB);
	whiteBalance = true;
	// Give 5 seconds to place black sheet in front of sensors
	HAL_Delay(5000);
	getRightColourIntensities(&freq_DC);
	darkColour = true;

	HAL_Delay(10);

}

float getRightColourFrequency() {
	captureDone = false;
	startCapture = true;
	isFirstCaptured = false;
	while (!captureDone) {}
	return frequency;
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

void getRightRGB(RGB *rgb) {
	Frequency freq;
	getRightColourIntensities(&freq);

	float ared = (freq.red - freq_DC.red) / (freq_WB.red - freq_DC.red);
	float agreen = (freq.green - freq_DC.green) / (freq_WB.green - freq_DC.green);
	float ablue = (freq.blue - freq_DC.blue) / (freq_WB.blue - freq_DC.blue);

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

uint8_t getLeftColourRaw() {
	uint8_t rxData = 0;
	HAL_UART_Receive(uart6, &rxData, sizeof(rxData), HAL_MAX_DELAY);
	HAL_Delay(10);
	return rxData;
}

//volatile uint8_t redRight;
//volatile uint8_t greenRight;
//volatile uint8_t blueRight;
Colour getRightColour() {
	return CLEAR;
}

volatile uint8_t redLeft;
volatile uint8_t greenLeft;
volatile uint8_t blueLeft;
Colour getLeftColour() {
	setLeftColour(RED);
	redLeft = getLeftColourRaw();
	setLeftColour(GREEN);
	greenLeft = getLeftColourRaw();
	setLeftColour(BLUE);
	blueLeft = getLeftColourRaw();

	if (redLeft >= 100 && redLeft <= 255 && greenLeft >= 40 && greenLeft <= 110 && blueLeft >= 0 && blueLeft <= 200) {
		return RED;
	} else if (greenLeft >= 25 && greenLeft <= 85) {
		return GREEN;
	} else if (blueLeft >= 25 && blueLeft <= 85) {
		return BLUE;
	}
	return CLEAR;
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
