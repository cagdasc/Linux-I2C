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
#include "BBB_I2C.h"

#define DEV_ADD 0x21
#define I2C_BUS 1
using namespace cacaosd_bbb_i2c;


int main(int argc, char **argv) {

	BBB_I2C i2c(DEV_ADD, I2C_BUS);

	int8_t data = 44;
	uint8_t *dataArray;

	dataArray = (uint8_t*) calloc(3, sizeof(uint8_t));
	dataArray[0] = 11;
	dataArray[1] = 12;
	dataArray[2] = 13;

//	while (true)
//		i2c.writeByteArduinoNoExit(data);

	while (true)
		i2c.writeByteBufferArduinoNoExit(dataArray, 3);

}

