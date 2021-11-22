#ifndef IMU_H
#define IMU_H

void initImu(I2C_HandleTypeDef *hi2c2);
void readGyro();
void readAccel();
void readMag();

#endif
