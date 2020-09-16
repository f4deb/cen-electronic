#ifndef PCA9685NXP_H
#define PCA9685NXP_H

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"

#include "../../common/io/outputStream.h"

#include "../../common/motorI2c/motorI2c.h"

// PCA9685 REGISTER 
#define PCA9685_MODE1           0x00
#define PCA9685_MODE1_MASK_RESTART    0b10000000   // 0 : restart disabled, 1 : enabled
#define PCA9685_MODE1_MASK_EXTCLK     0b01000000   // Use External Clock (1) or not (0)
#define PCA9685_MODE1_MASK_AUTO_INC   0b00100000   // AUTO_INCREMENT or not
#define PCA9685_MODE1_MASK_SLEEP      0b00010000   // SLEEP
#define PCA9685_MODE1_MASK_SUB1       0b00001000   // PCA9685 responds to I2C-bus subaddress 1
#define PCA9685_MODE1_MASK_SUB2       0b00000100   // PCA9685 responds to I2C-bus subaddress 2
#define PCA9685_MODE1_MASK_SUB3       0b00000010   // PCA9685 responds to I2C-bus subaddress 3
#define PCA9685_MODE1_MASK_ALLCALL    0b00000001   // PCA9685 responds to LED All Call I2C-bus address

// OTHER REGISTER
#define PCA9685_MODE2          0x01
#define PCA9685_SUBADR1        0x02
#define PCA9685_SUBADR2        0x03
#define PCA9685_SUBADR3        0x04
#define PCA9885_ALLCALLADR     0x05

// First LED Index
#define LED0_ON_L              0x6
#define LED0_ON_H              0x7
#define LED0_OFF_L             0x8
#define LED0_OFF_H             0x9

// For all LED
#define ALLLED_ON_L           0xFA
#define ALLLED_ON_H           0xFB
#define ALLLED_OFF_L          0xFC
#define ALLLED_OFF_H          0xFD

// FREQUENCY    
#define PCA9685_PRESCALE       0xFE

// SOFTWARE RESET 
#define PCA9685_SOFTWARE_RESET 0b00000110


/**
 * Initializes a mcp object with a motorI2c hardware component.
 * @param motorI2c a pointer on the clock structure.
 */
void initPwmPCA9685(MotorI2cPwm* motorI2cPwm, I2cBusConnection* i2cBusConnection);

#endif
