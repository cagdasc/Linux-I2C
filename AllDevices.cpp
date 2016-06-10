//
// Created by cagdas on 10.06.2016.
//
#include "AllDevices.h"

using namespace cacaosd_bbb_i2c;
using namespace cacaosd_mpu6050;
using namespace cacaosd_hmc5883l;
using namespace cacaosd_adxl345;

int ctrl;

int main() {
    ctrl = 1;

    signal(SIGINT, signal_handler);
    BBB_I2C *i2c0 = new BBB_I2C(0x69, 2);
    i2c0->openConnection();

    BBB_I2C *i2c1 = new BBB_I2C(0x1E, 2);
    i2c1->openConnection();

    BBB_I2C *i2c2 = new BBB_I2C(0x53, 2);
    i2c2->openConnection();

    MPU6050 *mpu6050 = new MPU6050(i2c0);
    HMC5883L *hmc5883L = new HMC5883L(i2c1);
    ADXL345 *adxl345 = new ADXL345(i2c2);

    //Initialize devices
    mpu6050->init();

    hmc5883L->initialize();

    adxl345->initialize();

    float k = 16000;

    while (ctrl) {
        std::cout << "MPU6050" << std::endl;
        std::cout << "Accel X: " << (float) mpu6050->getAccelerationX() / k << std::endl;
        std::cout << "Accel Y: " << (float) mpu6050->getAccelerationY() / k << std::endl;
        std::cout << "Accel Z: " << (float) mpu6050->getAccelerationZ() / k << std::endl;
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

