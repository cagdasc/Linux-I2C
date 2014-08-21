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
#include "ADXL345.h"
using namespace cacaosd_bbb_i2c;
using namespace cacaosd_adxl345;

int main(int argc, char **argv) {

	BBB_I2C i2c;
	ADXL345 adxl(i2c);
	adxl.initialize();

	while (true) {
		printf("Raw Accel X: %d\n", adxl.getAccelerationX());
		printf("Raw Accel Y: %d\n", adxl.getAccelerationY());
		printf("Raw Accel Z: %d\n", adxl.getAccelerationZ());
		printf("-------------------\n");

		usleep(200000);
	}
	return 0;
}

