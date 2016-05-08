#ifndef PERIODMETER_DEVICEINTERFACE_H
#define PERIODMETER_DEVICEINTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Get the value of TIMER1 INPUT*/
#define COMMAND_MESURE_PERIODMETER                   'w'

/**
* Interface for the Device
* @return the Interface for the LED device.
*/
DeviceInterface* getPeriodMeterDeviceInterface();

#endif