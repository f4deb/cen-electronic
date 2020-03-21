#ifndef CLOCK_DEVICE_INTERFACE_H
#define CLOCK_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

// List of CLOCK COMMAND HEADER

/**
 * Defines the header to read the clock.
 */
#define COMMAND_READ_CLOCK         'r'

/**
 * Defines the header to write the time on the clock.
 */
#define COMMAND_WRITE_TIME         't'

/**
 * Defines the header to write the Hours on the clock.
 */
#define COMMAND_WRITE_DATE         'd'

// Function to get the specific Device Interface

/**
 * Interface for Device.
 */
DeviceInterface* getClockDeviceInterface();

#endif
