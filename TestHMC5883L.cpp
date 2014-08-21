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
#include <stdlib.h>
#include "HMC5883L.h"

using namespace cacaosd_bbb_i2c;
using namespace cacaosd_hmc5883l;

int main(int argc, char **argv) {

	BBB_I2C i2c;
	HMC5883L hmc(i2c);
	hmc.initialize();

	while (true) {
		printf("Mag X: %d\n", hmc.getMagnitudeX());
		printf("Mag Y: %d\n", hmc.getMagnitudeY());
		printf("Mag Z: %d\n", hmc.getMagnitudeZ());
		printf("-------------\n");

		usleep(200000);
	}
	return 0;
}

