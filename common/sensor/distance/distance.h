#ifndef DISTANCE_H
#define DISTANCE_H

// forward declaration
struct Distance;
typedef struct Distance Distance;

/**
 * Get the value from the distance sensor
 * @return distance  the value from the distance sensor
 */
typedef int DistanceReadSensorValueFunction (Distance* distance);

/** 
 * Set the distance to know if we are above the value.
 * @param distanceSensorAlert the new limit for the distance
 */
typedef void DistanceWriteAlertLimitFunction(Distance* distance, int distanceSensorAlert);

/**
 * Distance sensor wrapping.
 */
struct Distance {
    /** The function which must be used to read the value of the distance (in celcius degree). */
    DistanceReadSensorValueFunction* readSensorValue;
    /** The function which must be used to write the alert limit of the distance sensor (in celcius degree). */
    DistanceWriteAlertLimitFunction* writeAlertLimit;
    /** A pointer on generic object (for example to store I2cBus ...). */
    void* object;
};

/**
 * Initialize the distance object wrapper.
 * @param distance the pointer on distance object (POO Programming)
 * @param readSensorValue the pointer on the callback function to read the value of the distance (in celcius degree).
 * @param writeAlertLimit the pointer on the callback function to write the alert limit of the distance sensor (in celcius degree).
 */
void initDistance(Distance* distance,
                     DistanceReadSensorValueFunction* readSensorValue,
                     DistanceWriteAlertLimitFunction* writeAlertLimit,
                     void* object);

#endif
