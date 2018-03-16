#include "distance.h"

#include <stdlib.h>

#include "../../../common/error/error.h"

void initDistance(Distance* distance,
    DistanceReadSensorValueFunction* readSensorValue,
    DistanceWriteAlertLimitFunction* writeAlertLimit,
    void* object) {
    if (distance == NULL) {
        writeError(TEMPERATURE_NULL);
        return;
    }  
    distance->readSensorValue = readSensorValue;
    distance->writeAlertLimit = writeAlertLimit;
    distance->object = object;
}
