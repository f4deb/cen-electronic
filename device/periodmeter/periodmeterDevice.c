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
    if (commandHeader == COMMAND_MESURE_PERIODMETER) {
        ackCommand(outputStream, PERIOD_METER_HEADER, COMMAND_MESURE_PERIODMETER);

        unsigned char periodMeterIndex = readHex2(inputStream);
        unsigned int value = readHex2(inputStream);
        
        //setPeriodMeterValue(periodMeterIndex,value);
             
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
