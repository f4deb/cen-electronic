#include "robotConfig.h"
#include <stdbool.h>

#include "../../common/io/binaryPrintWriter.h"
#include "../../common/io/outputStream.h"

#include "../../common/io/printWriter.h"

#include "../../robot/robot.h"

void initRobotConfig(RobotConfig* robotConfig,
        enum RobotType robotType,
        robotConfigReadIntFunction* robotConfigReadInt, robotConfigWriteIntFunction* robotConfigWriteInt) {
    setRobotType(robotType);
    robotConfig->robotConfigReadInt = robotConfigReadInt;
    robotConfig->robotConfigWriteInt = robotConfigWriteInt;
}

bool isConfigSet(RobotConfig* robotConfig, unsigned int configMask) {
    unsigned int config = getConfigValue(robotConfig);
    int intersection = (config & configMask);
    return intersection != 0;
}

unsigned int getConfigValue(RobotConfig* robotConfig) {
    return robotConfig->robotConfigReadInt(robotConfig);
    ;
}

bool isSonarActivated(RobotConfig* robotConfig) {
    return (getConfigValue(robotConfig) & CONFIG_SONAR_MASK) != 0;
}
