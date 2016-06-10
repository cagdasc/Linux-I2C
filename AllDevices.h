//
// Created by cagdas on 10.06.2016.
//

#ifndef ALLDEVICES_H
#define ALLDEVICES_H
#include <csignal>
#include <iostream>
#include "MPU6050.h"
#include "HMC5883L.h"
#include "ADXL345.h"

extern int ctrl;

void signal_handler(int signal) {
    std::cout << "Interrupt signal "<< signal <<" received." << std::endl;
    ctrl = 0;
    exit(signal);
}

#endif ALLDEVICES_H
