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

#include "AllDevices.h"

using namespace cacaosd_bbb_i2c;
using namespace cacaosd_hmc5883l;

int ctrl;

int main() {

	ctrl = 1;
	signal(SIGINT, signal_handler);

	BBB_I2C *i2c = new BBB_I2C(HMC5883L_DEV_ADD, 2);
	i2c->openConnection();

	HMC5883L *hmc5883L = new HMC5883L(i2c);
	hmc5883L->initialize();

	while (ctrl) {
		std::cout << "HMC5883L" << std::endl;
		std::cout << "Mag X: " << hmc5883L->getMagnitudeX() << std::endl;
		std::cout << "Mag Y: " << hmc5883L->getMagnitudeY() << std::endl;
		std::cout << "Mag Z: " << hmc5883L->getMagnitudeZ() << std::endl;
		std::cout << "----------------------" << std::endl;
		usleep(200000);
	}

	delete i2c, hmc5883L;
	return 0;
}

