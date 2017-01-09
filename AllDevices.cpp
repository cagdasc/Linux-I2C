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
using namespace cacaosd_hmc5883l;
using namespace cacaosd_adxl345;

int ctrl;

int main() {
    ctrl = 1;

    signal(SIGINT, signal_handler);
    I2cPort *i2c0 = new I2cPort(0x69, 2);
    i2c0->openConnection();

    I2cPort *i2c1 = new I2cPort(0x1E, 2);
    i2c1->openConnection();

    I2cPort *i2c2 = new I2cPort(0x53, 2);
    i2c2->openConnection();

    MPU6050 *mpu6050 = new MPU6050(i2c0);
    HMC5883L *hmc5883L = new HMC5883L(i2c1);
    ADXL345 *adxl345 = new ADXL345(i2c2);

    //Initialize devices
    if (i2c0->isConnectionOpen()) {
        mpu6050->initialize();
    } else {
        exit(1);
    }

    if (i2c1->isConnectionOpen()) {
        hmc5883L->initialize();
    } else {
        exit(1);
    }

    if (i2c2->isConnectionOpen()) {
        adxl345->initialize();
    } else {
        exit(1);
    }

    float k = 16000;

    while (ctrl) {
        std::cout << "MPU6050" << std::endl;
        std::cout << "Accel X: " << (float) mpu6050->getAccelerationX() / k << std::endl;
        std::cout << "Accel Y: " << (float) mpu6050->getAccelerationY() / k << std::endl;
        std::cout << "Accel Z: " << (float) mpu6050->getAccelerationZ() / k << std::endl;
        std::cout << "Gyro X: " << (float) mpu6050->getAccelerationX() / k << std::endl;
        std::cout << "Gyro Y: " << (float) mpu6050->getAccelerationY() / k << std::endl;
        std::cout << "Gyro Z: " << (float) mpu6050->getAccelerationZ() / k << std::endl;
        std::cout << "----------------------" << std::endl;

        usleep(20000);
        std::cout << "HMC5883L" << std::endl;
        std::cout << "Mag X: " << hmc5883L->getMagnitudeX() << std::endl;
        std::cout << "Mag Y: " << hmc5883L->getMagnitudeY() << std::endl;
        std::cout << "Mag Z: " << hmc5883L->getMagnitudeZ() << std::endl;
        std::cout << "----------------------" << std::endl;


        usleep(20000);
        std::cout << "ADXL345" << std::endl;
        std::cout << "Raw Accel X: " << adxl345->getAccelerationX() << std::endl;
        std::cout << "Raw Accel Y: " << adxl345->getAccelerationY() << std::endl;
        std::cout << "Raw Accel Z: " << adxl345->getAccelerationZ() << std::endl;
        std::cout << "----------------------" << std::endl;
        usleep(200000);
    }

    delete i2c0, i2c1, i2c2;
    delete mpu6050, hmc5883L, adxl345;

    return 0;

}

