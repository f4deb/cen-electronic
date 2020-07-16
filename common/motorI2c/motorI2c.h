#ifndef MOTORI2C_H
#define	MOTORI2C_H

#include <stdbool.h>

/**
 * Universal motorI2c definition.
 */
typedef struct {
    char mcp23017Address;
    char mcp23017Register;
    char mcp23017Data;
} Mcp23017Data;

// forward declaration
struct MotorI2c;
typedef struct MotorI2c MotorI2c;

/**
 * Update the specific motorI2c hardware with value from the struct.
 * @param motorI2cParam the pointer on motorI2c object
 */
typedef void WriteMotorI2cFunction(MotorI2c* motorI2cParam);

/**
 * Update the software motorI2c structure from the hardware.
 * @param motorI2cParam the pointer on motorI2c object.
 * @return the pointer on Mcp23017Data with refresh data (from hardware)
 */
typedef Mcp23017Data* ReadMotorI2cFunction(MotorI2c* motorI2cParam);

/**
 * Defines the contract for a motorI2c object.
 */
struct MotorI2c {
    /** The function which must be used to write the content of data to the hardware. */
    WriteMotorI2cFunction* writeMotorI2c;
    /** The function which must be used to read the content in the hardware to store in the mcp23017Data */
    ReadMotorI2cFunction* readMotorI2c;
    /** The content with all values. */
    Mcp23017Data mcp23017Data;
    /** A pointer on generic object (for example to store I2cBus, timer ...). */
    int* object;
};

/**
 * Returns true if the motorI2c is initialized (if the fields of callbacks are NOT NULL), false else.
 * @param motorI2c a pointer on the MotorI2c object (Simulates POO programming) 
 * @return true if the motorI2c is initialized (if the fields of callbacks are NOT NULL), false else.
 */
bool isMotorI2cInitialized(MotorI2c* motorI2c);

/**
 * Initializes (Constructor in POO).
 * @param motorI2cParam a pointer on motorI2c structure to initialize it.
 * @param writeMotorI2cFunction a pointer on the writeMotorI2cFunction
 * @param readMotorI2cFunction a pointer on the readMotorI2cFunction
 * @param object A pointer on generic object (for example to store I2cBus ...).
 */
void initMotorI2c(MotorI2c* motorI2cParam, WriteMotorI2cFunction* writeMotorI2cFunction, ReadMotorI2cFunction* readMotorI2cFunction, int* object);

#endif