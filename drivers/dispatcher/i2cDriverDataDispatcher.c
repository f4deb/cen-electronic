#include "stdlib.h"
#include "stdbool.h"

#include "driverDataDispatcher.h"
#include "driverDataDispatcherList.h"
#include "i2cDriverDataDispatcher.h"
#include "remoteDriverDataDispatcher.h"

// Drivers
#include "../../drivers/driver.h"

// I2C management
#include "../../common/i2c/master/i2cMaster.h"
#include "../../common/i2c/master/i2cMasterInputStream.h"
#include "../../common/i2c/master/i2cMasterOutputStream.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/transmitMode.h"

/**
 * The stream to send data through I2C
 */
// temp buffer, shared by every i2cDriverDataDispatcher
// useful only for copyInputToOutputStream !
static unsigned char i2cTempBufferArray[I2C_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH];
static Buffer i2cTempBuffer;
static I2cMasterOutputStream i2cMasterOutputStream;
static I2cMasterInputStream i2cMasterInputStream;

DriverDataDispatcher* addI2CDriverDataDispatcher(
        const char* dispatcherName,
        Buffer* i2cMasterInputBuffer,
        unsigned char (*i2cMasterInputBufferArray)[],
        unsigned char i2cMasterInputBufferLength,
        OutputStream* outputStream,
        InputStream* inputStream,
        I2cBusConnection* i2cBusConnection) {


    // Init the output Stream : I2C Master -> I2C Slave(address)
    initBuffer(&i2cTempBuffer, (unsigned char(*)[]) & i2cTempBufferArray, I2C_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH, "I2C Master Output", "global");
    initMasterI2cOutputStream(&i2cMasterOutputStream, i2cBusConnection, outputStream, &i2cTempBuffer);

    // Init the input Stream : I2C Slave (address) -> I2C Master
    initBuffer(i2cMasterInputBuffer, (unsigned char(*)[]) i2cMasterInputBufferArray, i2cMasterInputBufferLength, "I2C Master Input", dispatcherName);
    initMasterI2cInputStream(&i2cMasterInputStream, i2cBusConnection, i2cMasterInputBuffer, inputStream);

    // Clear previous data to avoid buffer from the other board provided by error at the initialization
    // TODO : Clarify this, to avoid to read some bad data until we are ready !
    clearInputStream(inputStream);

    DriverDataDispatcher* result = addDriverDataDispatcher(
            TRANSMIT_I2C,
            dispatcherName,
            NULL,
            i2cBusConnection->i2cAddress,
            inputStream,
            outputStream,
            remoteDriverDataDispatcherTransmit
            );
    return result;
}

