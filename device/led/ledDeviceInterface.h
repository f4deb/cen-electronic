#ifndef LED_DEVICE_INTERFACE_H
#define LED_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Set the state 1 of an Led. */
#define COMMAND_SET_LED_STATE         'S'

/**
* Interface for the Device
* @return the Interface for the Led device.
*/
DeviceInterface* getLedDeviceInterface();

#endif
