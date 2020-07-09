#include <stdbool.h>
#include <stdlib.h>

#include <plib.h>

#include "motorI2cDevice.h"
#include "motorI2cDeviceInterface.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/motorI2c/motorI2c.h"
#include "../../common/error/error.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logLevel.h"
#include "../../common/log/logger.h"

#include "../../device/device.h"

// FORWARD DECLARATION
MotorI2c* getMotorI2cFromDeviceDescriptor(void);

void _deviceMotorI2cCheckInitialized() {
    MotorI2c* motorI2c = getMotorI2cFromDeviceDescriptor();
    if (motorI2c == NULL) {
        writeError(MOTORI2C_NULL);
    }
    if (!isMotorI2cInitialized(motorI2c)) {
        writeError(MOTORI2C_NOT_INITIALIZED);
    }
}

void deviceMotorI2cInit(void) {
    _deviceMotorI2cCheckInitialized();
}

void deviceMotorI2cShutDown(void) {
}

bool isMotorI2cDeviceOk(void) {
    return true;
}

void deviceMotorI2cHandleRawData(unsigned char header, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    MotorI2c* motorI2c = getMotorI2cFromDeviceDescriptor();
    _deviceMotorI2cCheckInitialized();
    if (header == COMMAND_READ_MOTORI2C) {
            while (1){
        TRISBbits.TRISB0 = 0;
        LATBbits.LATB0 = 0;
        TRISBbits.TRISB1 = 0;
        LATBbits.LATB1 = 1;
        delayMilliSecs(500);
        TRISBbits.TRISB0 = 0;
        LATBbits.LATB0 = 1;
        TRISBbits.TRISB1 = 0;
        LATBbits.LATB1 = 0;
        delayMilliSecs(500);
    }        
        ackCommand(outputStream, MOTORI2C_DEVICE_HEADER, COMMAND_READ_MOTORI2C);
        MotorI2cData* motorI2cData = motorI2c->readMotorI2c(motorI2c);
        appendHex2(outputStream, motorI2cData->hour);
        append(outputStream, ':');
        appendHex2(outputStream, motorI2cData->minute);
        append(outputStream, ':');
        appendHex2(outputStream, motorI2cData->second);
        append(outputStream, ' ');
        appendHex2(outputStream, motorI2cData->day);
        append(outputStream, '/');
        appendHex2(outputStream, motorI2cData->month);
        append(outputStream, '/');
        appendHex2(outputStream, motorI2cData->year);
    } else if (header == COMMAND_WRITE_MOTORI2C) {
        MotorI2cData* motorI2cData = &(motorI2c->motorI2cData);
        motorI2cData->hour = readHex2(inputStream);
        motorI2cData->minute = readHex2(inputStream);
        motorI2cData->second = readHex2(inputStream);

        ackCommand(outputStream, MOTORI2C_DEVICE_HEADER, COMMAND_WRITE_MOTORI2C);
        motorI2c->writeMotorI2c(motorI2c);
    } else if (header == COMMAND_STOP_MOTORI2C) {
        MotorI2cData* motorI2cData = &(motorI2c->motorI2cData);
        motorI2cData->day = readHex2(inputStream);
        motorI2cData->month = readHex2(inputStream);
        motorI2cData->year = readHex2(inputStream);

        ackCommand(outputStream, MOTORI2C_DEVICE_HEADER, COMMAND_STOP_MOTORI2C);
        motorI2c->writeMotorI2c(motorI2c);
    }
}

static DeviceDescriptor descriptor;

DeviceDescriptor* getMotorI2cDeviceDescriptor(MotorI2c* motorI2c) {
    initDeviceDescriptor(&descriptor,
            &deviceMotorI2cInit,
            &deviceMotorI2cShutDown,
            &isMotorI2cDeviceOk,
            &deviceMotorI2cHandleRawData,
            (int*) motorI2c);

    return &descriptor;
}

MotorI2c* getMotorI2cFromDeviceDescriptor(void) {
    return (MotorI2c*) (descriptor.object);
}

