#include "ledDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getLedDeviceName(void) {
    return "LED";
}

int deviceLedGetInterface(char header, int mode,
        bool fillDeviceArgumentList) {
    if (header == COMMAND_SET_LED_STATE) {
        if (fillDeviceArgumentList) {
            setFunction("SetLed", 2, 0);
            setArgumentUnsignedHex2(0, "Led_idx");
            setArgumentUnsignedHex2(1, "0/1");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = LED_DEVICE_HEADER,
    .deviceGetName = &getLedDeviceName,
    .deviceGetInterface = &deviceLedGetInterface
};

DeviceInterface* getLedDeviceInterface() {
    return &deviceInterface;
}