Linux-I2C
===================

Linux I2C Library

This library is about I2C communication for Linux based systems. 
It was tested on BeagleBone Black Ubuntu 16.04 with g++-4.8 and works fine. 
Library has functions to work with Arduino UNO R3. 
I am working on MPU6050, ADXL345, HMC5883L chip for implement I2C library. 
You can find Arduino, MPU6050,ADXL345 and HMC5883L test example. 
I2C library is experimental so there is no warranty. 
It's basic and I am working for developing. 
If there is a some problem or some additional for this library, you can open an issue.

While I write this library, I inspired from [i2cdevlib](https://github.com/jrowberg/i2cdevlib) library.

#Usage
    $ mkdir build/
    $ cd build/
    $ cmake ..
    $ make all

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
