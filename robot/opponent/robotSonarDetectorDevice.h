#ifndef ROBOT_SONAR_DETECTOR_DEVICE_H
#define ROBOT_SONAR_DETECTOR_DEVICE_H

#include "../../device/device.h"


#define ROBOT_SONAR_DETECTOR_DEVICE_HISTORY_SIZE         3

#define ROBOT_SONAR_DETECTOR_DEVICE_HISTORY_THRESHOLD     2

#define ROBOT_SONAR_DETECTOR_DEVICE_DISTANCE_THRESHOLD     70

#define ROBOT_SONAR_DETECTOR_TIMER_SKIP_FOR_NEW_DETECTION 60

DeviceDescriptor* getRobotSonarDetectorDeviceDescriptor();

bool notifyObstacle();

void setSonarStatus(unsigned char aSonarStatus);

#endif
