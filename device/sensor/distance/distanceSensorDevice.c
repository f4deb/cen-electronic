#include <stdbool.h>

#include "distanceSensor.h"
#include "distanceSensorDevice.h"
#include "distanceSensorDeviceInterface.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/i2c/i2cCommon.h"

#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/sensor/distance/distance.h"

#include "../../../device/device.h"

static Distance* distance;

void deviceDistanceSensorInit(void) {
}

void deviceDistanceSensorShutDown(void) {
}

bool isDistanceSensorDeviceOk(void) {
    return true;
}

void deviceDistanceSensorHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream){
    if (header == COMMAND_READ_DISTANCE_SENSOR) {
        ackCommand(outputStream, DISTANCE_SENSOR_DEVICE_HEADER, COMMAND_READ_DISTANCE_SENSOR);
        unsigned char value = (unsigned char) distance->readSensorValue(distance);
        appendHex2(outputStream, value);
    } else if (header == COMMAND_SET_DISTANCE_SENSOR_ALERT) {
        char distanceSensorAlert = readHex2(inputStream);
        ackCommand(outputStream, DISTANCE_SENSOR_DEVICE_HEADER, COMMAND_SET_DISTANCE_SENSOR_ALERT);
        distance->writeAlertLimit(distance, distanceSensorAlert);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceDistanceSensorInit,
    .deviceShutDown = &deviceDistanceSensorShutDown,
    .deviceIsOk = &isDistanceSensorDeviceOk,
    .deviceHandleRawData = &deviceDistanceSensorHandleRawData,
};

DeviceDescriptor* getDistanceSensorDeviceDescriptor(Distance* distanceParam) {
    distance = distanceParam;
    return &descriptor;
}
