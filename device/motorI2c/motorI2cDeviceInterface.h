#ifndef MOTORI2CDEVICEINTERFACE_H
#define	MOTORI2CDEVICEINTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

// List of MOTORI2C COMMAND HEADER

/**
 * Defines the header to read the MOTORI2C switch.
 */
#define COMMAND_READ_MCP23017         'r'

/**
 * Defines the header to select the MOTORI2C switch.
 */
#define COMMAND_SELECT_SWITCH         'R'

/**
 * Defines the header to write the speed and direction on the MOTORI2C.
 */
#define COMMAND_WRITE_MCP23017         'w'

/**
 * Defines the header to Stop the MOTORI2C.
 */
#define COMMAND_STOP_MOTORI2C         's'

/**
 * Defines the header to print the debug on the MOTORI2C.
 */
#define COMMAND_DEBUG_MOTORI2C         'd'

// Function to get the specific Device Interface

/**
 * Interface for Device.
 */
DeviceInterface* getMotorI2cDeviceInterface();

#endif	/* MOTORI2CDEVICEINTERFACE_H */

