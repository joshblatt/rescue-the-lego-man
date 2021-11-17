#ifndef IMU_H
#define IMU_H

void readGyro(I2C_HandleTypeDef *hi2c2);
void readAccel(I2C_HandleTypeDef *hi2c2);
void readMag(I2C_HandleTypeDef *hi2c2);

#endif
