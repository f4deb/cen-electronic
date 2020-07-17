#include "MCP23017.h"

#include <plib.h>
#include "../../common/motorI2c/motorI2c.h"

#include "../../common/delay/cenDelay.h"
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
Mcp23017Data* _readPcm23017MotorI2c(MotorI2c* motorI2c) {
    I2cBusConnection* i2cBusConnection = _pcm23017GetI2cBusConnection(motorI2c);

    Mcp23017Data* mcp23017Data = &(motorI2c->mcp23017Data);

    portableMasterWaitSendI2C(i2cBusConnection);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, MCP23017_ADDRESS_7);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, 0x12);
    WaitI2cBusConnection(i2cBusConnection);
    
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, MCP23017_ADDRESS_7 +1);
    WaitI2cBusConnection(i2cBusConnection);
    mcp23017Data->mcp23017Data = portableMasterReadI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    
    
;
    return mcp23017Data;
}

/**
 * @see motorI2c.h
 * @private
 * Set the MotorI2c into the Pcm23017.
 * @param motorI2c the new value of motorI2c
 */
void _writePcm23017MotorI2c(MotorI2c* motorI2c) {
    I2cBusConnection* i2cBusConnection = _pcm23017GetI2cBusConnection(motorI2c);
    Mcp23017Data* mcp23017Data = &(motorI2c->mcp23017Data);
  
    portableMasterWaitSendI2C(i2cBusConnection);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, mcp23017Data->mcp23017Address);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, mcp23017Data->mcp23017Register);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, mcp23017Data->mcp23017Data);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);  
}

void initIoExpanderMCP23017(MotorI2c* motorI2c, I2cBusConnection* i2cBusConnection) {
    initMotorI2c(motorI2c, _writePcm23017MotorI2c, _readPcm23017MotorI2c, (int*) i2cBusConnection);
}

