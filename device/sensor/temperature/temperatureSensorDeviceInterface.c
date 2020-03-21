#include <stdbool.h>

#include "temperatureSensorDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* getTemperatureSensorDeviceName(void) {
    return "Temperature Sensor";
}

int deviceTemperatureSensorGetInterface(unsigned char header, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (header == COMMAND_READ_TEMPERATURE_SENSOR) {
        if (fillDeviceArgumentList) {
            setFunction("Temperature Sensor Read", 0, 1);
            setResultUnsignedHex2(0, "TEMPERATURE");
        }
        return commandLengthValueForMode(mode, 0, 2);
    } else if (header == COMMAND_SET_TEMPERATURE_SENSOR_ALERT) {
        if (fillDeviceArgumentList) {
            setFunction("Set Alert Temperature Sensor", 1, 0);
            setArgumentUnsignedHex2(0, "Alert Temperature");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = TEMPERATURE_SENSOR_DEVICE_HEADER,
    .deviceGetName = &getTemperatureSensorDeviceName,
    .deviceGetInterface = &deviceTemperatureSensorGetInterface
};

DeviceInterface* getTemperatureSensorDeviceInterface() {
    return &deviceInterface;
}
