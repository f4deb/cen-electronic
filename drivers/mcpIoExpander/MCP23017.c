#include "MCP23017.h"

#include "../../common/motorI2c/motorI2c.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

I2cBusConnection* _pcm23017GetI2cBusConnection(MotorI2c* motorI2c) {
    I2cBusConnection* result = (I2cBusConnection*) motorI2c->object;

    return result;
}

/**
 * @see motorI2c.h
 * @private
 * Read the hour and the date from the Pcm23017, and store in the structure.
 * @param motorI2c the motorI2c
 */
MotorI2cData* _readPcm23017MotorI2c(MotorI2c* motorI2c) {
    I2cBusConnection* i2cBusConnection = _pcm23017GetI2cBusConnection(motorI2c);

    MotorI2cData* motorI2cData = &(motorI2c->motorI2cData);

    
    return motorI2cData;
}

/**
 * @see motorI2c.h
 * @private
 * Set the MotorI2c into the Pcm23017.
 * @param motorI2c the new value of motorI2c
 */
void _writePcm23017MotorI2c(MotorI2c* motorI2c) {
    I2cBusConnection* i2cBusConnection = _pcm23017GetI2cBusConnection(motorI2c);

    MotorI2cData* motorI2cData = &(motorI2c->motorI2cData);

   
}

void initIoExpanderMCP23017(MotorI2c* motorI2c, I2cBusConnection* i2cBusConnection) {
    initMotorI2c(motorI2c, _writePcm23017MotorI2c, _readPcm23017MotorI2c, (int*) i2cBusConnection);
}

