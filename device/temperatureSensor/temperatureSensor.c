#include "temperatureSensor.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../drivers/sensor/LM75A.h"

/** Singleton of temperatureSensor (private) */
static TemperatureSensor globalTemperatureSensor;

TemperatureSensor* getGlobalTemperatureSensor() {
    return &globalTemperatureSensor;
}

void printTemperatureSensor(OutputStream* outputStream){
    char temperature = 0;
    temperature = getTemperatureSensor();
    appendDec(outputStream, temperature);
    
}

void setTemperatureAlertLimit(int temperatureMin, int temperatureMax){
    
}
