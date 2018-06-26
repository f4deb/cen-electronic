#ifndef DISTANCE_SENSOR_DEVICE_INTERFACE_H
#define DISTANCE_SENSOR_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

// List of DISTANCE SENSOR COMMAND HEADER

/**
* Defines the header to read the distance sensor
*/

#define COMMAND_READ_DISTANCE_SENSOR         'r'

/**
* Defines the header to set the distance sensor Alert 
*/
#define COMMAND_SET_DISTANCE_SENSOR_ALERT    'w'

/**
* Interface for Device.
*/
DeviceInterface* getDistanceSensorDeviceInterface(void);

#endif    

