#include <main.h>
#include <imu.h>


// Device ID 0xEA
#define ACCEL_GYRO_ADDR 0xEA << 1
#define ACCEL_XOUT_H_ADDR 0x2D << 1
#define ACCEL_XOUT_L_ADDR 0x2E << 1
#define ACCEL_YOUT_H_ADDR 0x2F << 1
#define ACCEL_YOUT_L_ADDR 0x30 << 1
#define ACCEL_ZOUT_H_ADDR 0x31 << 1
#define ACCEL_ZOUT_L_ADDR 0x32 << 1

#define GYRO_XOUT_H_ADDR 0x33 << 1
#define GYRO_XOUT_L_ADDR 0x34 << 1
#define GYRO_YOUT_H_ADDR 0x35 << 1
#define GYRO_YOUT_L_ADDR 0x36 << 1
#define GYRO_ZOUT_H_ADDR 0x37 << 1
#define GYRO_ZOUT_L_ADDR 0x38 << 1

// Device Id 0x09
// Max - 0x7FF0 -> 4912
// 0x0001 -> 0.15
// Zero - 0x0000 -> 0
// 0xFFFF -> -0.15
// Min - 0x8010 -> -4912
#define MAG_ADDR 0x09 << 1
#define MAG_XOUT_L_ADDR 0x11 << 1
#define MAG_XOUT_H_ADDR 0x12 << 1
#define MAG_YOUT_L_ADDR 0x13 << 1
#define MAG_YOUT_H_ADDR 0x14 << 1
#define MAG_ZOUT_L_ADDR 0x15 << 1
#define MAG_ZOUT_H_ADDR 0x16 << 1

uint8_t buf[6];

void readGyro(I2C_HandleTypeDef *hi2c2) {
	buf[0] = ACCEL_XOUT_H_ADDR;
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Master_Transmit(hi2c2, ACCEL_GYRO_ADDR, buf, 1 , HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		return;
	}

	ret = HAL_I2C_Master_Receive(hi2c2, ACCEL_GYRO_ADDR, buf, 6, HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		return;
	}
	HAL_Delay(100);
}

void readAccel(I2C_HandleTypeDef *hi2c2) {

}

void readMag(I2C_HandleTypeDef *hi2c2) {

}
