#include <stdbool.h>

#include "servoDevice.h"
#include "servoDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/pwm/pwmPic.h"
#include "../../common/pwm/servo/servoList.h"
#include "../../common/pwm/servo/servoPwm.h"
#include "../../common/pwm/servo/servoPwmDebug.h"

#include "../../device/device.h"
#include "../../device/deviceConstants.h"

// forward declaration
ServoList* getServoDeviceServoList(void);

void deviceServoInit(void) {
    // initPwmForServo(servoEnabledMask, PWM_SERVO_MIDDLE_POSITION);
}

void deviceServoShutDown(void) {
}

bool deviceServoIsOk(void) {
    return true;
}

void deviceServoHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // WRITE COMMANDS
    if (commandHeader == SERVO_COMMAND_WRITE) {
        ServoList* servoList = getServoDeviceServoList();
        unsigned int servoIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        unsigned int servoSpeed = readHex2(inputStream);
        checkIsSeparator(inputStream);
        unsigned int servoValue = readHex4(inputStream);
        if (servoIndex == SERVO_ALL_INDEX) {
            pwmServoAll(servoList, servoSpeed, servoValue);
        } else {
            Servo* servo = getServo(servoList, servoIndex);
            pwmServo(servo, servoSpeed, servoValue, false);
        }
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_WRITE);
    } else if (commandHeader == SERVO_COMMAND_WRITE_MAX_SPEED_UNDER_LOAD) {
        ServoList* servoList = getServoDeviceServoList();
        unsigned int servoIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        int servoMaxSpeedUnderLoad = readHex2(inputStream);
        Servo* servo = getServo(servoList, servoIndex);
        servo->maxSpeedUnderLoad = servoMaxSpeedUnderLoad;
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_WRITE_MAX_SPEED_UNDER_LOAD);
    } else if (commandHeader == SERVO_COMMAND_WRITE_COMPACT) {
        unsigned int servoValue = readHex4(inputStream);
        ServoList* servoList = getServoDeviceServoList();
        pwmServoAll(servoList, PWM_SERVO_SPEED_MAX, servoValue);
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_WRITE_COMPACT);
    }
    // ENABLE / DISABLE
    if (commandHeader == SERVO_COMMAND_WRITE_ENABLE_DISABLE) {
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_WRITE_ENABLE_DISABLE);
        ServoList* servoList = getServoDeviceServoList();
        unsigned int servoIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        bool enabled = readBool(inputStream);
        if (servoIndex == SERVO_ALL_INDEX) {
            servoEnableAll(servoList, enabled);
        } else {
            Servo* servo = getServo(servoList, servoIndex);
            pwmServoSetEnabled(servo, enabled);
        }
    } else if (commandHeader == SERVO_COMMAND_ENABLE_DISABLE_ALL) {
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_ENABLE_DISABLE_ALL);
        ServoList* servoList = getServoDeviceServoList();
        bool enabled = readBool(inputStream);
        servoEnableAll(servoList, enabled);
    }// READ COMMANDS
    else if (commandHeader == SERVO_COMMAND_GET_COUNT) {
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_GET_COUNT);
        ServoList* servoList = getServoDeviceServoList();
        unsigned int servoCount = getServoCount(servoList);
        appendHex2(outputStream, servoCount);

    } else if (commandHeader == SERVO_COMMAND_READ) {
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_READ);
        unsigned int servoIndex = readHex2(inputStream);
        ServoList* servoList = getServoDeviceServoList();
        Servo* servo = getServo(servoList, servoIndex);
        unsigned int speed = pwmServoReadTargetSpeed(servo);
        unsigned int currentPosition = pwmServoReadCurrentPosition(servo);
        unsigned int targetPosition = pwmServoReadTargetPosition(servo);

        appendHex2(outputStream, servoIndex);
        appendSeparator(outputStream);
        appendHex2(outputStream, speed);
        appendSeparator(outputStream);
        appendHex4(outputStream, currentPosition);
        appendSeparator(outputStream);
        appendHex4(outputStream, targetPosition);
    } else if (commandHeader == SERVO_COMMAND_READ_SPEED) {
        unsigned int servoIndex = readHex2(inputStream);
        ServoList* servoList = getServoDeviceServoList();
        Servo* servo = getServo(servoList, servoIndex);
        unsigned int speed = pwmServoReadTargetSpeed(servo);

        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_READ_SPEED);
        appendHex2(outputStream, speed);
    } else if (commandHeader == SERVO_COMMAND_READ_MAX_SPEED_UNDER_LOAD) {
        unsigned int servoIndex = readHex2(inputStream);
        ServoList* servoList = getServoDeviceServoList();
        Servo* servo = getServo(servoList, servoIndex);
        unsigned int maxSpeedUnderLoad = pwmServoReadMaxSpeedUnderLoad(servo);

        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_READ_MAX_SPEED_UNDER_LOAD);
        appendHex2(outputStream, maxSpeedUnderLoad);
    } else if (commandHeader == SERVO_COMMAND_READ_CURRENT_POSITION) {
        unsigned int servoIndex = readHex2(inputStream);
        ServoList* servoList = getServoDeviceServoList();
        Servo* servo = getServo(servoList, servoIndex);
        int currentPosition = pwmServoReadCurrentPosition(servo);

        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_READ_CURRENT_POSITION);
        appendHex4(outputStream, currentPosition);
    } else if (commandHeader == SERVO_COMMAND_READ_TARGET_POSITION) {
        unsigned int servoIndex = readHex2(inputStream);
        ServoList* servoList = getServoDeviceServoList();
        Servo* servo = getServo(servoList, servoIndex);
        int targetPosition = pwmServoReadTargetPosition(servo);

        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_READ_TARGET_POSITION);
        appendHex4(outputStream, targetPosition);
    }// DEBUG COMMANDS
    else if (commandHeader == SERVO_COMMAND_TEST) {
        ServoList* servoList = getServoDeviceServoList();
        testAllPwmServos(servoList);
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_TEST);
    } else if (commandHeader == SERVO_COMMAND_GET_TIME_TO_REACH_UNDER_LOAD) {
        unsigned int servoIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        unsigned int servoTargetPosition = readHex4(inputStream);

        ServoList* servoList = getServoDeviceServoList();
        Servo* servo = getServo(servoList, servoIndex);

        unsigned int timeToReachUnderLoad = pwmServoComputeTimeMilliSecondsToReachTargetPosition(servo, servoTargetPosition);
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_GET_TIME_TO_REACH_UNDER_LOAD);
        appendHex4(outputStream, timeToReachUnderLoad);
    } else if (commandHeader == SERVO_COMMAND_DEBUG) {
        ServoList* servoList = getServoDeviceServoList();
        printServoList(getInfoOutputStreamLogger(), servoList);
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_DEBUG);
    }
}

static DeviceDescriptor descriptor;

/**
 * @private
 */
ServoList* getServoDeviceServoList(void) {
    return (ServoList*) descriptor.object;
}

DeviceDescriptor* getServoDeviceDescriptor(ServoList* servoList) {
    initDeviceDescriptor(&descriptor,
            &deviceServoInit,
            &deviceServoShutDown,
            &deviceServoIsOk,
            &deviceServoHandleRawData,
            (int*) servoList);

    return &descriptor;
}
