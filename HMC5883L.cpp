/* 
 * File:   HMC5883L.cpp
 * Author: caca
 * 
 * Created on August 23, 2013, 2:39 PM
 */

#include "HMC5883L.h"

HMC5883L::HMC5883L() {
}

HMC5883L::HMC5883L(const HMC5883L& orig) {
}

HMC5883L::~HMC5883L() {
}

void HMC5883L::initialize() {
    setSamplesAvarage(SAMPLES_AVARAGE_8);
    setOutputRate(OUTPUT_RATE_4);
    setMeasurementMode(MEASUREMENT_NORMAL);
    setMeasurementGain(GAIN_1090);
    setOperationMode(OPERATION_MODE_CONT);
}

void HMC5883L::setSamplesAvarage(uint8_t avarage) {

    switch (avarage) {
        case 0:
            i2c.writeBitsNoExit(DEV_ADD, CONFIG_A, SAMPLES_AVARAGE_1, SAMPLES_AVARAGE_LENGTH, SAMPLES_AVARAGE_START);
            break;
        case 1:
            i2c.writeBitsNoExit(DEV_ADD, CONFIG_A, SAMPLES_AVARAGE_2, SAMPLES_AVARAGE_LENGTH, SAMPLES_AVARAGE_START);
            break;
        case 2:
            i2c.writeBitsNoExit(DEV_ADD, CONFIG_A, SAMPLES_AVARAGE_4, SAMPLES_AVARAGE_LENGTH, SAMPLES_AVARAGE_START);
            break;
        case 3:
            i2c.writeBitsNoExit(DEV_ADD, CONFIG_A, SAMPLES_AVARAGE_8, SAMPLES_AVARAGE_LENGTH, SAMPLES_AVARAGE_START);
            break;
        default:
            break;
    }

}

uint8_t HMC5883L::getSamplesAvarage() {
    return i2c.readBitsNoExit(DEV_ADD, CONFIG_A, SAMPLES_AVARAGE_LENGTH, SAMPLES_AVARAGE_START);
}

void HMC5883L::setOutputRate(uint8_t rate) {
    switch (rate) {
        case 0:
            i2c.writeBitsNoExit(DEV_ADD, CONFIG_A, OUTPUT_RATE_0, OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
            break;
        case 1:
            i2c.writeBitsNoExit(DEV_ADD, CONFIG_A, OUTPUT_RATE_1, OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
            break;
        case 2:
            i2c.writeBitsNoExit(DEV_ADD, CONFIG_A, OUTPUT_RATE_2, OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
            break;
        case 3:
            i2c.writeBitsNoExit(DEV_ADD, CONFIG_A, OUTPUT_RATE_3, OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
            break;
        case 4:
            i2c.writeBitsNoExit(DEV_ADD, CONFIG_A, OUTPUT_RATE_4, OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
            break;
        case 5:
            i2c.writeBitsNoExit(DEV_ADD, CONFIG_A, OUTPUT_RATE_5, OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
            break;
        case 6:
            i2c.writeBitsNoExit(DEV_ADD, CONFIG_A, OUTPUT_RATE_6, OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
            break;
        case 7:
            printf("Reserved.\n");
            break;
        default:
            break;
    }
}

uint8_t HMC5883L::getOutputRate() {
    return i2c.readBitsNoExit(DEV_ADD, CONFIG_A, OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
}

void HMC5883L::setMeasurementMode(uint8_t mode) {
    switch (mode) {
        case 0:
            i2c.writeBitsNoExit(DEV_ADD, CONFIG_A, MEASUREMENT_NORMAL, MEASUREMENT_LENGTH, MEASUREMENT_START);
            break;
        case 1:
            i2c.writeBitsNoExit(DEV_ADD, CONFIG_A, MEASUREMENT_POSITIVE, MEASUREMENT_LENGTH, MEASUREMENT_START);
            break;
        case 2:
            i2c.writeBitsNoExit(DEV_ADD, CONFIG_A, MEASUREMENT_NEGATIVE, MEASUREMENT_LENGTH, MEASUREMENT_START);
            break;
        default:
            break;
    }
}

uint8_t HMC5883L::getMeasurementMode() {
    return i2c.readBitsNoExit(DEV_ADD, CONFIG_A, MEASUREMENT_LENGTH, MEASUREMENT_START);
}

void HMC5883L::setMeasurementGain(uint8_t gain) {
    switch (gain) {
        case 0:
            i2c.writeByteNoExit(DEV_ADD, CONFIG_B, (GAIN_1370 << 5));
            break;
        case 1:
            i2c.writeByteNoExit(DEV_ADD, CONFIG_B, (GAIN_1090 << 5));
            break;
        case 2:
            i2c.writeByteNoExit(DEV_ADD, CONFIG_B, (GAIN_820 << 5));
            break;
        case 3:
            i2c.writeByteNoExit(DEV_ADD, CONFIG_B, (GAIN_660 << 5));
            break;
        case 4:
            i2c.writeByteNoExit(DEV_ADD, CONFIG_B, (GAIN_440 << 5));
            break;
        case 5:
            i2c.writeByteNoExit(DEV_ADD, CONFIG_B, (GAIN_390 << 5));
            break;
        case 6:
            i2c.writeByteNoExit(DEV_ADD, CONFIG_B, (GAIN_330 << 5));
            break;
        case 7:
            i2c.writeByteNoExit(DEV_ADD, CONFIG_B, (GAIN_230 << 5));
            break;
        default:
            break;
    }
}

uint8_t HMC5883L::getMeasurementGain() {
    return i2c.readBitsNoExit(DEV_ADD, CONFIG_B, GAIN_LENGTH, GAIN_START);
}

void HMC5883L::setOperationMode(uint8_t mode) {
    switch (mode) {
        case 0:
            i2c.writeByteNoExit(DEV_ADD, MODE_REG, OPERATION_MODE_CONT);
            break;
        case 1:
            i2c.writeByteNoExit(DEV_ADD, MODE_REG, OPERATION_MODE_SINGLE);
            break;
        case 2:
            i2c.writeByteNoExit(DEV_ADD, MODE_REG, OPERATION_MODE_IDLE);
            break;
        default:
            break;
    }
}

uint8_t HMC5883L::getOperationMode() {
    return i2c.readBitsNoExit(DEV_ADD, MODE_REG, OPERATION_MODE_LENGTH, OPERATION_MODE_START);
}

int16_t HMC5883L::getMagnitudeX() {
    return i2c.readWordNoExit(DEV_ADD, X_HIGH, X_LOW);
}

int16_t HMC5883L::getMagnitudeY() {
    return i2c.readWordNoExit(DEV_ADD, Y_HIGH, Y_LOW);
}

int16_t HMC5883L::getMagnitudeZ() {
    return i2c.readWordNoExit(DEV_ADD, Z_HIGH, Z_LOW);
}

uint8_t HMC5883L::getRDYStatus() {
    return i2c.readBitNoExit(DEV_ADD, STATUS_REG, RDY_BIT);
}

uint8_t HMC5883L::getLockStatus() {
    return i2c.readBitNoExit(DEV_ADD, STATUS_REG, LOCK_BIT);
}