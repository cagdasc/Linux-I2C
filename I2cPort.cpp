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

#include "I2cPort.h"

namespace cacaosd_i2cport {

/**
 * @funtion I2cPort()
 */
    I2cPort::I2cPort() {
        this->connection_open = false;
    }

/**
 * @funtion I2cPort(uint8_t bus_address)
 * @param bus_addr I2C Bus address.
 */
    I2cPort::I2cPort(uint8_t bus_address) {
        this->connection_open = false;
        this->bus_address = bus_address;
        this->path = (char *) calloc(PATH_SIZE, sizeof(char));
        sprintf(path, "/dev/i2c-%d", this->bus_address);
    }

/**
 * @funtion I2cPort(uint8_t device_address, uint8_t bus_address)
 * @param device_address Device Address
 * @param bus_address I2C Bus address.
 */
    I2cPort::I2cPort(uint8_t device_address, uint8_t bus_address) {
        this->connection_open = false;
        this->bus_address = bus_address;
        this->path = (char *) calloc(PATH_SIZE, sizeof(char));
        this->device_address = device_address;
        sprintf(path, "/dev/i2c-%d", this->bus_address);
    }

/** Default Destructor
 * @funtion ~I2cPort()
 *
 */
    I2cPort::~I2cPort() {
        free(path);
        this->closeConnection();
    }

/**
 * @funtion setBusAddress(uint8_t bus_address)
 * @param bus_address I2C Bus address.
 */
    void I2cPort::setBusAddress(uint8_t bus_address) {
        free(path);
        this->bus_address = bus_address;
        this->path = (char *) calloc(PATH_SIZE, sizeof(char));
        sprintf(path, "/dev/i2c-%d", this->bus_address);
    }

/**
 * @funtion getBusAddress()
 * @return bus_addr I2C Bus address.
 */
    uint8_t I2cPort::getBusAddress() const {
        return this->bus_address;
    }

/**
 * @funtion setDeviceAddress(uint8_t device_address)
 * @param dev_addr Device Address
 */
    void I2cPort::setDeviceAddress(uint8_t device_address) {
        this->device_address = device_address;
    }

/**
 * @funtion getDeviceAddress()
 * @return device_address Device Address
 */
    uint8_t I2cPort::getDeviceAddress() const {
        return this->device_address;
    }

/**
 * @function openConnection()
 * @return file type of int
 */
    void I2cPort::openConnection() {
        int file;

        if ((file = open(path, O_RDWR)) < 0) {
            msg_error("%s do not open. Address %d.", path, device_address);
            exit(1);
        }

        if (ioctl(file, I2C_SLAVE, device_address) < 0) {
            msg_error("Can not join I2C Bus. Address %d.", device_address);
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

/** Close connection.
 * @function closeConnection()
 * @return void
 */
    void I2cPort::closeConnection() {
        this->connection_open = false;
        close(this->file_descriptor);
    }

/**
 * @function writeBit(uint8_t DATA_REGADD, uint8_t data, int bitNum)
 * @param DATA_REGADD Data Register Address.
 * @param data Writing data.
 * @param bitNum Bit Number for writing.
 * @return void.
 */
    void I2cPort::writeBit(uint8_t DATA_REGADD, uint8_t data, uint8_t bitNum) {
        int8_t temp = readByte(DATA_REGADD);
        if (data == 0) {
            temp = temp & ~(1 << bitNum);
        } else if (data == 1) {
            temp = temp | (1 << bitNum);
        } else {
            msg_warning("Value must be 0 or 1! --> Address %d.", device_address);
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
    void I2cPort::writeMoreBits(uint8_t DATA_REGADD, uint8_t data, uint8_t length,
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
 * @function writeByte(uint8_t DATA_REGADD, uint8_t data)
 * @param DATA_REGADD Data Register Address.
 * @param data Writing data.
 * @return void.
 */
    void I2cPort::writeByte(uint8_t DATA_REGADD, uint8_t data) {

        uint8_t buffer[2];

        buffer[0] = DATA_REGADD;
        buffer[1] = data;

        if (write(this->file_descriptor, buffer, 2) != 2) {
            msg_error("Can not write data. Address %d.", device_address);
        }

    }

/**
 * @function writeByteBuffer(uint8_t DATA_REGADD, uint8_t *data, uint8_t length)
 * @param DATA_REGADD Data Register Address.
 * @param data Data storage array.
 * @param length Array length.
 * @return void.
 */
    void I2cPort::writeByteBuffer(uint8_t DATA_REGADD, uint8_t *data,
                                  uint8_t length) {

        uint8_t buffer[1];
        buffer[0] = DATA_REGADD;

        if (write(this->file_descriptor, buffer, 1) != 1) {
            msg_error("Can not write data. Address %d.", device_address);
        }

        if (write(this->file_descriptor, data, length) != length) {
            msg_error("Can not write data. Address %d.", device_address);
        }

    }

/**
 * @function writeByteArduino(int8_t data)
 * @param data Writing data.
 * @return void.
 */
    void I2cPort::writeByteArduino(int8_t data) {

        int8_t buffer[1];
        buffer[0] = data;

        if (write(this->file_descriptor, buffer, 1) != 1) {
            msg_error("Can not write data. Address %d.", device_address);
        }

    }

/**
 * @function writeByteBufferArduino(uint8_t *data, uint8_t length)
 * @param data Data storage array.
 * @param length Array length.
 * @return void.
 */
    void I2cPort::writeByteBufferArduino(uint8_t *data, uint8_t length) {

        if (write(this->file_descriptor, data, length) != length) {
            msg_error("Can not write data. Address %d.", device_address);
        }

    }

/**
 * @function readBit(uint8_t DATA_REGADD, uint8_t bitNum)
 * @param DATA_REGADD Data Register Address.
 * @param bitNum Bit Number for reading.
 * @return uint8_t bit value.
 */

    uint8_t I2cPort::readBit(uint8_t DATA_REGADD, uint8_t bitNum) {
        int8_t temp = readByte(DATA_REGADD);
        return (uint8_t) ((temp >> bitNum) % 2);
    }

/**
 * @function readBits(uint8_t DATA_REGADD, uint8_t length, uint8_t startBit)
 * @param DATA_REGADD Data Register Address.
 * @param length Bits length.
 * @param startBit Starting point of the value.
 * @return uint8_t bit value.
 */
    uint8_t I2cPort::readMoreBits(uint8_t DATA_REGADD, uint8_t length,
                                  uint8_t startBit) {
        int8_t temp = readByte(DATA_REGADD);
        return (uint8_t) ((temp >> startBit) % (uint8_t) pow(2, length));
    }

/**
 * @function readByte(uint8_t DATA_REGADD)
 * @param DATA_REGADD Data Register Address.
 * @return uint8_t bit value.
 */
    uint8_t I2cPort::readByte(uint8_t DATA_REGADD) {

        uint8_t buffer[1];
        buffer[0] = DATA_REGADD;

        if (write(this->file_descriptor, buffer, 1) != 1) {
            msg_error("Can not write data. Address %d.", device_address);
        }

        uint8_t value[1];

        if (read(this->file_descriptor, value, 1) != 1) {
            msg_error("Can not read data. Address %d.", device_address);
        }

        return value[0];
    }

/**
 * @function readByteBuffer(uint8_t DATA_REGADD, uint8_t *data, uint8_t length)
 * @param DATA_REGADD Data Register Address.
 * @param data Data storage array.
 * @param length Array length.
 * @return void.
 */
    void I2cPort::readByteBuffer(uint8_t DATA_REGADD, uint8_t *data,
                                 uint8_t length) {

        uint8_t buffer[1];
        buffer[0] = DATA_REGADD;

        if (write(this->file_descriptor, buffer, 1) != 1) {
            msg_error("Can not write data. Address %d.", device_address);
        }

        if (read(this->file_descriptor, data, length) != length) {
            msg_error("Can not read data. Address %d.", device_address);
        }

    }

/**
 * @function readByteBufferArduino(uint8_t* data, uint8_t length)
 * @param data Data storage array.
 * @param length Array length.
 * @return void.
 */
    void I2cPort::readByteBufferArduino(uint8_t *data, uint8_t length) {

        if (read(this->file_descriptor, data, length) != length) {
            msg_error("Can not read data. Address %d.", device_address);
        }

    }

/**
 * @function readWord(uint8_t MSB, uint8_t LSB)
 * @param MSB 16-bit values Most Significant Byte Address.
 * @param LSB 16-bit values Less Significant Byte Address..
 * @return void.
 */
    int16_t I2cPort::readWord(uint8_t MSB, uint8_t LSB) {

        uint8_t msb = readByte(MSB);

        uint8_t lsb = readByte(LSB);

        return ((int16_t) msb << 8) + lsb;
    }

}  // namespace cacaosd_i2cport
