#ifndef COMMON_PLL_H
#define COMMON_PLL_H

#include <stdbool.h>

/**
 * Universal PLL definition.
 */
typedef struct {
    int accel_X;
    int accel_Y;
    int accel_Z;
    int accel_gyro_X;
    int accel_gyro_Y;
    int accel_gyro_Z;
    int temperature;
    float rall;  //rotation about the X-axis      phi
    float pitch;  // rotation about the Y-axis    theta
    float yaw;  //rotation about the Z-axis       psi
} PllData;

// forward declaration
struct Pll;
typedef struct Pll Pll;

/**
 * initialise the specific PLL hardware.
 * @param pllParam the pointer on PLL object
 */
typedef void InitPLLFunction(Pll* pllParam);

/**
 * Update the specific PLLhardware with value from the struct.
 * @param pllParam the pointer on Pll object
 */
typedef PllData* GetAccelPLLFunction(Pll* pllParam);



/**
 * Defines the contract for a Pll object.
 */
struct Pll {
    /** the function which must be used to initialise the hardwre PLL */
    InitPLLFunction* initPLL;
    /** The function which must be used to write the content of data to the hardware. */
    GetAccelPLLFunction* getAccelPLL;    
    /** The content with all values. */    
    PllData pllData;
    /** A pointer on generic object (for example to store I2cBus ...). */
    int* object;
};

/**
 * Returns true if the pll is initialized (if the fields of callbacks are NOT NULL), false else.
 * @param pll a pointer on the Pll object (Simulates POO programming) 
 * @return true if the pll is initialized (if the fields of callbacks are NOT NULL), false else.
 */
bool isPllInitialized(Pll* Pll);

/**
 * Initializes (Constructor in POO).
 * @param pllParam a pointer on Pll structure to initialize it.
 * @param GetAccelPLLFunction a pointer on the GetAccelPLLFunction
 * @param object A pointer on generic object (for example to store I2cBus ...).
 */
void initPll(Pll* pllParam, 
        InitPLLFunction* InitPLLFunction,
        GetAccelPLLFunction* GetAccelPLLFunction,         
        int* object);

#endif

