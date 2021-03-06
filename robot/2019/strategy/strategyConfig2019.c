#include "strategyConfig2019.h"

#include "../../../common/error/error.h"

#include "../../../motion/motionConstants.h"
#include "../../../motion/extended/bsplineMotion.h"

#include "../../../robot/config/robotConfig.h"

const float MOTION_ACCELERATION_FACTORS_2019[8] = {MOTION_ACCELERATION_FACTOR_0, MOTION_ACCELERATION_FACTOR_1, MOTION_ACCELERATION_FACTOR_2, MOTION_ACCELERATION_FACTOR_3,
    MOTION_ACCELERATION_FACTOR_4, MOTION_ACCELERATION_FACTOR_5, MOTION_ACCELERATION_FACTOR_6, MOTION_ACCELERATION_FACTOR_7};

const float MOTION_SPEED_FACTORS_2019[8] = {MOTION_SPEED_FACTOR_0, MOTION_SPEED_FACTOR_1, MOTION_SPEED_FACTOR_2, MOTION_SPEED_FACTOR_3,
    MOTION_SPEED_FACTOR_4, MOTION_SPEED_FACTOR_5, MOTION_SPEED_FACTOR_6, MOTION_SPEED_FACTOR_7};

// If Sonar Mask = 0x00, then we consider that Sonar is off
const float SONAR_DISTANCE_FACTORS_2019[4] = {8.0f, 0.50f, 0.75f, 1.0f};

float getAccelerationFactor2019(RobotConfig* robotConfig) {
    unsigned int config = robotConfig->robotConfigReadInt(robotConfig);
    unsigned int accelerationFactorIndex = (config & CONFIG_SPEED_MASK) >> CONFIG_SPEED_SHIFT_BIT_VALUE;
    if (accelerationFactorIndex >= 0 && accelerationFactorIndex <= 7) {
        return MOTION_ACCELERATION_FACTORS_2019[accelerationFactorIndex];
    }
    writeError(ROBOT_CONFIG_ERROR);

    return MOTION_ACCELERATION_FACTOR_0;
}

float getSpeedFactor2019(RobotConfig* robotConfig) {
    unsigned int config = robotConfig->robotConfigReadInt(robotConfig);
    unsigned int speedFactorIndex = (config & CONFIG_SPEED_MASK) >> CONFIG_SPEED_SHIFT_BIT_VALUE;
    if (speedFactorIndex >= 0 && speedFactorIndex <= 7) {
        return MOTION_SPEED_FACTORS_2019[speedFactorIndex];
    }
    writeError(ROBOT_CONFIG_ERROR);

    return MOTION_SPEED_FACTOR_0;
}

float getSonarDistanceCheckFactor2019(RobotConfig* robotConfig) {
    unsigned int config = robotConfig->robotConfigReadInt(robotConfig);
    unsigned int sonarDistanceIndex = (config & CONFIG_SONAR_MASK) >> CONFIG_SONAR_SHIFT_BIT_VALUE;
    if (sonarDistanceIndex >= 0 && sonarDistanceIndex <= 3) {
        return SONAR_DISTANCE_FACTORS_2019[sonarDistanceIndex];
    }
    writeError(ROBOT_CONFIG_ERROR);

    return 8.0f;
}