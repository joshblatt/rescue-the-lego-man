#ifndef SERVO_H
#define SERVO_H

void initServo(TIM_HandleTypeDef *htim2);
void moveServo();
void openServo();
void closeServo();

#endif
