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

#ifndef BBB_I2C_H
#define	BBB_I2C_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#define I2C_BUS 1
#define PATH_SIZE 15

class BBB_I2C {
public:

	BBB_I2C();
	BBB_I2C(uint8_t DEV_ADD);
	BBB_I2C(uint8_t DEV_ADD, uint8_t busAddr);
	~BBB_I2C();

	int openConnection();
	void setBusAddress(uint8_t busAddr);

	//Write Methods
	void writeBit(uint8_t DATA_REGADD, uint8_t data, uint8_t bitNum);
	void writeBitNoExit(uint8_t DATA_REGADD, uint8_t data, uint8_t bitNum);
	void writeMoreBits(uint8_t DATA_REGADD, uint8_t data, uint8_t length,
			uint8_t startBit);
	void writeMoreBitsNoExit(uint8_t DATA_REGADD, uint8_t data, uint8_t length,
			uint8_t startBit);
	void writeByte(uint8_t DATA_REGADD, uint8_t data);
	void writeByteNoExit(uint8_t DATA_REGADD, uint8_t data);
	void writeByteBuffer(uint8_t DATA_REGADD, uint8_t *data, uint8_t length);
	void writeByteBufferNoExit(uint8_t DATA_REGADD, uint8_t *data,
			uint8_t length);
	void writeByteArduino(int8_t data);
	void writeByteArduinoNoExit(int8_t data);
	void writeByteBufferArduino(uint8_t *data, uint8_t length);
	void writeByteBufferArduinoNoExit(uint8_t *data, uint8_t length);

	//Read Methods
	uint8_t readBit(uint8_t DATA_REGADD, uint8_t bitNum);
	uint8_t readBitNoExit(uint8_t DATA_REGADD, uint8_t bitNum);
	uint8_t readMoreBits(uint8_t DATA_REGADD, uint8_t length, uint8_t startBit);
	uint8_t readMoreBitsNoExit(uint8_t DATA_REGADD, uint8_t length,
			uint8_t startBit);
	uint8_t readByte(uint8_t DATA_REGADD);
	uint8_t readByteNoExit(uint8_t DATA_REGADD);
	void readByteBuffer(uint8_t DATA_REGADD, uint8_t *data, uint8_t length);
	void readByteBufferNoExit(uint8_t DATA_REGADD, uint8_t *data,
			uint8_t length);
	void readByteBufferArduino(uint8_t *data, uint8_t length);
	void readByteBufferArduinoNoExit(uint8_t *data, uint8_t length);
	int16_t readWord(uint8_t MSB, uint8_t LSB);
	int16_t readWordNoExit(uint8_t MSB, uint8_t LSB);

	void setDEV_ADD(uint8_t DEV_ADD);

private:
	uint8_t busAddr;
	uint8_t DEV_ADD;
	char *path;

};

#endif	/* BBB_I2C_H */

