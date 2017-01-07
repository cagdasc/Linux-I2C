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

#ifndef HMC5883L_H
#define HMC5883L_H

#include "I2cPort.h"

#define HMC5883L_DEV_ADD 0x1E
#define CONFIG_A 0x00
#define CONFIG_B 0x01
#define MODE_REG 0x02
#define X_HIGH 0x03
#define X_LOW 0x04
#define Z_HIGH 0x05
#define Z_LOW 0x06
#define Y_HIGH 0x07
#define Y_LOW 0x08
#define STATUS_REG 0x09
#define ID_REG_A 0x0A
#define ID_REG_B 0x0B
#define ID_REG_C 0x0C

#define SAMPLES_AVARAGE_START 0x05
#define SAMPLES_AVARAGE_LENGTH 0x02
#define SAMPLES_AVARAGE_1 0x00
#define SAMPLES_AVARAGE_2 0x01
#define SAMPLES_AVARAGE_4 0x02
#define SAMPLES_AVARAGE_8 0x03

#define OUTPUT_RATE_START 0x02
#define OUTPUT_RATE_LENGTH 0x03
#define OUTPUT_RATE_0 0x00
#define OUTPUT_RATE_1 0x01
#define OUTPUT_RATE_2 0x02
#define OUTPUT_RATE_3 0x03
#define OUTPUT_RATE_4 0x04
#define OUTPUT_RATE_5 0x05
#define OUTPUT_RATE_6 0x06
#define OUTPUT_RATE_7 0x07

#define MEASUREMENT_START 0x00
#define MEASUREMENT_LENGTH 0x02
#define MEASUREMENT_NORMAL 0x00
#define MEASUREMENT_POSITIVE 0x01
#define MEASUREMENT_NEGATIVE 0x02

#define GAIN_START 0x05
#define GAIN_LENGTH 0x03
#define GAIN_1370 0x00
#define GAIN_1090 0x01
#define GAIN_820 0x02
#define GAIN_660 0x03
#define GAIN_440 0x04
#define GAIN_390 0x05
#define GAIN_330 0x06
#define GAIN_230 0x07

#define OPERATION_MODE_START 0x00
#define OPERATION_MODE_LENGTH 0x02
#define OPERATION_MODE_CONT 0x00
#define OPERATION_MODE_SINGLE 0x01
#define OPERATION_MODE_IDLE 0x02

#define RDY_BIT 0x00
#define LOCK_BIT 0x01
using namespace cacaosd_i2cport;

namespace cacaosd_hmc5883l {

    class HMC5883L {
    public:
        HMC5883L(I2cPort *i2c);

        virtual ~HMC5883L();

        void initialize();

        uint8_t getDeviceAddress() const;

        void setDeviceAddress(uint8_t device_address);

        void setSamplesAvarage(uint8_t avarage);

        uint8_t getSamplesAvarage() const;

        void setOutputRate(uint8_t rate);

        uint8_t getOutputRate() const;

        void setMeasurementMode(uint8_t mode);

        uint8_t getMeasurementMode() const;

        void setMeasurementGain(uint8_t gain);

        uint8_t getMeasurementGain() const;

        void setOperationMode(uint8_t mode);

        uint8_t getOperationMode() const;

        int16_t getMagnitudeX() const;

        int16_t getMagnitudeY() const;

        int16_t getMagnitudeZ() const;

        uint8_t getRDYStatus() const;

        uint8_t getLockStatus() const;

        uint8_t getIDA() const;

        uint8_t getIDB() const;

        uint8_t getIDC() const;

    private:
        I2cPort *i2c;
        uint8_t device_address;
    };
}  // namespace cacaosd_hmc5883l
#endif	/* HMC5883L_H */

