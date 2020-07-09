#ifndef MCP23017_H
#define MCP23017_H

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"

#include "../../common/io/outputStream.h"

#include "../../common/motorI2c/motorI2c.h"

#define MCP23017_READ_ADDRESS            MCP23017_ADDRESS_7 + 1

#define MCP23017_REGISTER          0x02

/**
 * Initializes a mcp object with a motorI2c hardware component.
 * @param motorI2c a pointer on the clock structure.
 */
void initIoExpanderMCP23017(MotorI2c* motorI2c, I2cBusConnection* i2cBusConnection);

#endif
