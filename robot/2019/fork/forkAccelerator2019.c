#include "forkAccelerator2019.h"
#include "fork2019.h"

#include <stdbool.h>

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/error/error.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/pwm/servo/servoPwm.h"
#include "../../../common/pwm/servo/servoList.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/timer/delayTimer.h"

#include "../../../robot/2019/elevator/elevator2019.h"

bool fork2019AcceleratorDrop(ServoList* servoList, unsigned int firstLeftRightServoIndex, unsigned int secondLeftRightServoIndex) {
    // We wait because all actions must be finished before going to the next step !
    bool wait = true;

    // Elevator Up to the max
    moveElevatorUp(servoList, wait);

    // First release

    // Fork Push On to release at the right angle
    moveForkPushOn(servoList, firstLeftRightServoIndex, wait);

    // Let the puck fall
    moveForkBack(servoList, firstLeftRightServoIndex, wait);

    // Fork Push Off to avoid to block the elevator
    moveForkPushOff(servoList, firstLeftRightServoIndex, wait);

    // Prepare for the second release
    moveElevatorAcceleratorSecondDrop(servoList, wait);

    // Second release : we take the second Servo Index
    // Fork Push On to release at the right angle
    moveForkPushOn(servoList, secondLeftRightServoIndex, wait);

    // Let the puck fall
    moveForkBack(servoList, secondLeftRightServoIndex, wait);

    // We don't wait, we would do it during the next move
    moveForkPushOff(servoList, secondLeftRightServoIndex, false);

    return true;
}