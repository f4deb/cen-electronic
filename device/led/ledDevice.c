#include <stdbool.h>
#include <p32xxxx.h>

#include "ledDevice.h"
#include "ledDeviceInterface.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"


// DEVICE INTERFACE

void initLed( void ) {

}

void stopLed( void ) {

}

bool isLedDeviceOk ( void ) {
    return true;
}

void deviceLedHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_SET_LED_STATE) {
        signed int ledIndex = readSignedHex2(inputStream);
        signed int ledState = readSignedHex2(inputStream);
        TRISCbits.TRISC14 = 0;
        PORTCbits.RC14 = !PORTCbits.RC14;
        TRISDbits.TRISD11 = 0;
        PORTDbits.RD11 = !PORTCbits.RC14;
        appendAck(outputStream);
        append(outputStream, COMMAND_SET_LED_STATE);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initLed,
    .deviceShutDown = &stopLed,
    .deviceIsOk = &isLedDeviceOk,
    .deviceHandleRawData = &deviceLedHandleRawData,
};

DeviceDescriptor* getLedDeviceDescriptor() {
    return &descriptor;
}

