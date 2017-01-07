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
using namespace cacaosd_mpu6050;

int ctrl;

int main() {

    ctrl = 1;
    signal(SIGINT, signal_handler);

    I2cPort *i2c = new I2cPort(0x68, 2);
    i2c->openConnection();

    MPU6050 *mpu6050 = new MPU6050(i2c);
    mpu6050->init();

    float k = 16000;

    while (ctrl) {
        std::cout << "MPU6050" << std::endl;
        std::cout << "Accel X: " << (float) mpu6050->getAccelerationX() / k << std::endl;
        std::cout << "Accel Y: " << (float) mpu6050->getAccelerationY() / k << std::endl;
        std::cout << "Accel Z: " << (float) mpu6050->getAccelerationZ() / k << std::endl;
        std::cout << "----------------------" << std::endl;
        usleep(200000);
    }

    delete i2c, mpu6050;

    return 0;
}

