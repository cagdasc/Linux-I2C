/*
 Copyright (C) 2014  Cagdas Caglak cagdascaglak@gmail.com http://expcodes.blogspot.com.tr/

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MPU6050.h"
namespace cacaosd_mpu6050 {

MPU6050::MPU6050(uint8_t DEV_ADD) :
		i2c(DEV_ADD, 1) {
	this->DEV_ADD = DEV_ADD;
}

MPU6050::MPU6050(BBB_I2C &i2c) :
		DEV_ADD(DEF_DEV_ADD) {
	this->i2c = i2c;
	this->i2c.setDEV_ADD(DEV_ADD);
}

MPU6050::~MPU6050() {
}

void MPU6050::setDeviceAddress(uint8_t DEV_ADD) {
	this->DEV_ADD = DEV_ADD;
}

uint8_t MPU6050::getDeviceAddress() {
	return this->DEV_ADD;
}

void MPU6050::setSleepMode(bool mode) {
	int8_t byte = i2c.readByteNoExit(PWR_MGMT_1);
	if (mode) {
		byte |= 64;
	} else {
		byte &= ~64;
	}
	i2c.writeByteNoExit(PWR_MGMT_1, byte);
}

bool MPU6050::getSleepMode() {
	int8_t byte = i2c.readByteNoExit(PWR_MGMT_1);
	byte >>= 6;
	byte %= 2;
	if (byte == 1) {
		return true;
	} else {
		return false;
	}
}

void MPU6050::setRangeAcceleration(uint8_t range) {
	uint8_t afs;
	afs = i2c.readByteNoExit(ACCEL_CONFIG);
	if (range == 0) {
		afs &= ~24;
	} else if (range == 1) {
		afs |= 8;
		afs &= ~16;
	} else if (range == 2) {
		afs &= ~8;
		afs |= 16;
	} else {
		afs |= 24;
	}
	i2c.writeByteNoExit(ACCEL_CONFIG, afs);
}

uint8_t MPU6050::getRangeAcceleration() {
	uint8_t afs;
	afs = i2c.readByteNoExit(ACCEL_CONFIG);
	afs >>= 3;
	afs %= 4;
	return afs;
}

void MPU6050::setRangeGyroscope(uint8_t range) {
	uint8_t fs;
	fs = i2c.readByteNoExit(GYRO_CONFIG);
	if (range == 0) {
		fs &= ~24;
	} else if (range == 1) {
		fs |= 8;
		fs &= ~16;
	} else if (range == 2) {
		fs &= ~8;
		fs |= 16;
	} else {
		fs |= 24;
	}
	i2c.writeByteNoExit(GYRO_CONFIG, fs);
}

uint8_t MPU6050::getRangeGyroscope() {
	uint8_t fs;
	fs = i2c.readByteNoExit(GYRO_CONFIG);
	fs >>= 3;
	fs %= 4;
	return fs;
}

void MPU6050::init() {
	setSleepMode(false);
	setRangeAcceleration(0);
	setRangeGyroscope(0);
}

void MPU6050::getAccelerations(int16_t *ax, int16_t *ay, int16_t *az) {

	*ax = i2c.readWordNoExit(ACCEL_XOUT_H, ACCEL_XOUT_L);
	*ay = i2c.readWordNoExit(ACCEL_YOUT_H, ACCEL_YOUT_L);
	*az = i2c.readWordNoExit(ACCEL_ZOUT_H, ACCEL_ZOUT_L);

}

int16_t MPU6050::getAccelerationX() {
	return i2c.readWordNoExit(ACCEL_XOUT_H, ACCEL_XOUT_L);
}

int16_t MPU6050::getAccelerationY() {
	return i2c.readWordNoExit(ACCEL_YOUT_H, ACCEL_YOUT_L);
}

int16_t MPU6050::getAccelerationZ() {
	return i2c.readWordNoExit(ACCEL_ZOUT_H, ACCEL_ZOUT_L);
}

void MPU6050::getAngularVelocities(int16_t* gx, int16_t* gy, int16_t* gz) {

	*gx = i2c.readWordNoExit(GYRO_XOUT_H, GYRO_XOUT_L);
	*gy = i2c.readWordNoExit(GYRO_YOUT_H, GYRO_YOUT_L);
	*gz = i2c.readWordNoExit(GYRO_ZOUT_H, GYRO_ZOUT_L);

}

int16_t MPU6050::getAngularVelocityX() {
	return i2c.readWordNoExit(GYRO_XOUT_H, GYRO_XOUT_L);
}

int16_t MPU6050::getAngularVelocityY() {
	return i2c.readWordNoExit(GYRO_YOUT_H, GYRO_YOUT_L);
}

int16_t MPU6050::getAngularVelocityZ() {
	return i2c.readWordNoExit(GYRO_ZOUT_H, GYRO_ZOUT_L);
}

int16_t MPU6050::getTemperature() {
	return i2c.readWordNoExit(TEMP_OUT_H, TEMP_OUT_L);
}

void MPU6050::getMotions6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx,
		int16_t* gy, int16_t* gz) {

	*ax = i2c.readWordNoExit(ACCEL_XOUT_H, ACCEL_XOUT_L);
	*ay = i2c.readWordNoExit(ACCEL_YOUT_H, ACCEL_YOUT_L);
	*az = i2c.readWordNoExit(ACCEL_ZOUT_H, ACCEL_ZOUT_L);

	*gx = i2c.readWordNoExit(GYRO_XOUT_H, GYRO_XOUT_L);
	*gy = i2c.readWordNoExit(GYRO_YOUT_H, GYRO_YOUT_L);
	*gz = i2c.readWordNoExit(GYRO_ZOUT_H, GYRO_ZOUT_L);

}

void MPU6050::setDLPFMode(uint8_t mode) {
	uint8_t config = i2c.readByteNoExit(CONFIG);
	if (mode == 0) {
		config = config & ~7;
	} else if (mode == 1) {
		config |= 1;
		config &= ~6;
	} else if (mode == 2) {
		config |= 2;
		config &= ~5;
	} else if (mode == 3) {
		config |= 3;
		config &= ~4;
	} else if (mode == 4) {
		config |= 4;
		config &= ~3;
	} else if (mode == 5) {
		config |= 5;
		config &= ~2;
	} else if (mode == 6) {
		config |= 6;
		config &= ~1;
	} else if (mode == 7) {
		config |= 7;
	}

	i2c.writeByteNoExit(CONFIG, config);
}

uint8_t MPU6050::getDLPFMode() {
	uint8_t config = i2c.readByteNoExit(CONFIG);
	return config % 8;
}

void MPU6050::setSampleRate(uint8_t rate) {
	i2c.writeByteNoExit(SMPLRT_DIV, rate);
}

uint8_t MPU6050::getSampleRate() {
	return i2c.readByteNoExit(SMPLRT_DIV);
}

void MPU6050::setMotionDetectionThresold(uint8_t value) {
	i2c.writeByteNoExit(MOT_THR, value);
}

uint8_t MPU6050::getMotionDetectionThresold() {
	return i2c.readByteNoExit(MOT_THR);
}

void MPU6050::setTEMP_FIFO_EN(uint8_t value) {
	i2c.writeBitNoExit(FIFO_EN, value, TEMP_FIFO_EN_BIT);
}

uint8_t MPU6050::getTEMP_FIFO_EN() {
	return i2c.readBitNoExit(FIFO_EN, TEMP_FIFO_EN_BIT);
}

void MPU6050::setXG_FIFO_EN(uint8_t value) {
	i2c.writeBitNoExit(FIFO_EN, value, XG_FIFO_EN_BIT);
}

uint8_t MPU6050::getXG_FIFO_EN() {
	return i2c.readBitNoExit(FIFO_EN, XG_FIFO_EN_BIT);
}

void MPU6050::setYG_FIFO_EN(uint8_t value) {
	i2c.writeBitNoExit(FIFO_EN, value, YG_FIFO_EN_BIT);
}

uint8_t MPU6050::getYG_FIFO_EN() {
	return i2c.readBitNoExit(FIFO_EN, YG_FIFO_EN_BIT);
}

void MPU6050::setZG_FIFO_EN(uint8_t value) {
	i2c.writeBitNoExit(FIFO_EN, value, ZG_FIFO_EN_BIT);
}

uint8_t MPU6050::getZG_FIFO_EN() {
	return i2c.readBitNoExit(FIFO_EN, ZG_FIFO_EN_BIT);
}

void MPU6050::setACCEL_FIFO_EN(uint8_t value) {
	i2c.writeBitNoExit(FIFO_EN, value, ACCEL_FIFO_EN_BIT);
}

uint8_t MPU6050::getACCEL_FIFO_EN() {
	return i2c.readBitNoExit(FIFO_EN, ACCEL_FIFO_EN_BIT);
}

void MPU6050::setSLV2_FIFO_EN(uint8_t value) {
	i2c.writeBitNoExit(FIFO_EN, value, SLV2_FIFO_EN_BIT);
}

uint8_t MPU6050::getSLV2_FIFO_EN() {
	return i2c.readBitNoExit(FIFO_EN, SLV2_FIFO_EN_BIT);
}

void MPU6050::setSLV1_FIFO_EN(uint8_t value) {
	i2c.writeBitNoExit(FIFO_EN, value, SLV1_FIFO_EN_BIT);
}

uint8_t MPU6050::getSLV1_FIFO_EN() {
	return i2c.readBitNoExit(FIFO_EN, SLV1_FIFO_EN_BIT);
}

void MPU6050::setSLV0_FIFO_EN(uint8_t value) {
	i2c.writeBitNoExit(FIFO_EN, value, SLV0_FIFO_EN_BIT);
}

uint8_t MPU6050::getSLV0_FIFO_EN() {
	return i2c.readBitNoExit(FIFO_EN, SLV0_FIFO_EN_BIT);
}

uint16_t MPU6050::getFIFO_Count() {
	return i2c.readWordNoExit(FIFO_COUNTH, FIFO_COUNTL);
}

void MPU6050::setFIFO_Enable(uint8_t value) {
	i2c.writeBitNoExit(USER_CTRL, value, FIFO_EN_BIT);
}

uint8_t MPU6050::getFIFO_Enable() {
	return i2c.readBitNoExit(USER_CTRL, FIFO_EN_BIT);
}

void MPU6050::getFIFO_Data(uint8_t *data, uint8_t length) {
	i2c.readByteBufferNoExit(FIFO_R_W, data, length);
}

void MPU6050::setFIFO_Reset(uint8_t value) {
	i2c.writeBitNoExit(USER_CTRL, value, FIFO_RESET_BIT);
}

uint8_t MPU6050::getFIFO_Reset() {
	return i2c.readBitNoExit(USER_CTRL, FIFO_RESET_BIT);
}

}  // namespace cacaosd_mpu6050
