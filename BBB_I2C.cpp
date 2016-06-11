/*
 Copyright (C) 2014  Cagdas Caglak http://expcodes.blogspot.com.tr/

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

#include "BBB_I2C.h"

namespace cacaosd_bbb_i2c {

/**
 * @funtion BBB_I2C(uint8_t bus_addr)
 * @param bus_addr I2C Bus address.
 */
    BBB_I2C::BBB_I2C(uint8_t busAddr) {
        this->connection_open = false;
        this->bus_addr = busAddr;
        this->path = (char *) calloc(PATH_SIZE, sizeof(char));
        sprintf(path, "/dev/i2c-%d", this->bus_addr);
    }

/**
 * @funtion BBB_I2C(uint8_t dev_addr, uint8_t bus_addr)
 * @param dev_addr Device Address
 * @param bus_addr I2C Bus address.
 */
    BBB_I2C::BBB_I2C(uint8_t dev_addr, uint8_t busAddr) {
        this->connection_open = false;
        this->bus_addr = busAddr;
        this->path = (char *) calloc(PATH_SIZE, sizeof(char));
        this->dev_addr = dev_addr;
        sprintf(path, "/dev/i2c-%d", this->bus_addr);
    }

/** Default Destructor
 * @funtion ~BBB_I2C()
 *
 */
    BBB_I2C::~BBB_I2C() {
        free(path);
        this->closeConnection();
    }

/**
 * @funtion setBusAddress(uint8_t bus_addr)
 * @param bus_addr I2C Bus address.
 */
    void BBB_I2C::setBusAddress(uint8_t busAddr) {
        free(path);
        this->bus_addr = busAddr;
        this->path = (char *) calloc(PATH_SIZE, sizeof(char));
        sprintf(path, "/dev/i2c-%d", this->bus_addr);
    }

/**
 * @funtion getBusAddress()
 * @return bus_addr I2C Bus address.
 */
    uint8_t BBB_I2C::getBusAddress() {
        return this->bus_addr;
    }

/**
 * @funtion setDevAddr(uint8_t dev_addr)
 * @param dev_addr Device Address
 */
    void BBB_I2C::setDevAddr(uint8_t dev_addr) {
        this->dev_addr = dev_addr;
    }

/**
 * @funtion getDevAddr()
 * @return dev_addr Device Address
 */
    uint8_t BBB_I2C::getDevAddr() {
        return this->dev_addr;
    }
/**
 * @function openConnection()
 * @return file type of int
 */
    void BBB_I2C::openConnection() {
        int file;

        if ((file = open(path, O_RDWR)) < 0) {
            msg_error("%s do not open. Address %d.", path, dev_addr);
            exit(1);
        }

        if (ioctl(file, I2C_SLAVE, dev_addr) < 0) {
            msg_error("Can not join I2C Bus. Address %d.", dev_addr);
            exit(1);
        }

        if (file < 0) {
            this->connection_open = false;
            msg_error("Connection was not established.");
            exit(1);
        }
        this->connection_open = true;
        this->file_descriptor = file;
    }

    void BBB_I2C::closeConnection() {
        this->connection_open = false;
        close(this->file_descriptor);
    }

/**
 * @function writeBit(uint8_t dev_addr, uint8_t DATA_REGADD, uint8_t data, int bitNum)
 * @param dev_addr Device Address.
 * @param DATA_REGADD Data Register Address.
 * @param data Writing data.
 * @param bitNum Bit Number for writing.
 * @return void.
 */
    void BBB_I2C::writeBit(uint8_t DATA_REGADD, uint8_t data, uint8_t bitNum) {
        int8_t temp = readByte(DATA_REGADD);
        if (data == 0) {
            temp = temp & ~(1 << bitNum);
        } else if (data == 1) {
            temp = temp | (1 << bitNum);
        } else {
            msg_warning("Value must be 0 or 1! --> Address %d.", dev_addr);
        }

        writeByte(DATA_REGADD, temp);

    }

/**
 * @function writeBits(uint8_t dev_addr, uint8_t DATA_REGADD, uint8_t data, int length, int startBit)
 * @param dev_addr Device Address.
 * @param DATA_REGADD Data Register Address.
 * @param length Bits length.
 * @param startBit Starting point of the data.
 * @return void.
 */
    void BBB_I2C::writeMoreBits(uint8_t DATA_REGADD, uint8_t data, uint8_t length,
                                uint8_t startBit) {
        int8_t temp = readByte(DATA_REGADD);
        uint8_t bits = 1;
        uint8_t i = 0;

        while (i < length - 1) {
            bits = (bits << 1);
            ++bits;
            ++i;
        }

        temp &= ~(bits << startBit);

        temp |= (data << startBit);

        writeByte(DATA_REGADD, temp);

    }

/**
 * @function writeByte(uint8_t dev_addr, uint8_t DATA_REGADD, uint8_t data)
 * @param dev_addr Device Address.
 * @param DATA_REGADD Data Register Address.
 * @param data Writing data.
 * @return void.
 */
    void BBB_I2C::writeByte(uint8_t DATA_REGADD, uint8_t data) {

        uint8_t buffer[2];

        buffer[0] = DATA_REGADD;
        buffer[1] = data;

        if (write(this->file_descriptor, buffer, 2) != 2) {
            msg_error("Can not write data. Address %d.", dev_addr);
        }

    }

/**
 * @function writeByteBuffer(uint8_t dev_addr, uint8_t DATA_REGADD, uint8_t *data, uint8_t length)
 * @param dev_addr Device Address.
 * @param DATA_REGADD Data Register Address.
 * @param *data Data storage array.
 * @param length Array length.
 * @return void.
 */
    void BBB_I2C::writeByteBuffer(uint8_t DATA_REGADD, uint8_t *data,
                                  uint8_t length) {

        uint8_t buffer[1];
        buffer[0] = DATA_REGADD;

        if (write(this->file_descriptor, buffer, 1) != 1) {
            msg_error("Can not write data. Address %d.", dev_addr);
        }

        if (write(this->file_descriptor, data, length) != length) {
            msg_error("Can not write data. Address %d.", dev_addr);
        }

    }

/**
 * @function writeByteArduino(uint8_t dev_addr, int8_t data)
 * @param dev_addr Arduino Device Address.
 * @param data Writing data.
 * @return void.
 */
    void BBB_I2C::writeByteArduino(int8_t data) {

        int8_t buffer[1];
        buffer[0] = data;

        if (write(this->file_descriptor, buffer, 1) != 1) {
            msg_error("Can not write data. Address %d.", dev_addr);
        }

    }

/**
 * @function writeByteBufferArduino(uint8_t dev_addr, uint8_t *data, uint8_t length)
 * @param dev_addr Arduino Device Address.
 * @param *data Data storage array.
 * @param length Array length.
 * @return void.
 */
    void BBB_I2C::writeByteBufferArduino(uint8_t *data, uint8_t length) {

        if (write(this->file_descriptor, data, length) != length) {
            msg_error("Can not write data. Address %d.", dev_addr);
        }

    }

/**
 * @function readBit(uint8_t dev_addr, uint8_t DATA_REGADD, uint8_t bitNum)
 * @param dev_addr Device Address.
 * @param DATA_REGADD Data Register Address.
 * @param bitNum Bit Number for reading.
 * @return uint8_t bit value.
 */

    uint8_t BBB_I2C::readBit(uint8_t DATA_REGADD, uint8_t bitNum) {
        int8_t temp = readByte(DATA_REGADD);
        return (temp >> bitNum) % 2;
    }

/**
 * @function readBits(uint8_t dev_addr, uint8_t DATA_REGADD, uint8_t length, uint8_t startBit)
 * @param dev_addr Device Address.
 * @param DATA_REGADD Data Register Address.
 * @param length Bits length.
 * @param startBit Starting point of the value.
 * @return uint8_t bit value.
 */
    uint8_t BBB_I2C::readMoreBits(uint8_t DATA_REGADD, uint8_t length,
                                  uint8_t startBit) {
        int8_t temp = readByte(DATA_REGADD);
        return (temp >> startBit) % (uint8_t) pow(2, length);
    }

/**
 * @function readByte(uint8_t dev_addr, uint8_t DATA_REGADD)
 * @param dev_addr Device Address.
 * @param DATA_REGADD Data Register Address.
 * @return uint8_t bit value.
 */
    uint8_t BBB_I2C::readByte(uint8_t DATA_REGADD) {

        uint8_t buffer[1];
        buffer[0] = DATA_REGADD;

        if (write(this->file_descriptor, buffer, 1) != 1) {
            msg_error("Can not write data. Address %d.", dev_addr);
        }

        uint8_t value[1];

        if (read(this->file_descriptor, value, 1) != 1) {
            msg_error("Can not read data. Address %d.", dev_addr);
        }

        return value[0];
    }

/**
 * @function readByteBuffer(uint8_t dev_addr, uint8_t DATA_REGADD, uint8_t *data, uint8_t length)
 * @param dev_addr Device Address.
 * @param DATA_REGADD Data Register Address.
 * @param *data Data storage array.
 * @param length Array length.
 * @return void.
 */
    void BBB_I2C::readByteBuffer(uint8_t DATA_REGADD, uint8_t *data,
                                 uint8_t length) {

        uint8_t buffer[1];
        buffer[0] = DATA_REGADD;

        if (write(this->file_descriptor, buffer, 1) != 1) {
            msg_error("Can not write data. Address %d.", dev_addr);
        }

        if (read(this->file_descriptor, data, length) != length) {
            msg_error("Can not read data. Address %d.", dev_addr);
        }

    }

/**
 * @function readByteBufferArduino(uint8_t dev_addr, uint8_t* data, uint8_t length)
 * @param dev_addr Arduino Device Address.
 * @param *data Data storage array.
 * @param length Array length.
 * @return void.
 */
    void BBB_I2C::readByteBufferArduino(uint8_t *data, uint8_t length) {

        if (read(this->file_descriptor, data, length) != length) {
            msg_error("Can not read data. Address %d.", dev_addr);
        }

    }

/**
 * @function readWord(uint8_t dev_addr, uint8_t MSB, uint8_t LSB)
 * @param dev_addr Arduino Device Address.
 * @param MSB 16-bit values Most Significant Byte Address.
 * @param LSB 16-bit values Less Significant Byte Address..
 * @return void.
 */
    int16_t BBB_I2C::readWord(uint8_t MSB, uint8_t LSB) {

        uint8_t msb = readByte(MSB);

        uint8_t lsb = readByte(LSB);

        return ((int16_t) msb << 8) + lsb;
    }

}  // namespace cacaosd_bbb_i2c
