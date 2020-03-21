#ifndef TEMPERATURE_SENSOR_DEVICE_INTERFACE_H
#define TEMPERATURE_SENSOR_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

// List of TEMPERATURE SENSOR COMMAND HEADER

/**
 * Defines the header to read the temperature sensor
 */

#define COMMAND_READ_TEMPERATURE_SENSOR         'r'

/**
 * Defines the header to set the temperature sensor Alert 
 */
#define COMMAND_SET_TEMPERATURE_SENSOR_ALERT    'w'

/**
 * Interface for Device.
 */
DeviceInterface* getTemperatureSensorDeviceInterface(void);

#endif    

