#include <stdbool.h>

#include "dataDispatcherDevice.h"
#include "dataDispatcherDeviceInterface.h"

#include "../../common/error/error.h"

#include "../../common/i2c/i2cDebug.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/reader.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/logHandler.h"
#include "../../common/log/loggerDebug.h"

#include "../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../drivers/dispatcher/driverDataDispatcherDebug.h"

#include "../../device/device.h"
#include "../../device/deviceConstants.h"
#include "../../device/deviceUsage.h"

void deviceDataDispatcherInit(void) {
}

void deviceDataDispatcherShutDown(void) {
}

bool deviceDataDispatcherIsOk(void) {
    return true;
}

void deviceDataDispatcherHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // Dispatcher List
    if (header == COMMAND_DISPATCHER_LIST) {
        ackCommand(outputStream, SYSTEM_DEBUG_DEVICE_HEADER, COMMAND_DISPATCHER_LIST);
        DriverDataDispatcherList* dispatcherList = getDispatcherList();
        printDriverDataDispatcherList(getInfoOutputStreamLogger(), dispatcherList);         
    }
    else if (header == COMMAND_PING_DISPATCHER_INDEX) {
        // Handle directly by DriverStreamListener => Throw an error
        writeError(DISPATCHER_PING_MUST_BE_HANDLE_IN_DRIVER_STREAM_LISTENER);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceDataDispatcherInit,
    .deviceShutDown = &deviceDataDispatcherShutDown,
    .deviceIsOk = &deviceDataDispatcherIsOk,
    .deviceHandleRawData = &deviceDataDispatcherHandleRawData,
};

DeviceDescriptor* getDataDispatcherDeviceDescriptor(void) {
    return &descriptor;
}
