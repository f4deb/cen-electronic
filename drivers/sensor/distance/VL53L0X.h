// SENSOR DISTANCE
#ifndef VL53L0X_H
#define VL53L0X_H

#include "../../../common/sensor/distance/distance.h"

#include "../../../common/i2c/i2cCommon.h"

#define VL53L0X_READ_SENSOR_REGISTER              0x00  //NOK
#define VL53L0X_CONFIGURATION_SENSOR_REGISTER     0x01  //NOK
#define VL53L0X_HYSTERESIS_SENSOR_REGISTER        0x02  //NOK
#define VL53L0X_OVER_DISTANCE_SENSOR_REGISTER   0x03  //NOK

// Overtemp Shutdown output
//  0  OS active LOW
//  1  OS active HIGH
#define OS_POLARITY_LOW 0x00  //NOK
#define OS_POLARITY_HIGH 0x04  //NOK

/**
 * Initializes a distance structure for a VL53L0X sensor.
 * @param distance a pointer on the distance object (POO simulation)
 * @param i2cBusConnection a pointer on the i2cBusConnection
 */
void initDistanceVL53L0X(Distance* distance, I2cBusConnection* i2cBusConnection);

#endif

