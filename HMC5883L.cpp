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

#include "HMC5883L.h"

namespace cacaosd_hmc5883l {

HMC5883L::HMC5883L(uint8_t DEV_ADD) :
		i2c(DEV_ADD, I2C_BUS) {
	this->DEV_ADD = DEV_ADD;
}

HMC5883L::HMC5883L(BBB_I2C &i2c) :
		DEV_ADD(DEF_DEV_ADD) {
	this->i2c = i2c;
	this->i2c.setDEV_ADD(DEV_ADD);
}
HMC5883L::~HMC5883L() {
}

void HMC5883L::initialize() {
	setSamplesAvarage(SAMPLES_AVARAGE_8);
	setOutputRate(OUTPUT_RATE_4);
	setMeasurementMode(MEASUREMENT_NORMAL);
	setMeasurementGain(GAIN_1090);
	setOperationMode(OPERATION_MODE_CONT);
}

void HMC5883L::setSamplesAvarage(uint8_t avarage) {
	if (avarage == 0) {
		i2c.writeMoreBits(CONFIG_A, SAMPLES_AVARAGE_1,
		SAMPLES_AVARAGE_LENGTH, SAMPLES_AVARAGE_START);
	} else if (avarage == 1) {
		i2c.writeMoreBits(CONFIG_A, SAMPLES_AVARAGE_2,
		SAMPLES_AVARAGE_LENGTH, SAMPLES_AVARAGE_START);
	} else if (avarage == 2) {
		i2c.writeMoreBits(CONFIG_A, SAMPLES_AVARAGE_4,
		SAMPLES_AVARAGE_LENGTH, SAMPLES_AVARAGE_START);
	} else if (avarage == 3) {
		i2c.writeMoreBits(CONFIG_A, SAMPLES_AVARAGE_8,
		SAMPLES_AVARAGE_LENGTH, SAMPLES_AVARAGE_START);
	}
}

uint8_t HMC5883L::getSamplesAvarage() {
	return i2c.readMoreBits(CONFIG_A, SAMPLES_AVARAGE_LENGTH,
	SAMPLES_AVARAGE_START);
}

void HMC5883L::setOutputRate(uint8_t rate) {
	if (rate == 0) {
		i2c.writeMoreBits(CONFIG_A, OUTPUT_RATE_0,
		OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
	} else if (rate == 1) {
		i2c.writeMoreBits(CONFIG_A, OUTPUT_RATE_1,
		OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
	} else if (rate == 2) {
		i2c.writeMoreBits(CONFIG_A, OUTPUT_RATE_2,
		OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
	} else if (rate == 3) {
		i2c.writeMoreBits(CONFIG_A, OUTPUT_RATE_3,
		OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
	} else if (rate == 4) {
		i2c.writeMoreBits(CONFIG_A, OUTPUT_RATE_4,
		OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
	} else if (rate == 5) {
		i2c.writeMoreBits(CONFIG_A, OUTPUT_RATE_5,
		OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
	} else if (rate == 6) {
		i2c.writeMoreBits(CONFIG_A, OUTPUT_RATE_6,
		OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
	} else if (rate == 7) {
		printf("Reserved.\n");
	}
}

uint8_t HMC5883L::getOutputRate() {
	return i2c.readMoreBits(CONFIG_A, OUTPUT_RATE_LENGTH,
	OUTPUT_RATE_START);
}

void HMC5883L::setMeasurementMode(uint8_t mode) {
	if (mode == 0) {
		i2c.writeMoreBits(CONFIG_A, MEASUREMENT_NORMAL,
		MEASUREMENT_LENGTH, MEASUREMENT_START);
	} else if (mode == 2) {
		i2c.writeMoreBits(CONFIG_A, MEASUREMENT_POSITIVE,
		MEASUREMENT_LENGTH, MEASUREMENT_START);
	} else if (mode == 3) {
		i2c.writeMoreBits(CONFIG_A, MEASUREMENT_NEGATIVE,
		MEASUREMENT_LENGTH, MEASUREMENT_START);
	}
}

uint8_t HMC5883L::getMeasurementMode() {
	return i2c.readMoreBits(CONFIG_A, MEASUREMENT_LENGTH,
	MEASUREMENT_START);
}

void HMC5883L::setMeasurementGain(uint8_t gain) {
	if (gain == 0) {
		i2c.writeByte(CONFIG_B, (GAIN_1370 << 5));
	} else if (gain == 1) {
		i2c.writeByte(CONFIG_B, (GAIN_1090 << 5));
	} else if (gain == 2) {
		i2c.writeByte(CONFIG_B, (GAIN_820 << 5));
	} else if (gain == 3) {
		i2c.writeByte(CONFIG_B, (GAIN_660 << 5));
	} else if (gain == 4) {
		i2c.writeByte(CONFIG_B, (GAIN_440 << 5));
	} else if (gain == 5) {
		i2c.writeByte(CONFIG_B, (GAIN_390 << 5));
	} else if (gain == 6) {
		i2c.writeByte(CONFIG_B, (GAIN_330 << 5));
	} else if (gain == 7) {
		i2c.writeByte(CONFIG_B, (GAIN_230 << 5));
	}
}

uint8_t HMC5883L::getMeasurementGain() {
	return i2c.readMoreBits(CONFIG_B, GAIN_LENGTH, GAIN_START);
}

void HMC5883L::setOperationMode(uint8_t mode) {
	if (mode == 0) {
		i2c.writeByte(MODE_REG, OPERATION_MODE_CONT);
	} else if (mode == 1) {
		i2c.writeByte(MODE_REG, OPERATION_MODE_SINGLE);
	} else if (mode == 2) {
		i2c.writeByte(MODE_REG, OPERATION_MODE_IDLE);
	}
}

uint8_t HMC5883L::getOperationMode() {
	return i2c.readMoreBits(MODE_REG, OPERATION_MODE_LENGTH,
	OPERATION_MODE_START);
}

int16_t HMC5883L::getMagnitudeX() {
	return i2c.readWord(X_HIGH, X_LOW);
}

int16_t HMC5883L::getMagnitudeY() {
	return i2c.readWord(Y_HIGH, Y_LOW);
}

int16_t HMC5883L::getMagnitudeZ() {
	return i2c.readWord(Z_HIGH, Z_LOW);
}

uint8_t HMC5883L::getRDYStatus() {
	return i2c.readBit(STATUS_REG, RDY_BIT);
}

uint8_t HMC5883L::getLockStatus() {
	return i2c.readBit(STATUS_REG, LOCK_BIT);
}

}  // namespace cacaosd_hmc5883l
