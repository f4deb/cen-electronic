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
            setFunction("Write Led", 2, 0);
            setArgumentUnsignedHex2(0, "Led_index");
            setArgumentUnsignedHex2(1, "Led_state");
        }
        return commandLengthValueForMode(mode, 4, 0);
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
