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

#ifndef BBB_I2C_H
#define    BBB_I2C_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#define PATH_SIZE 15

#define msg_error(M, ...) printf("[ERROR]:" M "\n", ##__VA_ARGS__);
#define msg_warning(M, ...) printf("[WARNING]:" M "\n", ##__VA_ARGS__);

namespace cacaosd_bbb_i2c {

    class BBB_I2C {
    public:

        BBB_I2C(uint8_t busAddr);

        BBB_I2C(uint8_t DEV_ADD, uint8_t busAddr);

        ~BBB_I2C();

        void openConnection();

        void closeConnection();


        bool isConnectionOpen() const {
            return connection_open;
        }

        void setBusAddress(uint8_t busAddr);

        uint8_t getBusAddress();

        void setDevAddr(uint8_t DEV_ADD);

        uint8_t getDevAddr();

        void writeBit(uint8_t DATA_REGADD, uint8_t data, uint8_t bitNum);

        void writeMoreBits(uint8_t DATA_REGADD, uint8_t data, uint8_t length,
                           uint8_t startBit);

        void writeByte(uint8_t DATA_REGADD, uint8_t data);

        void writeByteBuffer(uint8_t DATA_REGADD, uint8_t *data, uint8_t length);

        void writeByteArduino(int8_t data);

        void writeByteBufferArduino(uint8_t *data, uint8_t length);

        uint8_t readBit(uint8_t DATA_REGADD, uint8_t bitNum);

        uint8_t readMoreBits(uint8_t DATA_REGADD, uint8_t length, uint8_t startBit);

        uint8_t readByte(uint8_t DATA_REGADD);

        void readByteBuffer(uint8_t DATA_REGADD, uint8_t *data, uint8_t length);

        void readByteBufferArduino(uint8_t *data, uint8_t length);

        int16_t readWord(uint8_t MSB, uint8_t LSB);



    private:
        int file_descriptor;
        uint8_t bus_addr;
        uint8_t dev_addr;
        char *path;
        bool connection_open;

    };
}  // namespace cacaosd_bbb_i2c

#endif	/* BBB_I2C_H */

