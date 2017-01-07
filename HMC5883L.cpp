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

#include "HMC5883L.h"

namespace cacaosd_hmc5883l {

    HMC5883L::HMC5883L(I2cPort *i2c) {
        this->i2c = i2c;
    }

    HMC5883L::~HMC5883L() {

    }

    uint8_t HMC5883L::getDeviceAddress() const {
        return device_address;
    }

    void HMC5883L::setDeviceAddress(uint8_t device_address) {
        HMC5883L::device_address = device_address;
    }

/** Power on and prepare for general usage.
 * This will prepare the magnetometer with default settings, ready for single-
 * use mode (very low power requirements). Default settings include 8-sample
 * averaging, 15 Hz data output rate, normal measurement bias, a,d 1090 gain (in
 * terms of LSB/Gauss). Be sure to adjust any settings you need specifically
 * after initialization, especially the gain settings if you happen to be seeing
 * a lot of -4096 values (see the datasheet for mor information).
 */
    void HMC5883L::initialize() {
        setSamplesAvarage(SAMPLES_AVARAGE_8);
        setOutputRate(OUTPUT_RATE_4);
        setMeasurementMode(MEASUREMENT_NORMAL);
        setMeasurementGain(GAIN_1090);
        setOperationMode(OPERATION_MODE_CONT);
    }

/** Set number of samples averaged per measurement.
 * @param averaging New samples averaged per measurement setting(0-3 for 1/2/4/8 respectively)
 * @see CONFIG_A
 * @see SAMPLES_AVARAGE_LENGTH
 */
    void HMC5883L::setSamplesAvarage(uint8_t avarage) {
        if (avarage == 0) {
            i2c->writeMoreBits(CONFIG_A, SAMPLES_AVARAGE_1,
                               SAMPLES_AVARAGE_LENGTH, SAMPLES_AVARAGE_START);
        } else if (avarage == 1) {
            i2c->writeMoreBits(CONFIG_A, SAMPLES_AVARAGE_2,
                               SAMPLES_AVARAGE_LENGTH, SAMPLES_AVARAGE_START);
        } else if (avarage == 2) {
            i2c->writeMoreBits(CONFIG_A, SAMPLES_AVARAGE_4,
                               SAMPLES_AVARAGE_LENGTH, SAMPLES_AVARAGE_START);
        } else if (avarage == 3) {
            i2c->writeMoreBits(CONFIG_A, SAMPLES_AVARAGE_8,
                               SAMPLES_AVARAGE_LENGTH, SAMPLES_AVARAGE_START);
        }
    }

/** Get number of samples averaged per measurement.
 * @return Current samples averaged per measurement (0-3 for 1/2/4/8 respectively)
 * @see CONFIG_A
 * @see SAMPLES_AVARAGE_LENGTH
 */
    uint8_t HMC5883L::getSamplesAvarage() const {
        return i2c->readMoreBits(CONFIG_A, SAMPLES_AVARAGE_LENGTH,
                                 SAMPLES_AVARAGE_START);
    }

/** Set data output rate value.
 * @param rate Rate of data output to registers
 * @see getOutputRate()
 * @see CONFIG_A
 * @see OUTPUT_RATE_LENGTH
 */
    void HMC5883L::setOutputRate(uint8_t rate) {
        if (rate == 0) {
            i2c->writeMoreBits(CONFIG_A, OUTPUT_RATE_0,
                               OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
        } else if (rate == 1) {
            i2c->writeMoreBits(CONFIG_A, OUTPUT_RATE_1,
                               OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
        } else if (rate == 2) {
            i2c->writeMoreBits(CONFIG_A, OUTPUT_RATE_2,
                               OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
        } else if (rate == 3) {
            i2c->writeMoreBits(CONFIG_A, OUTPUT_RATE_3,
                               OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
        } else if (rate == 4) {
            i2c->writeMoreBits(CONFIG_A, OUTPUT_RATE_4,
                               OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
        } else if (rate == 5) {
            i2c->writeMoreBits(CONFIG_A, OUTPUT_RATE_5,
                               OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
        } else if (rate == 6) {
            i2c->writeMoreBits(CONFIG_A, OUTPUT_RATE_6,
                               OUTPUT_RATE_LENGTH, OUTPUT_RATE_START);
        } else if (rate == 7) {
            printf("Reserved.\n");
        }
    }

/** Get data output rate value.
 * The Table below shows all selectable output rates in continuous measurement
 * mode. All three channels shall be measured within a given output rate. Other
 * output rates with maximum rate of 160 Hz can be achieved by monitoring DRDY
 * interrupt pin in single measurement mode.
 *
 * Value | Typical Data Output Rate (Hz)
 * ------+------------------------------
 * 0     | 0.75
 * 1     | 1.5
 * 2     | 3
 * 3     | 7.5
 * 4     | 15 (Default)
 * 5     | 30
 * 6     | 75
 * 7     | Not used
 *
 * @return Current rate of data output to registers
 * @see CONFIG_A
 * @see OUTPUT_RATE_LENGTH
 */
    uint8_t HMC5883L::getOutputRate() const {
        return i2c->readMoreBits(CONFIG_A, OUTPUT_RATE_LENGTH,
                                 OUTPUT_RATE_START);
    }

/** Set measurement bias value.
 * @param bias New bias value (0-2 for normal/positive/negative respectively)
 * @see CONFIG_A
 * @see MEASUREMENT_LENGTH
 */
    void HMC5883L::setMeasurementMode(uint8_t mode) {
        if (mode == 0) {
            i2c->writeMoreBits(CONFIG_A, MEASUREMENT_NORMAL,
                               MEASUREMENT_LENGTH, MEASUREMENT_START);
        } else if (mode == 2) {
            i2c->writeMoreBits(CONFIG_A, MEASUREMENT_POSITIVE,
                               MEASUREMENT_LENGTH, MEASUREMENT_START);
        } else if (mode == 3) {
            i2c->writeMoreBits(CONFIG_A, MEASUREMENT_NEGATIVE,
                               MEASUREMENT_LENGTH, MEASUREMENT_START);
        }
    }

/** Get measurement bias value.
 * @return Current bias value (0-2 for normal/positive/negative respectively)
 * @see CONFIG_A
 * @see MEASUREMENT_LENGTH
 */
    uint8_t HMC5883L::getMeasurementMode() const {
        return i2c->readMoreBits(CONFIG_A, MEASUREMENT_LENGTH,
                                 MEASUREMENT_START);
    }

/** Set magnetic field gain value.
 * @param gain New magnetic field gain value
 * @see getMeasurementGain()
 * @see CONFIG_B
 */
    void HMC5883L::setMeasurementGain(uint8_t gain) {
        if (gain == 0) {
            i2c->writeByte(CONFIG_B, (GAIN_1370 << 5));
        } else if (gain == 1) {
            i2c->writeByte(CONFIG_B, (GAIN_1090 << 5));
        } else if (gain == 2) {
            i2c->writeByte(CONFIG_B, (GAIN_820 << 5));
        } else if (gain == 3) {
            i2c->writeByte(CONFIG_B, (GAIN_660 << 5));
        } else if (gain == 4) {
            i2c->writeByte(CONFIG_B, (GAIN_440 << 5));
        } else if (gain == 5) {
            i2c->writeByte(CONFIG_B, (GAIN_390 << 5));
        } else if (gain == 6) {
            i2c->writeByte(CONFIG_B, (GAIN_330 << 5));
        } else if (gain == 7) {
            i2c->writeByte(CONFIG_B, (GAIN_230 << 5));
        }
    }

/** Get magnetic field gain value.
 * The table below shows nominal gain settings. Use the "Gain" column to convert
 * counts to Gauss. Choose a lower gain value (higher GN#) when total field
 * strength causes overflow in one of the data output registers (saturation).
 * The data output range for all settings is 0xF800-0x07FF (-2048 - 2047).
 *
 * Value | Field Range | Gain (LSB/Gauss)
 * ------+-------------+-----------------
 * 0     | +/- 0.88 Ga | 1370
 * 1     | +/- 1.3 Ga  | 1090 (Default)
 * 2     | +/- 1.9 Ga  | 820
 * 3     | +/- 2.5 Ga  | 660
 * 4     | +/- 4.0 Ga  | 440
 * 5     | +/- 4.7 Ga  | 390
 * 6     | +/- 5.6 Ga  | 330
 * 7     | +/- 8.1 Ga  | 230
 *
 * @return Current magnetic field gain value
 * @see CONFIG_B
 * @see GAIN_LENGTH
 */
    uint8_t HMC5883L::getMeasurementGain() const {
        return i2c->readMoreBits(CONFIG_B, GAIN_LENGTH, GAIN_START);
    }

/** Set measurement mode.
 * @param newMode New measurement mode
 * @see getMode()
 * @see OPERATION_MODE_CONT
 * @see OPERATION_MODE_SINGLE
 * @see OPERATION_MODE_IDLE
 * @see MODE_REG
 */
    void HMC5883L::setOperationMode(uint8_t mode) {
        if (mode == 0) {
            i2c->writeByte(MODE_REG, OPERATION_MODE_CONT);
        } else if (mode == 1) {
            i2c->writeByte(MODE_REG, OPERATION_MODE_SINGLE);
        } else if (mode == 2) {
            i2c->writeByte(MODE_REG, OPERATION_MODE_IDLE);
        }
    }

/** Get measurement mode.
 * In continuous-measurement mode, the device continuously performs measurements
 * and places the result in the data register. RDY goes high when new data is
 * placed in all three registers. After a power-on or a write to the mode or
 * configuration register, the first measurement set is available from all three
 * data output registers after a period of 2/fDO and subsequent measurements are
 * available at a frequency of fDO, where fDO is the frequency of data output.
 *
 * When single-measurement mode (default) is selected, device performs a single
 * measurement, sets RDY high and returned to idle mode. Mode register returns
 * to idle mode bit values. The measurement remains in the data output register
 * and RDY remains high until the data output register is read or another
 * measurement is performed.
 *
 * @return Current measurement mode
 * @see MODE_REG
 * @see OPERATION_MODE_LENGTH
 */
    uint8_t HMC5883L::getOperationMode() const {
        return i2c->readMoreBits(MODE_REG, OPERATION_MODE_LENGTH,
                                 OPERATION_MODE_START);
    }

/** Get X-axis heading measurement.
 * @return 16-bit signed integer with X-axis heading
 * @see X_HIGH
 */
    int16_t HMC5883L::getMagnitudeX() const {
        return i2c->readWord(X_HIGH, X_LOW);
    }

/** Get Y-axis heading measurement.
 * @return 16-bit signed integer with Y-axis heading
 * @see Y_HIGH
 */
    int16_t HMC5883L::getMagnitudeY() const {
        return i2c->readWord(Y_HIGH, Y_LOW);
    }

/** Get Z-axis heading measurement.
 * @return 16-bit signed integer with Z-axis heading
 * @see Z_HIGH
 */
    int16_t HMC5883L::getMagnitudeZ() const {
        return i2c->readWord(Z_HIGH, Z_LOW);
    }

/** Get data ready status.
 * This bit is set when data is written to all six data registers, and cleared
 * when the device initiates a write to the data output registers and after one
 * or more of the data output registers are written to. When RDY bit is clear it
 * shall remain cleared for 250 us. DRDY pin can be used as an alternative to
 * the status register for monitoring the device for measurement data.
 * @return Data ready status
 * @see STATUS_REG
 * @see RDY_BIT
 */
    uint8_t HMC5883L::getRDYStatus() const {
        return i2c->readBit(STATUS_REG, RDY_BIT);
    }

/** Get data output register lock status.
 * This bit is set when this some but not all for of the six data output
 * registers have been read. When this bit is set, the six data output registers
 * are locked and any new data will not be placed in these register until one of
 * three conditions are met: one, all six bytes have been read or the mode
 * changed, two, the mode is changed, or three, the measurement configuration is
 * changed.
 * @return Data output register lock status
 * @see STATUS_REG
 * @see LOCK_BIT
 */
    uint8_t HMC5883L::getLockStatus() const {
        return i2c->readBit(STATUS_REG, LOCK_BIT);
    }

/** Get identification byte A
 * @return ID_A byte (should be 01001000, ASCII value 'H')
 */
    uint8_t HMC5883L::getIDA() const {
        return i2c->readByte(ID_REG_A);
    }

/** Get identification byte B
 * @return ID_A byte (should be 00110100, ASCII value '4')
 */
    uint8_t HMC5883L::getIDB() const {
        return i2c->readByte(ID_REG_B);
    }

/** Get identification byte C
 * @return ID_A byte (should be 00110011, ASCII value '3')
 */
    uint8_t HMC5883L::getIDC() const {
        return i2c->readByte(ID_REG_C);
    }

}  // namespace cacaosd_hmc5883l
