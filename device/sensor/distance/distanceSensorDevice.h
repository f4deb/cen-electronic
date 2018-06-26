#ifndef DISTANCE_SENSOR_DEVICE_H
#define DISTANCE_SENSOR_DEVICE_H

#include "../../../common/sensor/distance/distance.h"

#include "../../../device/deviceDescriptor.h"

/**
* Returns a descriptor on the DistanceSensor device.
* @param distance a wrapper on distance device
*/
DeviceDescriptor* getDistanceSensorDeviceDescriptor(Distance* distance);

#endif    

