/* 
 * File:   BBB_I2C.h
 * Author: Cagdas Caglak
 * E-mail: cagdascaglak@gmail.com
 * Code is free but There is not warranty.
 * Created on July 26, 2013, 5:01 PM
 */

#ifndef BBB_I2C_H
#define	BBB_I2C_H

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
    BBB_I2C();
    BBB_I2C(const BBB_I2C& orig);
    virtual ~BBB_I2C();
    
    void writeBit(char DEV_ADD, char DATA_REGADD, char value, int bitNum, int bus);
    void writeBitNoExit(char DEV_ADD, char DATA_REGADD, char value, int bitNum, int bus);
    void writeByte(char DEV_ADD, char DATA_REGADD, char value, int bus);
    void writeByteNoExit(char DEV_ADD, char DATA_REGADD, char value, int bus);
    void writeByteBuffer(char DEV_ADD, char DATA_REGADD, uint8_t *value, uint8_t length, int bus);
    void writeByteBufferNoExit(char DEV_ADD, char DATA_REGADD, uint8_t *value, uint8_t length, int bus);
    void writeByteArduino(char DEV_ADD, int8_t value, int bus);
    void writeByteArduinoNoExit(char DEV_ADD, int8_t value, int bus);
    void writeByteBufferArduino(char DEV_ADD, uint8_t *value, uint8_t buff_len, int bus);
    void writeByteBufferArduinoNoExit(char DEV_ADD, uint8_t *value, uint8_t buff_len, int bus);
    
    uint8_t readBit(char DEV_ADD, char DATA_REGADD, uint8_t bitNum, int bus);
    uint8_t readBitNoExit(char DEV_ADD, char DATA_REGADD, uint8_t bitNum, int bus);
    int8_t readByte(char DEV_ADD, char DATA_REGADD, int bus);
    int8_t readByteNoExit(char DEV_ADD, char DATA_REGADD, int bus);
    void readByteBuffer(char DEV_ADD, char DATA_REGADD, uint8_t *data, uint8_t length, int bus);
    void readByteBufferNoExit(char DEV_ADD, char DATA_REGADD, uint8_t *data, uint8_t length, int bus);
    void readByteBufferArduino(char DEV_ADD,uint8_t *data, uint8_t length, int bus);
    void readByteBufferArduinoNoExit(char DEV_ADD,uint8_t *data, uint8_t length, int bus);
    int16_t readWord(char DEV_ADD, uint8_t MSB, uint8_t LSB, int bus);
    int16_t readWordNoExit(char DEV_ADD, uint8_t MSB, uint8_t LSB, int bus);

private:

};

#endif	/* BBB_I2C_H */

