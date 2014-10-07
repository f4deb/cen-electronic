#include "clockDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"

const char* getClockDeviceName (){
    return "Clock";
}

int deviceClockGetInterface(char header, int mode, bool fillDeviceArgumentList){
    if (header == COMMAND_READ_CLOCK ) {
        if (fillDeviceArgumentList) {
            setFunction("Clock Read", 0, 12);
            setResultUnsignedHex2(0, "HOUR");
            setResultUnsignedChar1(1, "");
            setResultUnsignedHex2(2, "MINUTE");
            setResultUnsignedChar1(3, "");
            setResultUnsignedHex2(4, "SECONDE");
            setResultUnsignedChar1(5, "");
            setResultUnsignedHex2(6, "DAY");
            setResultUnsignedChar1(7, "");
            setResultUnsignedHex2(8, "MONTH");
            setResultUnsignedChar1(9, "");
            setResultUnsignedHex2(10, "YEAR");
            setResultUnsignedChar1(11, "");
        }
        return commandLengthValueForMode(mode, 0, 18);
    } else if (header == COMMAND_WRITE_HOUR) {
        if (fillDeviceArgumentList) {
            setFunction("Hour Write", 3, 0);
            setArgumentUnsignedHex2(0, "HOUR");
            setArgumentUnsignedHex2(1, "MINUTE");
            setArgumentUnsignedHex2(2, "SECONDE");
        }
        return commandLengthValueForMode(mode, 6, 0);
    } else if (header == COMMAND_WRITE_DATE) {
        if (fillDeviceArgumentList) {
            setFunction("Date Write", 3, 0);
            setArgumentUnsignedHex2(0, "DAY");
            setArgumentUnsignedHex2(1, "MONTH");
            setArgumentUnsignedHex2(2, "YEAR");
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
