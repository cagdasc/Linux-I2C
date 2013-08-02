/* 
 * File:   BBB_I2C.cpp
 * Author: Cagdas Caglak
 * E-mail: cagdascaglak@gmail.com
 * Code is free but There is not warranty.
 * Created on July 26, 2013, 5:01 PM
 * ----------------------------------------
 * 03/08/2013 ...NoExit() methods added and it doesn't include exit(1) function. Add Device Address in error messages.
 */

#include "BBB_I2C.h"

BBB_I2C::BBB_I2C() {
}

BBB_I2C::BBB_I2C(const BBB_I2C& orig) {
}

BBB_I2C::~BBB_I2C() {
}

void BBB_I2C::writeBit(char DEV_ADD, char DATA_REGADD, char value, int bitNum, int bus) {
    int8_t temp = readByte(DEV_ADD, DATA_REGADD, bus);
    if (value == 0) {
        temp = temp & ~(1 << bitNum);
    } else if (value == 1) {
        temp = temp | (1 << bitNum);
    } else {
        printf("Value must be 0 or 1! --> Address %d.\n",DEV_ADD);
        exit(1);
    }

    writeByte(DEV_ADD, DATA_REGADD, temp, bus);

}

void BBB_I2C::writeBitNoExit(char DEV_ADD, char DATA_REGADD, char value, int bitNum, int bus) {
    int8_t temp = readByte(DEV_ADD, DATA_REGADD, bus);
    if (value == 0) {
        temp = temp & ~(1 << bitNum);
    } else if (value == 1) {
        temp = temp | (1 << bitNum);
    } else {
        printf("Value must be 0 or 1! --> Address %d.\n",DEV_ADD);
    }

    writeByte(DEV_ADD, DATA_REGADD, temp, bus);

}

void BBB_I2C::writeByte(char DEV_ADD, char DATA_REGADD, char value, int bus) {
    char path[20];

    sprintf(path, "/dev/i2c-%d", bus);

    int file;

    if ((file = open(path, O_RDWR)) < 0) {
        printf("%s do not open. Address %d.\n", path, DEV_ADD);
        exit(1);
    }

    if (ioctl(file, I2C_SLAVE, DEV_ADD) < 0) {
        printf("Can not join I2C Bus. Address %d.\n", DEV_ADD);
        exit(1);
    }

    uint8_t buffer[2];

    buffer[0] = DATA_REGADD;
    buffer[1] = value;

    if (write(file, buffer, 2) != 2) {
        printf("Can not write data. Address %d.\n", DEV_ADD);
        exit(1);
    }

    close(file);

}

void BBB_I2C::writeByteNoExit(char DEV_ADD, char DATA_REGADD, char value, int bus) {
    char path[20];

    sprintf(path, "/dev/i2c-%d", bus);

    int file;

    if ((file = open(path, O_RDWR)) < 0) {
        printf("%s do not open. Address %d.\n", path, DEV_ADD);
    }

    if (ioctl(file, I2C_SLAVE, DEV_ADD) < 0) {
        printf("Can not join I2C Bus. Address %d.\n", DEV_ADD);
    }

    uint8_t buffer[2];

    buffer[0] = DATA_REGADD;
    buffer[1] = value;

    if (write(file, buffer, 2) != 2) {
        printf("Can not write data. Address %d.\n", DEV_ADD);
    }

    close(file);

}

void BBB_I2C::writeByteBuffer(char DEV_ADD, char DATA_REGADD, uint8_t *value, uint8_t length, int bus) {
    char path[20];

    sprintf(path, "/dev/i2c-%d", bus);

    int file;

    if ((file = open(path, O_RDWR)) < 0) {
        printf("%s do not open. Address %d.\n", path, DEV_ADD);
        exit(1);
    }

    if (ioctl(file, I2C_SLAVE, DEV_ADD) < 0) {
        printf("Can not join I2C Bus. Address %d.\n", DEV_ADD);
        exit(1);
    }

    char buffer[1];
    buffer[0] = DATA_REGADD;

    if (write(file, buffer, 1) != 1) {
        printf("Can not write data. Address %d.\n", DEV_ADD);
        exit(1);
    }

    if (write(file, value, length) != length) {
        printf("Can not write data. Address %d.\n", DEV_ADD);
        exit(1);
    }

    close(file);
}

void BBB_I2C::writeByteBufferNoExit(char DEV_ADD, char DATA_REGADD, uint8_t *value, uint8_t length, int bus) {
    char path[20];

    sprintf(path, "/dev/i2c-%d", bus);

    int file;

    if ((file = open(path, O_RDWR)) < 0) {
        printf("%s do not open. Address %d.\n", path, DEV_ADD);
    }

    if (ioctl(file, I2C_SLAVE, DEV_ADD) < 0) {
        printf("Can not join I2C Bus. Address %d.\n", DEV_ADD);
    }

    char buffer[1];
    buffer[0] = DATA_REGADD;

    if (write(file, buffer, 1) != 1) {
        printf("Can not write data. Address %d.\n", DEV_ADD);
    }

    if (write(file, value, length) != length) {
        printf("Can not write data. Address %d.\n", DEV_ADD);
    }

    close(file);
}

void BBB_I2C::writeByteArduino(char DEV_ADD, int8_t value, int bus) {
    char path[20];

    sprintf(path, "/dev/i2c-%d", bus);

    int file;

    if ((file = open(path, O_RDWR)) < 0) {
        printf("%s do not open. Address %d.\n", path, DEV_ADD);
        exit(1);
    }

    if (ioctl(file, I2C_SLAVE, DEV_ADD) < 0) {
        printf("Can not join I2C Bus. Address %d.\n", DEV_ADD);
        exit(1);
    }

    int8_t buffer[1];

    buffer[0] = value;

    if (write(file, buffer, 1) != 1) {
        printf("Can not write data. Address %d.\n", DEV_ADD);
        exit(1);
    }

    close(file);

}
void BBB_I2C::writeByteArduinoNoExit(char DEV_ADD, int8_t value, int bus) {
    char path[20];

    sprintf(path, "/dev/i2c-%d", bus);

    int file;

    if ((file = open(path, O_RDWR)) < 0) {
        printf("%s do not open. Address %d.\n", path, DEV_ADD);
    }

    if (ioctl(file, I2C_SLAVE, DEV_ADD) < 0) {
        printf("Can not join I2C Bus. Address %d.\n", DEV_ADD);
    }

    int8_t buffer[1];

    buffer[0] = value;

    if (write(file, buffer, 1) != 1) {
        printf("Can not write data. Address %d.\n", DEV_ADD);
    }

    close(file);

}

void BBB_I2C::writeByteBufferArduino(char DEV_ADD, uint8_t *value, uint8_t buff_len, int bus) {
    char path[20];

    sprintf(path, "/dev/i2c-%d", bus);

    int file;

    if ((file = open(path, O_RDWR)) < 0) {
        printf("%s do not open. Address %d.\n", path, DEV_ADD);
        exit(1);
    }

    if (ioctl(file, I2C_SLAVE, DEV_ADD) < 0) {
        printf("Can not join I2C Bus. Address %d.\n", DEV_ADD);
        exit(1);
    }


    if (write(file, value, buff_len) != buff_len) {
        printf("Can not write data. Address %d.\n", DEV_ADD);
        exit(1);
    }

    close(file);
}

void BBB_I2C::writeByteBufferArduinoNoExit(char DEV_ADD, uint8_t *value, uint8_t buff_len, int bus) {
    char path[20];

    sprintf(path, "/dev/i2c-%d", bus);

    int file;

    if ((file = open(path, O_RDWR)) < 0) {
        printf("%s do not open. Address %d.\n", path, DEV_ADD);
    }

    if (ioctl(file, I2C_SLAVE, DEV_ADD) < 0) {
        printf("Can not join I2C Bus. Address %d.\n", DEV_ADD);
    }


    if (write(file, value, buff_len) != buff_len) {
        printf("Can not write data. Address %d.\n",DEV_ADD);
    }

    close(file);
}

uint8_t BBB_I2C::readBit(char DEV_ADD, char DATA_REGADD, uint8_t bitNum, int bus) {
    int8_t temp = readByte(DEV_ADD, DATA_REGADD, bus);
    return (temp >> bitNum) % 2;
}

int8_t BBB_I2C::readByte(char DEV_ADD, char DATA_REGADD, int bus) {
    char path[20];

    sprintf(path, "/dev/i2c-%d", bus);

    int file;

    if ((file = open(path, O_RDWR)) < 0) {
        printf("%s do not open. Address %d.\n", path, DEV_ADD);
        exit(1);
    }

    if (ioctl(file, I2C_SLAVE, DEV_ADD) < 0) {
        printf("Can not join I2C Bus. Address %d.\n", DEV_ADD);
        exit(1);
    }

    uint8_t buffer[1];

    buffer[0] = DATA_REGADD;

    if (write(file, buffer, 1) != 1) {
        printf("Can not write data. Address %d.\n", DEV_ADD);
        exit(1);
    }

    int8_t value[1];

    if (read(file, value, 1) != 1) {
        printf("Can not read data. Address %d.\n", DEV_ADD);
        exit(1);
    }

    close(file);

    return value[0];
}

int8_t BBB_I2C::readByteNoExit(char DEV_ADD, char DATA_REGADD, int bus) {
    char path[20];

    sprintf(path, "/dev/i2c-%d", bus);

    int file;

    if ((file = open(path, O_RDWR)) < 0) {
        printf("%s do not open. Address %d.\n", path, DEV_ADD);
    }

    if (ioctl(file, I2C_SLAVE, DEV_ADD) < 0) {
        printf("Can not join I2C Bus. Address %d.\n", DEV_ADD);
    }

    uint8_t buffer[1];

    buffer[0] = DATA_REGADD;

    if (write(file, buffer, 1) != 1) {
        printf("Can not write data. Address %d.\n", DEV_ADD);
    }

    int8_t value[1];

    if (read(file, value, 1) != 1) {
        printf("Can not read data. Address %d.\n", DEV_ADD);
    }

    close(file);

    return value[0];
}

void BBB_I2C::readByteBuffer(char DEV_ADD, char DATA_REGADD, uint8_t *data, uint8_t length, int bus) {
    char path[20];

    sprintf(path, "/dev/i2c-%d", bus);

    int file;

    if ((file = open(path, O_RDWR)) < 0) {
        printf("%s do not open. Address %d.\n", path, DEV_ADD);
        exit(1);
    }

    if (ioctl(file, I2C_SLAVE, DEV_ADD) < 0) {
        printf("Can not join I2C Bus. Address %d.\n", DEV_ADD);
        exit(1);
    }

    uint8_t buffer[1];

    buffer[0] = DATA_REGADD;

    if (write(file, buffer, 1) != 1) {
        printf("Can not write data. Address %d.\n", DEV_ADD);
        exit(1);
    }

    if (read(file, data, length) != length) {
        printf("Can not read data. Address %d.\n", DEV_ADD);
        exit(1);
    }

    close(file);

}

void BBB_I2C::readByteBufferNoExit(char DEV_ADD, char DATA_REGADD, uint8_t *data, uint8_t length, int bus) {
    char path[20];

    sprintf(path, "/dev/i2c-%d", bus);

    int file;

    if ((file = open(path, O_RDWR)) < 0) {
        printf("%s do not open. Address %d.\n", path, DEV_ADD);
    }

    if (ioctl(file, I2C_SLAVE, DEV_ADD) < 0) {
        printf("Can not join I2C Bus. Address %d.\n", DEV_ADD);
    }

    uint8_t buffer[1];

    buffer[0] = DATA_REGADD;

    if (write(file, buffer, 1) != 1) {
        printf("Can not write data. Address %d.\n", DEV_ADD);
    }

    if (read(file, data, length) != length) {
        printf("Can not read data. Address %d.\n", DEV_ADD);
    }

    close(file);

}

void BBB_I2C::readByteBufferArduino(char DEV_ADD, uint8_t* data, uint8_t length, int bus) {
    char path[20];

    sprintf(path, "/dev/i2c-%d", bus);

    int file;

    if ((file = open(path, O_RDWR)) < 0) {
        printf("%s do not open. Address %d.\n", path, DEV_ADD);
        exit(1);
    }

    if (ioctl(file, I2C_SLAVE, DEV_ADD) < 0) {
        printf("Can not join I2C Bus. Address %d.\n", DEV_ADD);
        exit(1);
    }

    if (read(file, data, length) != length) {
        printf("Can not read data. Address %d.\n", DEV_ADD);
        exit(1);
    }

    close(file);

}

void BBB_I2C::readByteBufferArduinoNoExit(char DEV_ADD, uint8_t* data, uint8_t length, int bus) {
    char path[20];

    sprintf(path, "/dev/i2c-%d", bus);

    int file;

    if ((file = open(path, O_RDWR)) < 0) {
        printf("%s do not open. Address %d.\n", path, DEV_ADD);
    }

    if (ioctl(file, I2C_SLAVE, DEV_ADD) < 0) {
        printf("Can not join I2C Bus. Address %d.\n", DEV_ADD);
    }

    if (read(file, data, length) != length) {
        printf("Can not read data. Address %d.\n", DEV_ADD);
    }

    close(file);

}

int16_t BBB_I2C::readWord(char DEV_ADD, uint8_t MSB, uint8_t LSB, int bus) {

    int16_t msb = readByte(DEV_ADD, MSB, bus);

    int16_t lsb = readByte(DEV_ADD, LSB, bus);

    msb = msb << 8;
    msb += lsb;

    return msb;
}