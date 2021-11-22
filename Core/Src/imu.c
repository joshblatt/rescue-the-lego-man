#include <main.h>
#include <imu.h>


// Device ID 0x69
#define ACCEL_GYRO_ADDR 0x69 << 1
#define ACCEL_XOUT_H_ADDR 0x2D
#define ACCEL_XOUT_L_ADDR 0x2E
#define ACCEL_YOUT_H_ADDR 0x2F
#define ACCEL_YOUT_L_ADDR 0x30
#define ACCEL_ZOUT_H_ADDR 0x31
#define ACCEL_ZOUT_L_ADDR 0x32

#define GYRO_XOUT_H_ADDR 0x33
#define GYRO_XOUT_L_ADDR 0x34
#define GYRO_YOUT_H_ADDR 0x35
#define GYRO_YOUT_L_ADDR 0x36
#define GYRO_ZOUT_H_ADDR 0x37
#define GYRO_ZOUT_L_ADDR 0x38

// Device Id 0x09
// Max - 0x7FF0 -> 4912
// 0x0001 -> 0.15
// Zero - 0x0000 -> 0
// 0xFFFF -> -0.15
// Min - 0x8010 -> -4912
#define MAG_ADDR 0x09 << 1
#define MAG_XOUT_L_ADDR 0x11
#define MAG_XOUT_H_ADDR 0x12
#define MAG_YOUT_L_ADDR 0x13
#define MAG_YOUT_H_ADDR 0x14
#define MAG_ZOUT_L_ADDR 0x15
#define MAG_ZOUT_H_ADDR 0x16



I2C_HandleTypeDef *i2c2;

void initImu(I2C_HandleTypeDef *hi2c2) {
	i2c2 = hi2c2;
}

void readGyro() {
	uint8_t buf[6] = {0};
	buf[0] = ACCEL_XOUT_H_ADDR;
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Master_Transmit(i2c2, ACCEL_GYRO_ADDR, buf, 1, HAL_MAX_DELAY);
//	if (ret != HAL_OK) {
//		return;
//	}
	HAL_Delay(20);
	ret = HAL_I2C_Master_Receive(i2c2, ACCEL_GYRO_ADDR, buf, 6, HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		return;
	}
	HAL_Delay(100);
}

void readAccel() {

}

void readMag() {

}
