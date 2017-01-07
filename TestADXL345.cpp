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

using namespace cacaosd_i2cport;
using namespace cacaosd_adxl345;

int ctrl;

int main() {

    ctrl = 1;
    signal(SIGINT, signal_handler);

    I2cPort *i2c = new I2cPort(ADXL345_DEFAULT_ADDRESS, 2);
    i2c->openConnection();

    ADXL345 *adxl345 = new ADXL345(i2c);
    adxl345->initialize();

    while (ctrl) {
        std::cout << "ADXL345" << std::endl;
        std::cout << "Raw Accel X: " << adxl345->getAccelerationX() << std::endl;
        std::cout << "Raw Accel Y: " << adxl345->getAccelerationY() << std::endl;
        std::cout << "Raw Accel Z: " << adxl345->getAccelerationZ() << std::endl;
        std::cout << "----------------------" << std::endl;

        usleep(200000);
    }

    delete i2c, adxl345;

    return 0;
}

