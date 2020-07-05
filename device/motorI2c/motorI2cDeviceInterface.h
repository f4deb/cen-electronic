#ifndef MOTORI2CDEVICEINTERFACE_H
#define	MOTORI2CDEVICEINTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

// List of MOTORI2C COMMAND HEADER

/**
 * Defines the header to read the MOTORI2C.
 */
#define COMMAND_READ_MOTORI2C         'r'

/**
 * Defines the header to write the time on the MOTORI2C.
 */
#define COMMAND_WRITE_MOTORI2C         'w'

/**
 * Defines the header to write the Hours on the MOTORI2C.
 */
#define COMMAND_STOP_MOTORI2C         's'

// Function to get the specific Device Interface

/**
 * Interface for Device.
 */
DeviceInterface* getMotorI2cDeviceInterface();

#endif	/* MOTORI2CDEVICEINTERFACE_H */

