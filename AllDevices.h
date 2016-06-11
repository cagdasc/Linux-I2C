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

#endif /*ALLDEVICES_H*/
