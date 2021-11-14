#ifndef SERVO_H
#define SERVO_H

void moveServo(TIM_HandleTypeDef *htim2);
void openServo(TIM_HandleTypeDef *htim2);
void closeServo(TIM_HandleTypeDef *htim2);

#endif
