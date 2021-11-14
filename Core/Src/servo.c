#include <main.h>
#include <servo.h>

void moveServo(TIM_HandleTypeDef *htim2) {
	htim2->Instance->CCR2 = 75;
	HAL_Delay(2000);

	htim2->Instance->CCR2 = 150;
	HAL_Delay(2000);
}

void openServo(TIM_HandleTypeDef *htim2) {
	htim2->Instance->CCR2 = 75;
	HAL_Delay(1000);
}

void closeServo(TIM_HandleTypeDef *htim2) {
	htim2->Instance->CCR2 = 150;
	HAL_Delay(1000);
}
