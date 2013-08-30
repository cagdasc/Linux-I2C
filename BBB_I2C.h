/* 
 * File:   BBB_I2C.h
 * Author: Cagdas Caglak
 * E-mail: cagdascaglak@gmail.com
 * Code is free but There is not warranty.
 * Created on July 26, 2013, 5:01 PM
 */

#ifndef BBB_I2C_H
#define	BBB_I2C_H

#include <math.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

class BBB_I2C {
public:

    void writeBit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t value, int bitNum, int bus);
    void writeBitNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t value, int bitNum, int bus);
    void writeBitsNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t value, int length, int startBit, int bus);
    void writeByte(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t value, int bus);
    void writeByteNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t value, int bus);
    void writeByteBuffer(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t *value, uint8_t length, int bus);
    void writeByteBufferNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t *value, uint8_t length, int bus);
    void writeByteArduino(uint8_t DEV_ADD, int8_t value, int bus);
    void writeByteArduinoNoExit(uint8_t DEV_ADD, int8_t value, int bus);
    void writeByteBufferArduino(uint8_t DEV_ADD, uint8_t *value, uint8_t length, int bus);
    void writeByteBufferArduinoNoExit(uint8_t DEV_ADD, uint8_t *value, uint8_t length, int bus);

    uint8_t readBit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t bitNum, int bus);
    uint8_t readBitNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t bitNum, int bus);
    uint8_t readBitsNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t length, uint8_t startBit, int bus);
    uint8_t readByte(uint8_t DEV_ADD, uint8_t DATA_REGADD, int bus);
    uint8_t readByteNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, int bus);
    void readByteBuffer(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t *data, uint8_t length, int bus);
    void readByteBufferNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t *data, uint8_t length, int bus);
    void readByteBufferArduino(uint8_t DEV_ADD, uint8_t *data, uint8_t length, int bus);
    void readByteBufferArduinoNoExit(uint8_t DEV_ADD, uint8_t *data, uint8_t length, int bus);
    int16_t readWord(uint8_t DEV_ADD, uint8_t MSB, uint8_t LSB, int bus);
    int16_t readWordNoExit(uint8_t DEV_ADD, uint8_t MSB, uint8_t LSB, int bus);

private:

};

#endif	/* BBB_I2C_H */

