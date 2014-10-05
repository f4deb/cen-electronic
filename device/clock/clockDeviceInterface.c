#include "clockDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"

const char* getClockDeviceName (){
    return "Clock";
}

int deviceClockGetInterface(char header, int mode, bool fillDeviceArgumentList){
    if (header == COMMAND_READ_CLOCK ) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Clock Read");
        }
        return 0;
    } else if (header == COMMAND_WRITE_CLOCK) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunction("Clock Write",3,0);
            setArgumentUnsignedHex2(0, "HOUR");
            setArgumentUnsignedHex2(1, "MINUTE");
            setArgumentUnsignedHex2(2, "SECONDE");
        }
        return commandLengthValueForMode(mode, 6, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = CLOCK_DEVICE_HEADER,
    .deviceGetName = &getClockDeviceName,
    .deviceGetInterface = &deviceClockGetInterface
};

DeviceInterface* getClockDeviceInterface() {
    return &deviceInterface;
}
