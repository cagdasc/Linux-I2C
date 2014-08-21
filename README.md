BeagleBoneBlack-I2C
===================

BeagleBone Black I2C Library

This library is about I2C communication for BeagleBone Black. It tested on Ubuntu 14.04 and work fine. It has some functions to work with Arduino UNO R3. I am working on MPU6050, ADXL345, HMC5883L chip for implement I2C library. You can find Arduino, MPU6050,ADXL345 and HMC5883L test example. I2C library is experimental so there is no warranty. It's basic and I am working for developing. If there is a some problem or some additional for this library, you can share me.

While I write this library, I inpired from [i2cdevlib](https://github.com/jrowberg/i2cdevlib) library.

This library has specific methods for Arduino. You can communicate with Arduino easily. You can find Arduino side code in "Arduino" folder.
"NoExit" suffix was removed. If connection could not be established, the program is terminated but if there is a problem occur while data streaming, program not terminated.

#Usage
    make clean
    make all
    ./Test...

#License

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
