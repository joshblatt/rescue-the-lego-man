#include <colour_sensor.h>

#include <stdio.h>
#include <string.h>

#include <main.h>


// Right Colour Sensor
// S2 = PC0
// S3 = PC1
// OUT = PA12(possible will change)

// Left Colour Sensor
// S2 = PC3
// S3 = PB0
// OUT = PB7

UART_HandleTypeDef *uart1;
UART_HandleTypeDef *uart6;

void initColourSensors(UART_HandleTypeDef *huart1, UART_HandleTypeDef *huart6) {
	uart1 = huart1;
	uart6 = huart6;
}

uint8_t getRightColourRaw() {
	uint8_t rxData = 0;
	HAL_UART_Receive(uart1, &rxData, sizeof(rxData), HAL_MAX_DELAY);
	HAL_Delay(10);
	return rxData;
}

uint8_t getLeftColourRaw() {
	uint8_t rxData = 0;
	HAL_UART_Receive(uart6, &rxData, sizeof(rxData), HAL_MAX_DELAY);
	HAL_Delay(10);
	return rxData;
}

volatile uint8_t redRight;
volatile uint8_t greenRight;
volatile uint8_t blueRight;
Colour getRightColour() {
	setRightColour(RED);
	redRight = getRightColourRaw();
	setRightColour(GREEN);
	greenRight = getRightColourRaw();
	setRightColour(BLUE);
	blueRight = getRightColourRaw();

	if (redRight >= 25 && redRight <= 85) {
		return RED;
	} else if (greenRight >= 25 && redRight <= 85) {
		return GREEN;
	} else if (blueRight >= 25 && blueRight <= 85) {
		return BLUE;
	}

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
	HAL_Delay(10);
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
	HAL_Delay(10);
}
