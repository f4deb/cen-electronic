#ifndef TEMPERATURESENSOR_H
#define	TEMPERATURESENSOR_H

/**
 * Universal TemperatureSensor definition.
 */
typedef struct {
    int temperatureAmbient;
    int temperatureAlertMin;
    int temperatureAlertMax;
} TemperatureSensor;

/**
 * Returns the singleton for TemperatureSensor.
 * @returns the singleton for TemperatureSensor.
 */
TemperatureSensor* getGlobalTemperatureSensor();

/**
 * get the value from the temperature sensor
 * @return temperature  the value from the temperature sensor
 */
int getTemperatureSensor (void);

#endif