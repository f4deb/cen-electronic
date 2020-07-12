#ifndef MCP23017_H
#define MCP23017_H

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"

#include "../../common/io/outputStream.h"

#include "../../common/motorI2c/motorI2c.h"

// MCP23017 REGISTER
#define IODIRA      0X00
#define IODIRB      0X01
#define IPOLA       0x02
#define IPOLB       0x03
#define GPINTENA    0x04
#define GPINTENB    0x05
#define DEFVALA     0x06
#define DEFVALB     0x07
#define INTCONA     0x08
#define INTCONB     0x09
#define IOCON-1     0x0A
#define IOCON-2     0x0B
#define GPPUA       0x0C
#define GPPUB       0x0D
#define INTFA       0x0E
#define INTFB       0x0F
#define INTCAPA     0x10
#define INTCAPB     0x11
#define GPIOA       0x12
#define GPIOB       0x13
#define OLATA       0x14
#define OLATB       0x15

/**
 * Initializes a mcp object with a motorI2c hardware component.
 * @param motorI2c a pointer on the clock structure.
 */
void initIoExpanderMCP23017(MotorI2c* motorI2c, I2cBusConnection* i2cBusConnection);

#endif
