#include <motor.h>

#include <main.h>

void moveMotors() {
	// Motor 1 Pins
	// IN1 = PB5
	// IN2 = PB13

	// Motor 2 Pins
	// IN3 = PB4
	// IN4 = PB14

	// Motor 3 Pins
	// IN5 = PB10
	// IN6 = PB15

	// Motor 4 Pins
	// IN7 = PA8
	// IN8 = PB1


	// Truth Table
	// 0 0	off
	// 0 1	forward
	// 1 0	backward
	// 1 1	off

	// Motor 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

	// Motor 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

	// Motor 3
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

	// Motor 4
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

	HAL_Delay(500);
}
