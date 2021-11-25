#include <main.h>
#include <servo.h>

TIM_HandleTypeDef *tim2;

void initServo(TIM_HandleTypeDef *htim2) {
	tim2 = htim2;
	HAL_TIM_PWM_Start(htim2, TIM_CHANNEL_1);
	tim2->Instance->CCR1 = 125;

}

void moveServo() {
	tim2->Instance->CCR1 = 75;
	HAL_Delay(2000);

	tim2->Instance->CCR1 = 150;
	HAL_Delay(2000);
}

void openServo() {
	tim2->Instance->CCR1 = 75;
	HAL_Delay(1000);
}

void closeServo() {
	tim2->Instance->CCR1 = 150;
	HAL_Delay(1000);
}

void startServo() {
	HAL_TIM_PWM_Start(tim2, TIM_CHANNEL_1);
}

void stopServo() {
	HAL_TIM_PWM_Stop(tim2, TIM_CHANNEL_1);
}
