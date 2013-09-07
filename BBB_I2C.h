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
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#define I2C_BUS 1

class BBB_I2C {
public:

    BBB_I2C();
    BBB_I2C(uint8_t busAddr);
    
    //Write Methods
    void writeBit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t data, int bitNum);
    void writeBitNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t data, int bitNum);
    void writeBits(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t data, int length, int startBit);
    void writeBitsNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t data, int length, int startBit);
    void writeByte(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t data);
    void writeByteNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t data);
    void writeByteBuffer(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t *data, uint8_t length);
    void writeByteBufferNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t *data, uint8_t length);
    void writeByteArduino(uint8_t DEV_ADD, int8_t data);
    void writeByteArduinoNoExit(uint8_t DEV_ADD, int8_t data);
    void writeByteBufferArduino(uint8_t DEV_ADD, uint8_t *data, uint8_t length);
    void writeByteBufferArduinoNoExit(uint8_t DEV_ADD, uint8_t *data, uint8_t length);
    
    //Read Methods
    uint8_t readBit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t bitNum);
    uint8_t readBitNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t bitNum);
    uint8_t readBits(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t length, uint8_t startBit);
    uint8_t readBitsNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t length, uint8_t startBit);
    uint8_t readByte(uint8_t DEV_ADD, uint8_t DATA_REGADD);
    uint8_t readByteNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD);
    void readByteBuffer(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t *data, uint8_t length);
    void readByteBufferNoExit(uint8_t DEV_ADD, uint8_t DATA_REGADD, uint8_t *data, uint8_t length);
    void readByteBufferArduino(uint8_t DEV_ADD, uint8_t *data, uint8_t length);
    void readByteBufferArduinoNoExit(uint8_t DEV_ADD, uint8_t *data, uint8_t length);
    int16_t readWord(uint8_t DEV_ADD, uint8_t MSB, uint8_t LSB);
    int16_t readWordNoExit(uint8_t DEV_ADD, uint8_t MSB, uint8_t LSB);

private:
    uint8_t busAddr;
};

#endif	/* BBB_I2C_H */

