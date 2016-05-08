#ifndef PERIODMETER_H    /* Guard against multiple inclusion */
#define PERIODMETER_H

#include "../../device/deviceDescriptor.h"

/**
* Returns a descriptor on the device for the LED.
* @return a descriptor on the device for the LED
*/
DeviceDescriptor* getPeriodMeterDeviceDescriptor();

#endif