#ifndef MOTOR_H
#define MOTOR_H

#include <main.h>

void initMotors(TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim3, TIM_HandleTypeDef *htim4);
void moveMotors();
void moveForwards();
void moveBackwards();
void turnLeft();
void turnRight();
void stopMotors();
void stopLeftMotors();
void stopRightMotors();

#endif
