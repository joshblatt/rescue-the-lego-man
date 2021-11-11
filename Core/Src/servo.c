#include <main.h>
#include <servo.h>

#include "../../EUCAL/SERVO/SERVO.h"

#define SERVO_MOTOR 0

void servoInit() {
	SERVO_Init(SERVO_MOTOR);
}

void moveServo() {
    SERVO_MoveTo(SERVO_MOTOR, 0);
    HAL_Delay(1000);
    SERVO_MoveTo(SERVO_MOTOR, 45);
    HAL_Delay(500);
    SERVO_MoveTo(SERVO_MOTOR, 90);
    HAL_Delay(500);
    SERVO_MoveTo(SERVO_MOTOR, 135);
    HAL_Delay(500);
    SERVO_MoveTo(SERVO_MOTOR, 180);
    HAL_Delay(500);
    SERVO_MoveTo(SERVO_MOTOR, 90);
    HAL_Delay(1000);

}
