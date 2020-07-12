#include "motorI2cDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getMotorI2cDeviceName(void) {
    return "MotorI2c";
}

int deviceMotorI2cGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_READ_SWITCH) {
        if (fillDeviceArgumentList) {
            setFunction("MotorSwitch Read", 0, 5);
            setResultUnsignedHex4(0, "SPEED");
            setResultSeparator(1);
            setResultUnsignedHex2(2, "DIRECTION");
            setResultSeparator(3);
            setResultUnsignedHex2(4, "CAPTEUR");
        }
        return commandLengthValueForMode(mode, 0, 10);
    } 
    else if (commandHeader == COMMAND_SELECT_SWITCH) {
        if (fillDeviceArgumentList) {
            setFunction("MotorSwitch Select", 0, 5);
            setResultUnsignedHex4(0, "SPEED");
            setResultSeparator(1);
            setResultUnsignedHex2(2, "DIRECTION");
            setResultSeparator(3);
            setResultUnsignedHex2(4, "CAPTEUR");
        }
        return commandLengthValueForMode(mode, 0, 10);
    }     
    else if (commandHeader == COMMAND_WRITE_MOTORI2C) {
        if (fillDeviceArgumentList) {
            setFunction("Motor Write", 3, 0);
            setArgumentUnsignedHex4(0, "SPEED");
            setArgumentUnsignedHex2(1, "DIRECTION");
            setArgumentUnsignedHex2(2, "CAPTEUR");
        }
        return commandLengthValueForMode(mode, 8, 0);
    } else if (commandHeader == COMMAND_STOP_MOTORI2C) {
        if (fillDeviceArgumentList) {
            setFunction("Motor Stop", 3, 0);
            setArgumentUnsignedHex2(0, "SPEED");
            setArgumentUnsignedHex2(1, "DIRECTION");
            setArgumentUnsignedHex2(2, "CAPTEUR");
        }
        return commandLengthValueForMode(mode, 6, 0);
    } else if (commandHeader == COMMAND_DEBUG_MOTORI2C) {
        if (fillDeviceArgumentList) {
            setFunction("Debug", 3, 0);
            setArgumentUnsignedHex2(0, "SPEED");
            setArgumentUnsignedHex2(1, "DIRECTION");
            setArgumentUnsignedHex2(2, "CAPTEUR");
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
