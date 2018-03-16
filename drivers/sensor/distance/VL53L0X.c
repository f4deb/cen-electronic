#include "VL53L0X.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/i2c/i2cConstants.h"
#include "../../../common/i2c/master/i2cMaster.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/math/bcdUtils.h"

/**
 * Get the internal I2cBusConnection.
 * @param distance the distance structure (to simulate POO Programming).
 * @private
 */
I2cBusConnection* _VL53L0X_getI2cBusConnection(Distance* distance) {
    I2cBusConnection* result = (I2cBusConnection*) distance->object;
    
    return result;
}

int _VL53L0X_readSensorValue(Distance* distance) {    

    I2cBusConnection* i2cBusConnection = _VL53L0X_getI2cBusConnection(distance);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    
    int result = 0;
    char lm75aMsb = 0;
    char lm75aLsb;    
  
    portableMasterStartI2C(i2cBusConnection);
    
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, VL53L0X_READ_SENSOR_REGISTER);
    WaitI2C(i2cBus);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    //I2C read Address
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress | 0x01);
    WaitI2C(i2cBus);
    lm75aMsb = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    lm75aLsb = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    result = lm75aMsb;
    return result;
}

void _VL53L0X_writeAlertLimit(Distance* distance, int distanceSensorAlertValue) {
    I2cBusConnection* i2cBusConnection = _VL53L0X_getI2cBusConnection(distance);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, VL53L0X_OVER_DISTANCE_SENSOR_REGISTER);
    WaitI2C(i2cBus);
    unsigned char value = bcd2CharToDec(distanceSensorAlertValue);
    portableMasterWriteI2C(i2cBusConnection, value);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, 0x00);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, VL53L0X_CONFIGURATION_SENSOR_REGISTER);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, OS_POLARITY_HIGH);

    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
}

void initDistanceVL53L0X(Distance* distance, I2cBusConnection* i2cBusConnection) {
    initDistance(distance, _VL53L0X_readSensorValue, _VL53L0X_writeAlertLimit, i2cBusConnection);
}
