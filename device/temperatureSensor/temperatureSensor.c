#include "temperatureSensor.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../drivers/sensor/LM75A.h"

void printTemperatureSensor(OutputStream* outputStream){
    appendDec(outputStream, getTemperatureSensor());
}


