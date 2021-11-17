#ifndef TEST_H
#define TEST_H

#include <main.h>

void testColourSensor(UART_HandleTypeDef *huart1, UART_HandleTypeDef *huart6, TIM_HandleTypeDef *htim2);
void testMotors();
void testServo(TIM_HandleTypeDef *htim2);

#endif
