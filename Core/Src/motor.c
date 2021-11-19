#include <motor.h>

#include <main.h>

TIM_HandleTypeDef *tim1;
TIM_HandleTypeDef *tim3;

void initMotors(TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim3) {
	  HAL_TIM_PWM_Start(htim1, TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(htim3, TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(htim3, TIM_CHANNEL_4);
	  HAL_TIM_PWM_Start(htim3, TIM_CHANNEL_1);
	  tim1 = htim1;
	  tim3 = htim3;
	  htim1->Instance->CCR2 = 850;
	  htim3->Instance->CCR2 = 850;
	  htim3->Instance->CCR4 = 850;
	  htim3->Instance->CCR1 = 850;
	  HAL_Delay(1000);
}

void moveMotors() {
	// Motor 1 Pins - Back Left Motor
	// IN1 = PB5
	// IN2 = PB13

	// Motor 2 Pins - Front Left Motor
	// IN3 = PB4
	// IN4 = PB14

	// Motor 3 Pins - Front Right Motor
	// IN5 = PB10 -> PC4
	// IN6 = PB15

	// Motor 4 Pins - Back Right Motor
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
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

	// Motor 4
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

	HAL_Delay(500);
}

void moveForwards() {
	// Motor 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

	// Motor 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

	// Motor 3
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

	// Motor 4
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

	HAL_Delay(1000);
}

void moveBackwards() {
	// Motor 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

	// Motor 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

	// Motor 3
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

	// Motor 4
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

	HAL_Delay(1000);
}

void turnRight() {
	// Motor 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

	// Motor 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

	// Motor 3
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

	// Motor 4
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

	HAL_Delay(2000);
}

void turnLeft() {
	// Motor 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

	// Motor 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

	// Motor 3
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

	// Motor 4
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

	HAL_Delay(2000);
}

void stopMotors() {
	// Motor 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

	// Motor 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

	// Motor 3
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

	// Motor 4
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_Delay(1000);
}

void stopLeftMotors() {
	// Motor 1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

	// Motor 2
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_Delay(1000);
}

void stopRightMotors() {
	// Motor 3
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

	// Motor 4
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_Delay(1000);
}

void slowLeftMotors() {
	// Motor 1
	tim1->Instance->CCR2 = 250;

	// Motor 2
	tim3->Instance->CCR2 = 250;
	HAL_Delay(1000);
}

void slowRightMotors() {
	// Motor 3
	tim3->Instance->CCR4 = 250;

	// Motor 4
	tim3->Instance->CCR1 = 250;
	HAL_Delay(1000);
}

void speedLeftMotors() {
	// Motor 1
	tim1->Instance->CCR2 = 850;

	// Motor 2
	tim3->Instance->CCR2 = 850;
	HAL_Delay(1000);
}

void speedRightMotors() {
	// Motor 3
	tim3->Instance->CCR4 = 850;

	// Motor 4
	tim3->Instance->CCR1 = 850;
	HAL_Delay(1000);
}
