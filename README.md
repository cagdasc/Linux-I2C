<<<<<<< HEAD
   This code was written for my own project by me. I tried this code on BeagleBone Black Ubuntu 12.10. It's work with Arduino UNO R3 and MPU6050 6 axis Accelerometer and Gyroscope. I2C library is experimental so there is no warranty. It's basic and I am working for developing. If there is a some problem or some additional for this library, you can share me.
=======
BeagleBoneBlack-I2C
===================

BeagleBone Black I2C Library
   
   This code was written for my own project by me. I tried this code on BeagleBone Black Ubuntu 12.10. It's work with Arduino UNO R3. I2C library is experimental so there is no warranty. It's basic and I am working for developing. If there is a some problem or some additional for this library, you can share me.
>>>>>>> 32c76c8de0cbefcf75eacf7b997f55fa2d2a87c6

03/08/2013 ..NoExit() methods add the BBB_I2C library and so loops can not break to use I2C communication. 
23/08/2013 add writeBitsNoExit(..) and readBitsNoExit(..) for multiple  bits process.
24/08/2013 changed return type to readByte(..) and readByteNoExit(..). reorganization readWord(..) and readWordNoExit(..).
07/09/2013 added constructor methods for changed to i2c bus.(busAddr)
