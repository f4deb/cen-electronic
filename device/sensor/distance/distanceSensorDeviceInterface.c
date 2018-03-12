#include <stdbool.h>

#include "distanceSensorDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* getDistanceSensorDeviceName(void) {
    return "Distance Sensor";
}

int deviceDistanceSensorGetInterface(char header, DeviceInterfaceMode mode, bool fillDeviceArgumentList){
    if (header == COMMAND_READ_DISTANCE_SENSOR ) {
        if (fillDeviceArgumentList) {
            setFunction("Distance Sensor Read", 0, 1);
            setResultUnsignedHex2(0, "DISTANCE");
        }
        return commandLengthValueForMode(mode, 0, 2);
    } else if (header == COMMAND_SET_DISTANCE_SENSOR_ALERT) {
        if (fillDeviceArgumentList) {
            setFunction("Set Alert Distance Sensor", 1, 0);
            setArgumentUnsignedHex2(0, "Alert Distance");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = DISTANCE_SENSOR_DEVICE_HEADER,
    .deviceGetName = &getDistanceSensorDeviceName,
    .deviceGetInterface = &deviceDistanceSensorGetInterface
};

DeviceInterface* getDistanceSensorDeviceInterface() {
    return &deviceInterface;
}
