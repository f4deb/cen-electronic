#ifndef PID_MOTION_ERROR_H
#define PID_MOTION_ERROR_H

#include "../../common/io/outputStream.h"

/**
 * Defines the structs which stores the errors with the pid computation.
 */
typedef struct PidMotionError {
    /** Stores the previous error */
    float previousError;
    /** The error between normal speed and real speed */
    float error;
    /** The derivative error between normal speed and real speed */
    float derivativeError;
    /** The integral error between normal speed and real speed */
    float integralError;
} PidMotionError;

/**
 * Clear the pidMotionError structure.
 * @param pidMotionError the structure to (re)initialize
 */
void clearMotionError(PidMotionError* pidMotionError);

#endif
