#include "temperatureSensorDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"

const char* getTemperatureSensorDeviceName (){
    return "Temperature Sensor";
}

int deviceTemperatureSensorGetInterface(char header, int mode, bool fillDeviceArgumentList){
    if (header == COMMAND_READ_TEMPERATURE_SENSOR ) {
        if (fillDeviceArgumentList) {
            setFunction("Temperature Sensor Read", 0, 1);
            setResultUnsignedHex2(0, "TEMPERATURE");
        }
        return commandLengthValueForMode(mode, 0, 2);
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
