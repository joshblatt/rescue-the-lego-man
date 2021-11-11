#include <colour_sensor.h>

#include <main.h>

// Colour Sensor 1
// OUT = PC0
// S2 = PC1
// S3 = PB0

// Colour Sensor 2
float getReading(ADC_HandleTypeDef* hadc1) {
	HAL_ADC_Start(hadc1);
	HAL_ADC_PollForConversion(hadc1, HAL_MAX_DELAY);
	float raw = HAL_ADC_GetValue(hadc1);
	return raw;
}

void setColour(Colour colour) {
	if (colour == RED) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	} else if (colour == BLUE) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	} else if (colour == CLEAR) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	} else if (colour == GREEN) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	}
}
