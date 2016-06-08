#include <stdbool.h>

#include "periodmeterDevice.h"
#include "periodmeterDeviceInterface.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/logHandler.h"

#include "../device.h"


// DEVICE INTERFACE

void initPeriodMeter( void ) {

}

void stopPeriodMeter( void ) {

}

bool isPeriodMeterDeviceOk ( void ) {
    return true;
}

unsigned int readPeriodMeter(unsigned char periodMeterIndex) {
    int value = 0;

    return value;
}

void deviceperiodMeterHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
    int periodMeterIndex = 1; //timer1
    int value = 0;      // init value
    
    if (commandHeader == COMMAND_MESURE_PERIODMETER) {
        ackCommand(outputStream, PERIOD_METER_HEADER, COMMAND_MESURE_PERIODMETER);

        // read the period on TIMER1
        value = readPeriodMeter(periodMeterIndex);
        appendHex4(outputStream, value);             
    }       
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initPeriodMeter,
    .deviceShutDown = &stopPeriodMeter,
    .deviceIsOk = &isPeriodMeterDeviceOk,
    .deviceHandleRawData = &deviceperiodMeterHandleRawData,
};

DeviceDescriptor* getPeriodMeterDeviceDescriptor() {
    return &descriptor;
}
