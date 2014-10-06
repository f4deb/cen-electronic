#include <peripheral/legacy/i2c_legacy.h>

#include "../../drivers/clock/PCF8563.h"
#include "clock.h"
#include "clockDevice.h"
#include "clockDeviceInterface.h"

#include "../../common/cmd/commonCommand.h"

// Others includes

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"


void deviceClockInit(void) {
    // Place here Hardware Initialization
}

void deviceClockShutDown(void) {
    // Place here Hardware Shutdown
}

bool isClockDeviceOk(void) {
    // Place code to check if the device is ok, if we can not know, we expect that it's ok and we return "true"
    return true;
}

void deviceClockHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream){
        if (header == COMMAND_READ_CLOCK) {
        // Read XXX Parameters from the inputStream
            
        // Do the Job
        ackCommand(outputStream, CLOCK_DEVICE_HEADER, COMMAND_READ_CLOCK);
        appendHex2(outputStream,hor.ti_hour);
        append(outputStream,':');
        appendHex2(outputStream,hor.ti_min);
        append(outputStream,':');
        appendHex2(outputStream,hor.ti_sec);
        append(outputStream,' ');
        appendHex2(outputStream,hor.ti_day);
        append(outputStream,'/');
        appendHex2(outputStream,hor.ti_month);
        append(outputStream,'/');
        appendHex2(outputStream,hor.ti_year);
        append(outputStream,' ');
    } else if (header == COMMAND_WRITE_HOUR) {
        // Read XXX Parameters from the inputStream
        hor.ti_hour = readHex2(inputStream);
        hor.ti_min = readHex2(inputStream);
        hor.ti_sec = readHex2(inputStream);
        // Do the Job
        ackCommand(outputStream, CLOCK_DEVICE_HEADER, COMMAND_WRITE_HOUR);
        setClock();
    } else if (header == COMMAND_WRITE_DATE) {
        // Read XXX Parameters from the inputStream
        hor.ti_day = readHex2(inputStream);
        hor.ti_month = readHex2(inputStream);
        hor.ti_year = readHex2(inputStream);
        // Do the Job
        ackCommand(outputStream, CLOCK_DEVICE_HEADER, COMMAND_WRITE_DATE);
        setClock();
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceClockInit,
    .deviceShutDown = &deviceClockShutDown,
    .deviceIsOk = &isClockDeviceOk,
    .deviceHandleRawData = &deviceClockHandleRawData,
};

DeviceDescriptor* getClockDeviceDescriptor() {
    return &descriptor;
}




/*
static DeviceDescriptor descriptor = {
    .deviceInit = &deviceClockInit,
    .deviceShutDown = &deviceClockShutDown,
    .deviceIsOk = &isClockDeviceOk,
    .deviceHandleRawData = &deviceClockHandleRawData,
};



DeviceDescriptor* getClockDeviceDescriptor() {
    return &descriptor;
}*/