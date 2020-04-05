#ifndef TRAJECTORY_DEVICE_H
#define TRAJECTORY_DEVICE_H

#include "../../../common/io/outputStream.h"

#include "../../../common/math/cenMath.h"

#include "../../../device/deviceDescriptor.h"

// ADJUST VALUE

#define TRAJECTORY_DEVICE_ADJUST_DISTANCE_THRESHOLD    20.0f

// 3 degree max
#define TRAJECTORY_DEVICE_ADJUST_ANGLE_THRESHOLD       ((PI / 180.0f) * 3.0f)

// Only to use the same format of data between TrajectoryDevice and MotionDevice
#define NOTIFICATION_STATUS_FAKE                          0x0F

// DEVICE INTERFACE

/**
 * Returns a device descriptor on trajectory device.
 */
DeviceDescriptor* getTrajectoryDeviceDescriptor(void);

/**
 * Notify the absolute position without the header.
 */
void notifyAbsolutePositionAndSpeed(OutputStream* outputStream, char status);

// NOTIFICATION

bool trajectoryNotifyIfEnabledAndTreshold(OutputStream* notificationOutputStream);


#endif
