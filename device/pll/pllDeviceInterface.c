#include "pllDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getPllDeviceName(void) {
    return "Frequency Synthetiser";
}

int devicePllGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == WRITE_FREQUENCY_PLL) {
        if (fillDeviceArgumentList) {            
            setFunction("PLLAcceleration", 0, 5);
            setResultUnsignedHex4(0, "Acceleration X");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "Acceleration Y");
            setResultSeparator(3);
            setResultUnsignedHex4(4, "Acceleration Z");
        }
        return commandLengthValueForMode(mode, 0, 14);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = PLL_DEVICE_HEADER,
    .deviceGetName = &getPllDeviceName,
    .deviceGetInterface = &devicePllGetInterface
};

DeviceInterface* getPllDeviceInterface(void) {
    return &deviceInterface;
}