#include <colour_sensor.h>

#include <main.h>

// Right Colour Sensor
// S2 = PC0
// S3 = PC1
// OUT = PA0 (possible will change)

// Left Colour Sensor
// S2 = PA4
// S3 = PA1
// OUT = PA12 (works) huart6

uint8_t getRightColourRaw(UART_HandleTypeDef *huart6) {
	// TODO change to different uart to read
	uint8_t rxData;
	HAL_UART_Receive(huart6, &rxData, sizeof(rxData), HAL_MAX_DELAY);
	HAL_Delay(200);
	return rxData;
}

uint8_t getLeftColourRaw(UART_HandleTypeDef *huart6) {
	uint8_t rxData;
	HAL_UART_Receive(huart6, &rxData, sizeof(rxData), HAL_MAX_DELAY);
	HAL_Delay(200);
	return rxData;
}

Colour getRightColour(UART_HandleTypeDef *huart6) {
	setLeftColour(RED);
	uint8_t red = getLeftColourRaw(huart6);
	setLeftColour(GREEN);
	uint8_t green = getLeftColourRaw(huart6);
	setLeftColour(BLUE);
	uint8_t blue = getLeftColourRaw(huart6);

	HAL_Delay(200);

	if (red >= green && red >= blue) {
		return RED;
	} else if (green >= red && green >= blue) {
		return GREEN;
	}
	return BLUE;
}
Colour getLeftColour(UART_HandleTypeDef *huart6) {
	setLeftColour(RED);
	uint8_t red = getLeftColourRaw(huart6);
	setLeftColour(GREEN);
	uint8_t green = getLeftColourRaw(huart6);
	setLeftColour(BLUE);
	uint8_t blue = getLeftColourRaw(huart6);

	HAL_Delay(200);

	if (red >= green && red >= blue) {
		return RED;
	} else if (green >= red && green >= blue) {
		return GREEN;
	}
	return BLUE;
}

void setRightColour(Colour colour) {
	if (colour == RED) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	} else if (colour == BLUE) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	} else if (colour == CLEAR) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	} else if (colour == GREEN) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	}
	HAL_Delay(200);
}

void setLeftColour(Colour colour) {
	if (colour == RED) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	} else if (colour == BLUE) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	} else if (colour == CLEAR) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	} else if (colour == GREEN) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	}
	HAL_Delay(200);
}
