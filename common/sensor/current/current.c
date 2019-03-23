#include "current.h"

#include <stdlib.h>

#include "../../../common/error/error.h"

void initCurrent(Current* current,
    CurrentReadSensorValueFunction* readSensorValue,
    CurrentWriteAlertLimitFunction* writeAlertLimit,
    void* object) {
    if (current == NULL) {
        writeError(TEMPERATURE_NULL);
        return;
    }  
    current->readSensorValue = readSensorValue;
    current->writeAlertLimit = writeAlertLimit;
    current->object = object;
}
