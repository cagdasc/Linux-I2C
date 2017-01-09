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

#ifndef MPU6050_H
#define    MPU6050_H

#include "I2cPort.h"

#define SELF_TEST_X 0x0D
#define SELF_TEST_Y 0x0E
#define SELF_TEST_Z 0x0F
#define SELF_TEST_A 0x10
#define SMPLRT_DIV 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define MOT_THR 0x1F
#define FIFO_EN 0x23
#define I2C_MST_CTRL 0x24
#define I2C_SLV0_ADDR 0x25
#define I2C_SLV0_REG 0x26
#define I2C_SLV0_CTRL 0x27
#define I2C_SLV1_ADDR 0x28
#define I2C_SLV1_REG 0x29
#define I2C_SLV1_CTRL 0x2A
#define I2C_SLV2_ADDR 0x2B
#define I2C_SLV2_REG 0x2C
#define I2C_SLV2_CTRL 0x2D
#define I2C_SLV3_ADDR 0x2E
#define I2C_SLV3_REG 0x2F
#define I2C_SLV3_CTRL 0x30
#define I2C_SLV4_ADDR 0x31
#define I2C_SLV4_REG 0x32
#define I2C_SLV4_DO 0x33
#define I2C_SLV4_CTRL 0x34
#define I2C_SLV4_DI 0x35
#define I2C_MST_STATUS 0x36
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define INT_STATUS 0x3A
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48
#define I2C_SLV0_DO 0x63
#define I2C_SLV1_DO 0x64
#define I2C_SLV2_DO 0x65
#define I2C_SLV3_DO 0x66
#define I2C_MST_DELAY_CTRL 0x67
//#define SIGNAL_PATH_RESET 0x68
#define MOT_DETECT_CTRL 0x69
#define USER_CTRL 0x6A
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C
#define FIFO_COUNTH 0x72
#define FIFO_COUNTL 0x73
#define FIFO_R_W 0x74
#define WHO_AM_I 0x75
#define MPU6050_DEV_ADD 0x68
#define AFS_SEL 0x1C
#define FS_SEL 0x1B
#define TEMP_FIFO_EN_BIT 7
#define XG_FIFO_EN_BIT 6
#define YG_FIFO_EN_BIT 5
#define ZG_FIFO_EN_BIT 4
#define ACCEL_FIFO_EN_BIT 3
#define SLV2_FIFO_EN_BIT 2
#define SLV1_FIFO_EN_BIT 1
#define SLV0_FIFO_EN_BIT 0
#define DEV_RESET_BIT 7
#define FIFO_EN_BIT 6
#define FIFO_RESET_BIT 2
using namespace cacaosd_i2cport;

namespace cacaosd_mpu6050 {

    class MPU6050 {
    public:
        MPU6050(I2cPort *i2c);

        virtual ~MPU6050();

        void initialize();

        void reset();

        void setDeviceAddress(uint8_t DEV_ADD);

        uint8_t getDeviceAddress() const;

        void setSleepMode(bool mode);

        bool getSleepMode();

        void setRangeAcceleration(uint8_t range);

        uint8_t getRangeAcceleration();

        void setRangeGyroscope(uint8_t range);

        uint8_t getRangeGyroscope();

        void getAccelerations(int16_t *accels);

        int16_t getAccelerationX();

        int16_t getAccelerationY();

        int16_t getAccelerationZ();

        void getAngularVelocities(int16_t *gyros);

        int16_t getAngularVelocityX();

        int16_t getAngularVelocityY();

        int16_t getAngularVelocityZ();

        void getMotions6(int16_t *motion6);

        int16_t getTemperature();

        void setDLPFMode(uint8_t mode);

        uint8_t getDLPFMode();

        void setSampleRate(uint8_t rate);

        uint8_t getSampleRate();

        void setMotionDetectionThresold(uint8_t value);

        uint8_t getMotionDetectionThresold();

        void setTEMP_FIFO_EN(uint8_t value);

        uint8_t getTEMP_FIFO_EN();

        void setXG_FIFO_EN(uint8_t value);

        uint8_t getXG_FIFO_EN();

        void setYG_FIFO_EN(uint8_t value);

        uint8_t getYG_FIFO_EN();

        void setZG_FIFO_EN(uint8_t value);

        uint8_t getZG_FIFO_EN();

        void setACCEL_FIFO_EN(uint8_t value);

        uint8_t getACCEL_FIFO_EN();

        void setSLV2_FIFO_EN(uint8_t value);

        uint8_t getSLV2_FIFO_EN();

        void setSLV1_FIFO_EN(uint8_t value);

        uint8_t getSLV1_FIFO_EN();

        void setSLV0_FIFO_EN(uint8_t value);

        uint8_t getSLV0_FIFO_EN();

        uint16_t getFIFO_Count();

        void setFIFO_Enable(uint8_t value);

        uint8_t getFIFO_Enable();

        void getFIFO_Data(uint8_t *data, uint8_t length);

        void setFIFO_Reset(uint8_t value);

        uint8_t getFIFO_Reset();

    private:
        I2cPort *i2c;
        uint8_t device_address;

    };
}  // namespace cacaosd_mpu6050
#endif	/* MPU6050_H */

