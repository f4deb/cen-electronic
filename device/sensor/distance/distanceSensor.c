#include "distanceSensor.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

void printDistanceSensor(OutputStream* outputStream, Distance* distance){
    appendHex2(outputStream, distance->readSensorValue(distance));
}
