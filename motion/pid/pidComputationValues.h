#ifndef PID_COMPUTATION_VALUES_H
#define PID_COMPUTATION_VALUES_H

#include "instructionType.h"
#include "pidMotionError.h"
#include "pidCurrentValues.h"
#include "endDetection/motionEndInfo.h"

/**
 * All current values about the current motion in progress.
 */
typedef struct PidComputationValues {
    // ONLY ONE VALUE AT A TIME
    // theta error (distance for normal trajectory, and along Y axis for Spline Curve)
    float thetaError;
    // angle error
    float alphaError;
    // theta error (only for Curve implementation)
    // determine the distance between normal trajectory tangent line
    // and real trajectory tangent line (=> X Axis)
    float thetaXAxisError;
    // store the time of the pid timer when it was computer
    float pidTime;
    // Store error of each motion
    PidMotionError errors[INSTRUCTION_TYPE_COUNT];
    // store tension / position / current speed
    PidCurrentValues currentValues[INSTRUCTION_TYPE_COUNT];
    // Store Detection of end of trajectory
    MotionEndInfo motionEnd[INSTRUCTION_TYPE_COUNT];
} PidComputationValues;

#endif
