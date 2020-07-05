#include "motorI2cDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getMotorI2cDeviceName(void) {
    return "MotorI2c";
}

int deviceMotorI2cGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_READ_MOTORI2C) {
        if (fillDeviceArgumentList) {
            setFunction("MotorI2c Read", 0, 11);
            setResultUnsignedHex2(0, "HOUR");
            setResultSeparator(1);
            setResultUnsignedHex2(2, "MINUTE");
            setResultSeparator(3);
            setResultUnsignedHex2(4, "SECOND");
            setResultSeparator(5);
            setResultUnsignedHex2(6, "DAY");
            setResultSeparator(7);
            setResultUnsignedHex2(8, "MONTH");
            setResultSeparator(9);
            setResultUnsignedHex2(10, "YEAR");
        }
        return commandLengthValueForMode(mode, 0, 17);
    } else if (commandHeader == COMMAND_WRITE_MOTORI2C) {
        if (fillDeviceArgumentList) {
            setFunction("Time Write", 3, 0);
            setArgumentUnsignedHex2(0, "HOUR");
            setArgumentUnsignedHex2(1, "MINUTE");
            setArgumentUnsignedHex2(2, "SECOND");
        }
        return commandLengthValueForMode(mode, 6, 0);
    } else if (commandHeader == COMMAND_STOP_MOTORI2C) {
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
    .deviceGetName = &getMotorI2cDeviceName,
    .deviceHeader = MOTORI2C_DEVICE_HEADER,
    .deviceGetInterface = &deviceMotorI2cGetInterface
};

DeviceInterface* getMotorI2cDeviceInterface(void) {
    return &deviceInterface;
}
