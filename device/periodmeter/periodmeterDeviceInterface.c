#include "periodmeterDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getPeriodMeterDeviceName(void) {
    return "PERIOD METER";
}

int devicePeriodMeterGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_MESURE_PERIODMETER) {
        if (fillDeviceArgumentList) {
            setFunction("Read the Period", 0, 1);
            setResultUnsignedHex4(0, "Value(us)");
        }
        return commandLengthValueForMode(mode,0 ,4);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = PERIOD_METER_HEADER,
    .deviceGetName = &getPeriodMeterDeviceName,
    .deviceGetInterface = &devicePeriodMeterGetInterface
};

DeviceInterface* getPeriodMeterDeviceInterface() {
    return &deviceInterface;
}