/*
 * TestMPU6050.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: cagdas
 */
#include <stdio.h>
#include "MPU6050.h"

int main() {

	// First way
	BBB_I2C i2c(0x68, 1);
	MPU6050 mpu(i2c);

	//Second way
	//MPU6050 mpu;

	mpu.init();

	while (true) {
		printf("%d   %d   %d\n", mpu.getAccelerationX(), mpu.getAccelerationY(),
				mpu.getAccelerationZ());
	}

	return 0;
}

