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

#include "MPU6050.h"

namespace cacaosd_mpu6050 {


    MPU6050::MPU6050(I2cPort *i2c) {
        this->i2c = i2c;
    }

    MPU6050::~MPU6050() {
        delete i2c;
    }

/** Power on and prepare for general usage.
 * This will activate the device and take it out of sleep mode (which must be done
 * after start-up). This function also sets both the accelerometer and the gyroscope
 * to their most sensitive settings, namely +/- 2g and +/- 250 degrees/sec, and sets
 * the clock source to use the X Gyro for reference, which is slightly better than
 * the default internal clock source.
 */
    void MPU6050::initialize() {
        setRangeAcceleration(0);
        setRangeGyroscope(0);
        setSleepMode(false);
    }

/** Trigger a full device reset.
 * A small delay of ~50ms may be desirable after triggering a reset.
 * @see PWR_MGMT_1
 * @see DEV_RESET_BIT
 */
    void MPU6050::reset() {
        i2c->writeBit(PWR_MGMT_1, 1, DEV_RESET_BIT);
    }

/** Set device address.
 * @param dev_addr device address
 * @see DEF_DEV_ADD
 */
    void MPU6050::setDeviceAddress(uint8_t DEV_ADD) {
        this->device_address = DEV_ADD;
    }

/** Get device address.
 * @return device address
 */
    uint8_t MPU6050::getDeviceAddress() const {
        return this->device_address;
    }

/** Set sleep mode status.
 * @param enabled New sleep mode enabled status
 * @see getSleepEnabled()
 * @see PWR_MGMT_1
 */
    void MPU6050::setSleepMode(bool mode) {
        int8_t byte = i2c->readByte(PWR_MGMT_1);
        if (mode) {
            byte |= 64;
        } else {
            byte &= ~64;
        }
        i2c->writeByte(PWR_MGMT_1, byte);
    }

/** Get sleep mode status.
 * Setting the SLEEP bit in the register puts the device into very low power
 * sleep mode. In this mode, only the serial interface and internal registers
 * remain active, allowing for a very low standby current. Clearing this bit
 * puts the device back into normal mode. To save power, the individual standby
 * selections for each of the gyros should be used if any gyro axis is not used
 * by the application.
 * @return Current sleep mode enabled status
 * @see PWR_MGMT_1
 */
    bool MPU6050::getSleepMode() {
        int8_t byte = i2c->readByte(PWR_MGMT_1);
        byte >>= 6;
        byte %= 2;
        if (byte == 1) {
            return true;
        } else {
            return false;
        }
    }

/** Set full-scale accelerometer range.
 * @param range New full-scale accelerometer range setting
 * @see getRangeAcceleration()
 */
    void MPU6050::setRangeAcceleration(uint8_t range) {
        uint8_t afs;
        afs = i2c->readByte(ACCEL_CONFIG);
        if (range == 0) {
            afs &= ~24;
        } else if (range == 1) {
            afs |= 8;
            afs &= ~16;
        } else if (range == 2) {
            afs &= ~8;
            afs |= 16;
        } else {
            afs |= 24;
        }
        i2c->writeByte(ACCEL_CONFIG, afs);
    }

/** Get full-scale accelerometer range.
 * The FS_SEL parameter allows setting the full-scale range of the accelerometer
 * sensors, as described in the table below.
 *
 * <pre>
 * 0 = +/- 2g
 * 1 = +/- 4g
 * 2 = +/- 8g
 * 3 = +/- 16g
 * </pre>
 *
 * @return Current full-scale accelerometer range setting
 * @see ACCEL_CONFIG
 */
    uint8_t MPU6050::getRangeAcceleration() {
        uint8_t afs;
        afs = i2c->readByte(ACCEL_CONFIG);
        afs >>= 3;
        afs %= 4;
        return afs;
    }

/** Set full-scale gyroscope range.
 * @param range New full-scale gyroscope range value
 * @see getRangeGyroscope()
 * @see GYRO_CONFIG
 */
    void MPU6050::setRangeGyroscope(uint8_t range) {
        uint8_t fs;
        fs = i2c->readByte(GYRO_CONFIG);
        if (range == 0) {
            fs &= ~24;
        } else if (range == 1) {
            fs |= 8;
            fs &= ~16;
        } else if (range == 2) {
            fs &= ~8;
            fs |= 16;
        } else {
            fs |= 24;
        }
        i2c->writeByte(GYRO_CONFIG, fs);
    }

/** Get full-scale gyroscope range.
 * The FS_SEL parameter allows setting the full-scale range of the gyro sensors,
 * as described in the table below.
 *
 * <pre>
 * 0 = +/- 250 degrees/sec
 * 1 = +/- 500 degrees/sec
 * 2 = +/- 1000 degrees/sec
 * 3 = +/- 2000 degrees/sec
 * </pre>
 *
 * @return Current full-scale gyroscope range setting
 * @see GYRO_CONFIG
 */
    uint8_t MPU6050::getRangeGyroscope() {
        uint8_t fs;
        fs = i2c->readByte(GYRO_CONFIG);
        fs >>= 3;
        fs %= 4;
        return fs;
    }

    void MPU6050::getAccelerations(int16_t *accels) {
        accels[0] = i2c->readWord(ACCEL_XOUT_H, ACCEL_XOUT_L);
        accels[1] = i2c->readWord(ACCEL_YOUT_H, ACCEL_YOUT_L);
        accels[2] = i2c->readWord(ACCEL_ZOUT_H, ACCEL_ZOUT_L);
    }

    int16_t MPU6050::getAccelerationX() {
        return i2c->readWord(ACCEL_XOUT_H, ACCEL_XOUT_L);
    }

    int16_t MPU6050::getAccelerationY() {
        return i2c->readWord(ACCEL_YOUT_H, ACCEL_YOUT_L);
    }

    int16_t MPU6050::getAccelerationZ() {
        return i2c->readWord(ACCEL_ZOUT_H, ACCEL_ZOUT_L);
    }

    void MPU6050::getAngularVelocities(int16_t *gyros) {
        gyros[0] = i2c->readWord(GYRO_XOUT_H, GYRO_XOUT_L);
        gyros[1] = i2c->readWord(GYRO_YOUT_H, GYRO_YOUT_L);
        gyros[2] = i2c->readWord(GYRO_ZOUT_H, GYRO_ZOUT_L);
    }

    int16_t MPU6050::getAngularVelocityX() {
        return i2c->readWord(GYRO_XOUT_H, GYRO_XOUT_L);
    }

    int16_t MPU6050::getAngularVelocityY() {
        return i2c->readWord(GYRO_YOUT_H, GYRO_YOUT_L);
    }

    int16_t MPU6050::getAngularVelocityZ() {
        return i2c->readWord(GYRO_ZOUT_H, GYRO_ZOUT_L);
    }

    int16_t MPU6050::getTemperature() {
        return i2c->readWord(TEMP_OUT_H, TEMP_OUT_L);
    }

    void MPU6050::getMotions6(int16_t *motion6) {
        motion6[0] = i2c->readWord(ACCEL_XOUT_H, ACCEL_XOUT_L);
        motion6[1] = i2c->readWord(ACCEL_YOUT_H, ACCEL_YOUT_L);
        motion6[2] = i2c->readWord(ACCEL_ZOUT_H, ACCEL_ZOUT_L);

        motion6[3] = i2c->readWord(GYRO_XOUT_H, GYRO_XOUT_L);
        motion6[4] = i2c->readWord(GYRO_YOUT_H, GYRO_YOUT_L);
        motion6[5] = i2c->readWord(GYRO_ZOUT_H, GYRO_ZOUT_L);
    }

/** Set digital low-pass filter configuration.
 * @param mode New DLFP configuration setting
 * @see getDLPFMode()
 * @see CONFIG
 */
    void MPU6050::setDLPFMode(uint8_t mode) {
        uint8_t config = i2c->readByte(CONFIG);
        if (mode == 0) {
            config = config & ~7;
        } else if (mode == 1) {
            config |= 1;
            config &= ~6;
        } else if (mode == 2) {
            config |= 2;
            config &= ~5;
        } else if (mode == 3) {
            config |= 3;
            config &= ~4;
        } else if (mode == 4) {
            config |= 4;
            config &= ~3;
        } else if (mode == 5) {
            config |= 5;
            config &= ~2;
        } else if (mode == 6) {
            config |= 6;
            config &= ~1;
        } else if (mode == 7) {
            config |= 7;
        }

        i2c->writeByte(CONFIG, config);
    }

/** Get digital low-pass filter configuration.
 * The DLPF_CFG parameter sets the digital low pass filter configuration. It
 * also determines the internal sampling rate used by the device as shown in
 * the table below.
 *
 * Note: The accelerometer output rate is 1kHz. This means that for a Sample
 * Rate greater than 1kHz, the same accelerometer sample may be output to the
 * FIFO, DMP, and sensor registers more than once.
 *
 * <pre>
 *          |   ACCELEROMETER    |           GYROSCOPE
 * DLPF_CFG | Bandwidth | Delay  | Bandwidth | Delay  | Sample Rate
 * ---------+-----------+--------+-----------+--------+-------------
 * 0        | 260Hz     | 0ms    | 256Hz     | 0.98ms | 8kHz
 * 1        | 184Hz     | 2.0ms  | 188Hz     | 1.9ms  | 1kHz
 * 2        | 94Hz      | 3.0ms  | 98Hz      | 2.8ms  | 1kHz
 * 3        | 44Hz      | 4.9ms  | 42Hz      | 4.8ms  | 1kHz
 * 4        | 21Hz      | 8.5ms  | 20Hz      | 8.3ms  | 1kHz
 * 5        | 10Hz      | 13.8ms | 10Hz      | 13.4ms | 1kHz
 * 6        | 5Hz       | 19.0ms | 5Hz       | 18.6ms | 1kHz
 * 7        |   -- Reserved --   |   -- Reserved --   | Reserved
 * </pre>
 *
 * @return DLFP configuration
 * @see CONFIG
 */
    uint8_t MPU6050::getDLPFMode() {
        uint8_t config = i2c->readByte(CONFIG);
        return config % 8;
    }

/** Set gyroscope sample rate divider.
 * @param rate New sample rate divider
 * @see getSampleRate()
 * @see SMPLRT_DIV
 */
    void MPU6050::setSampleRate(uint8_t rate) {
        i2c->writeByte(SMPLRT_DIV, rate);
    }

/** Get gyroscope output rate divider.
 * The sensor register output, FIFO output, DMP sampling, Motion detection, Zero
 * Motion detection, and Free Fall detection are all based on the Sample Rate.
 * The Sample Rate is generated by dividing the gyroscope output rate by
 * SMPLRT_DIV:
 *
 * Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
 *
 * where Gyroscope Output Rate = 8kHz when the DLPF is disabled (DLPF_CFG = 0 or
 * 7), and 1kHz when the DLPF is enabled (see Register 26).
 *
 * Note: The accelerometer output rate is 1kHz. This means that for a Sample
 * Rate greater than 1kHz, the same accelerometer sample may be output to the
 * FIFO, DMP, and sensor registers more than once.
 *
 * For a diagram of the gyroscope and accelerometer signal paths, see Section 8
 * of the MPU-6000/MPU-6050 Product Specification document.
 *
 * @return Current sample rate
 * @see SMPLRT_DIV
 */
    uint8_t MPU6050::getSampleRate() {
        return i2c->readByte(SMPLRT_DIV);
    }

    void MPU6050::setMotionDetectionThresold(uint8_t value) {
        i2c->writeByte(MOT_THR, value);
    }

    uint8_t MPU6050::getMotionDetectionThresold() {
        return i2c->readByte(MOT_THR);
    }

    void MPU6050::setTEMP_FIFO_EN(uint8_t value) {
        i2c->writeBit(FIFO_EN, value, TEMP_FIFO_EN_BIT);
    }

    uint8_t MPU6050::getTEMP_FIFO_EN() {
        return i2c->readBit(FIFO_EN, TEMP_FIFO_EN_BIT);
    }

    void MPU6050::setXG_FIFO_EN(uint8_t value) {
        i2c->writeBit(FIFO_EN, value, XG_FIFO_EN_BIT);
    }

    uint8_t MPU6050::getXG_FIFO_EN() {
        return i2c->readBit(FIFO_EN, XG_FIFO_EN_BIT);
    }

    void MPU6050::setYG_FIFO_EN(uint8_t value) {
        i2c->writeBit(FIFO_EN, value, YG_FIFO_EN_BIT);
    }

    uint8_t MPU6050::getYG_FIFO_EN() {
        return i2c->readBit(FIFO_EN, YG_FIFO_EN_BIT);
    }

    void MPU6050::setZG_FIFO_EN(uint8_t value) {
        i2c->writeBit(FIFO_EN, value, ZG_FIFO_EN_BIT);
    }

    uint8_t MPU6050::getZG_FIFO_EN() {
        return i2c->readBit(FIFO_EN, ZG_FIFO_EN_BIT);
    }

    void MPU6050::setACCEL_FIFO_EN(uint8_t value) {
        i2c->writeBit(FIFO_EN, value, ACCEL_FIFO_EN_BIT);
    }

    uint8_t MPU6050::getACCEL_FIFO_EN() {
        return i2c->readBit(FIFO_EN, ACCEL_FIFO_EN_BIT);
    }

    void MPU6050::setSLV2_FIFO_EN(uint8_t value) {
        i2c->writeBit(FIFO_EN, value, SLV2_FIFO_EN_BIT);
    }

    uint8_t MPU6050::getSLV2_FIFO_EN() {
        return i2c->readBit(FIFO_EN, SLV2_FIFO_EN_BIT);
    }

    void MPU6050::setSLV1_FIFO_EN(uint8_t value) {
        i2c->writeBit(FIFO_EN, value, SLV1_FIFO_EN_BIT);
    }

    uint8_t MPU6050::getSLV1_FIFO_EN() {
        return i2c->readBit(FIFO_EN, SLV1_FIFO_EN_BIT);
    }

    void MPU6050::setSLV0_FIFO_EN(uint8_t value) {
        i2c->writeBit(FIFO_EN, value, SLV0_FIFO_EN_BIT);
    }

    uint8_t MPU6050::getSLV0_FIFO_EN() {
        return i2c->readBit(FIFO_EN, SLV0_FIFO_EN_BIT);
    }

    uint16_t MPU6050::getFIFO_Count() {
        return i2c->readWord(FIFO_COUNTH, FIFO_COUNTL);
    }

    void MPU6050::setFIFO_Enable(uint8_t value) {
        i2c->writeBit(USER_CTRL, value, FIFO_EN_BIT);
    }

    uint8_t MPU6050::getFIFO_Enable() {
        return i2c->readBit(USER_CTRL, FIFO_EN_BIT);
    }

    void MPU6050::getFIFO_Data(uint8_t *data, uint8_t length) {
        i2c->readByteBuffer(FIFO_R_W, data, length);
    }

    void MPU6050::setFIFO_Reset(uint8_t value) {
        i2c->writeBit(USER_CTRL, value, FIFO_RESET_BIT);
    }

    uint8_t MPU6050::getFIFO_Reset() {
        return i2c->readBit(USER_CTRL, FIFO_RESET_BIT);
    }

}  // namespace cacaosd_mpu6050
