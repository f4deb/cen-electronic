#include "INA3221.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/i2c/i2cConstants.h"
#include "../../../common/i2c/master/i2cMaster.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/math/bcdUtils.h"

/**
 * Get the internal I2cBusConnection.
 * @param current the current structure (to simulate POO Programming).
 * @private
 */
I2cBusConnection* _INA3221_getI2cBusConnection(Current* current) {
    I2cBusConnection* result = (I2cBusConnection*) current->object;
    
    return result;
}

int _INA3221_readSensorValue(Current* current) {
    I2cBusConnection* i2cBusConnection = _INA3221_getI2cBusConnection(current);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    int result = 0;
    char INA3221Msb = 0;
    char INA3221Lsb = 0;

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, CHANNEL1_SHUNT_VOLTAGE);
    WaitI2C(i2cBus);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    //I2C read Address
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress | 0x01);
    WaitI2C(i2cBus);
    INA3221Msb = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    // INA3221Lsb = 
    portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    result = INA3221Msb;
    return result;
}

void _INA3221_writeAlertLimit(Current* current, int currentSensorValue) {
    I2cBusConnection* i2cBusConnection = _INA3221_getI2cBusConnection(current);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, INA3221_OVER_CURRENT_SENSOR_REGISTER);
    WaitI2C(i2cBus);
    unsigned char value = bcd2CharToDec(currentSensorValue);
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
    portableMasterWriteI2C(i2cBusConnection, INA3221_CONFIGURATION_SENSOR_REGISTER);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, OS_POLARITY_HIGH);

    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
}

void initCurrent_INA3221(Current* current, I2cBusConnection* i2cBusConnection) {
    initCurrent(current, _INA3221_readSensorValue, _INA3221_writeAlertLimit, i2cBusConnection);
}
