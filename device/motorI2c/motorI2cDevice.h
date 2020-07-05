#ifndef MOTORI2CDEVICE_H
#define	MOTORI2CDEVICE_H

#include "../../common/motorI2c/motorI2c.h"

#include "../../device/deviceDescriptor.h"

/**
 * Returns a descriptor on the MOTORI2C device.
 * @param motorI2c the pointer on the motorI2c object.
 * @return a descriptor to handle with hardware the motorI2c object.
 */
DeviceDescriptor* getMotorI2cDeviceDescriptor(MotorI2c* motorI2c);

#endif

