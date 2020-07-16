#include "motorI2cDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getMotorI2cDeviceName(void) {
    return "MotorI2c";
}

int deviceMotorI2cGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_READ_MCP23017) {
        if (fillDeviceArgumentList) {
            setFunction("MCP23017 Read", 2, 1);
            setArgumentUnsignedHex2(0, "MCP23017 Address");
            setArgumentUnsignedHex2(1, "MCP23017 Register");

            setResultUnsignedHex2(0, "MCP23017 Data");
        }
        return commandLengthValueForMode(mode, 4, 2);
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
    else if (commandHeader == COMMAND_WRITE_MCP23017) {
        if (fillDeviceArgumentList) {
            setFunction("Motor Write", 3, 0);
            setArgumentUnsignedHex2(0, "MCP23017 Address");
            setArgumentUnsignedHex2(1, "MCP23017 Register");
            setArgumentUnsignedHex2(2, "MCP23017 Data");
        }
        return commandLengthValueForMode(mode, 6, 0);
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
