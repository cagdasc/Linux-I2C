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
#include <stdio.h>
#include "MPU6050.h"

using namespace cacaosd_bbb_i2c;
using namespace cacaosd_mpu6050;

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

