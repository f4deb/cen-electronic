/* 
 * File:   clock.h
 * Author: f4deb
 *
 * Created on 4 octobre 2014, 19:02
 */

#ifndef CLOCK_DEVICE_INTERFACE_H
#define	CLOCK_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"


// The CLOCK DEVICE HEADER

#define CLOCK_DEVICE_HEADER     'C'


// List of CLOCK COMMAND HEADER

/**
* Defines the header to read the clock
*/

#define COMMAND_READ_CLOCK         'r'

/**
* Defines the header to write the clock.
*/
#define COMMAND_WRITE_CLOCK         'w'

// Function to get the specific Device Interface

/**
* Interface for Device.
*/
DeviceInterface* getClockDeviceInterface();

#endif	/* CLOCK_DEVICE_INTERFACE_H */

