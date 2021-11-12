#include <main.h>
#include <servo.h>

//#include "../../EUCAL/SERVO/SERVO.h"

//#define SERVO_MOTOR 0

void servoInit() {
//	SERVO_Init(SERVO_MOTOR);
}

void changeDutyCycle(TIM_HandleTypeDef *htim2, uint32_t pulse) {
	TIM_OC_InitTypeDef sConfigOC = {0};
	  sConfigOC.OCMode = TIM_OCMODE_PWM1;
	  sConfigOC.Pulse = pulse;
	  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	  if (HAL_TIM_PWM_ConfigChannel(htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

void moveServo(TIM_HandleTypeDef *htim2) {
	htim2->Instance->CCR2 = 75;
	HAL_Delay(2000);

	htim2->Instance->CCR2 = 150;
	HAL_Delay(2000);
}
