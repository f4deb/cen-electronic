#include <peripheral/i2c.h>
#include <stdlib.h>

// List of available functionality

#include "mechanicalMotorBoard32.h"

#include "../../common/commons.h"
#include "../../common/2d/2d.h"
#include "../../common/math/cenMath.h"

#include "../../common/eeprom/eeprom.h"

#include "../../common/setup/32/picSetup32.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cDebug.h"

#include "../../common/i2c/master/i2cMaster.h"
#include "../../common/i2c/master/i2cMasterSetup.h"

#include "../../common/i2c/master/i2cMasterOutputStream.h"
#include "../../common/i2c/master/i2cMasterInputStream.h"


#include "../../common/i2c/slave/i2cSlave.h"
#include "../../common/i2c/slave/i2cSlaveSetup.h"
#include "../../common/i2c/slave/i2cSlaveLink.h"

#include "../../common/io/filter.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/printWriter.h"

#include "../../common/pwm/pwmPic.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/timerList.h"

#include "../../common/system/system.h"

#include "../../device/device.h"
#include "../../device/deviceList.h"
#include "../../device/transmitMode.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"

#include "../../drivers/driverStreamListener.h"

// -> Devices

//ADC
#include "../../device/adc/adcDevice.h"
#include "../../device/adc/adcDeviceInterface.h"

//CLOCK
#include "../../device/clock/clockDevice.h"
#include "../../device/clock/clockDeviceInterface.h"

// EEPROM
#include "../../device/eeprom/eepromDevice.h"
#include "../../device/eeprom/eepromDeviceInterface.h"

// FILE
#include "../../device/file/fileDevice.h"
#include "../../device/file/fileDeviceInterface.h"

// Test
#include "../../device/test/testDevice.h"
#include "../../device/test/testDeviceInterface.h"

// Serial
#include "../../device/serial/serialDebugDevice.h"
#include "../../device/serial/serialDebugDeviceInterface.h"

// System
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// Timer
#include "../../device/timer/timerDevice.h"
#include "../../device/timer/timerDeviceInterface.h"

// Log
//#include "../../device/log/logDevice.h"
//#include "../../device/log/logDeviceInterface.h"

// I2C Slave Device/
#include "../../device/i2c/slave/i2cSlaveDebugDevice.h"
#include "../../device/i2c/slave/i2cSlaveDebugDeviceInterface.h"

// Motors
#include "../../device/motor/pwmMotorDevice.h"
#include "../../device/motor/pwmMotorDeviceInterface.h"

// PID
#include "../../motion/pid/pid.h"
#include "../../motion/pid/pidDebug.h"
#include "../../motion/pid/profile/pidMotionProfileComputer.h"
#include "../../device/motion/pid/pidDevice.h"
#include "../../device/motion/pid/pidDeviceInterface.h"

// Coders
#include "../../device/motion/position/codersDevice.h"
#include "../../device/motion/position/codersDeviceInterface.h"

// Trajectory
#include "../../device/motion/position/trajectoryDevice.h"
#include "../../device/motion/position/trajectoryDeviceInterface.h"

// Motion
#include "../../device/motion/simple/motionDevice.h"
#include "../../device/motion/simple/motionDeviceInterface.h"

// Robot
#include "../../robot/kinematics/robotKinematicsDevice.h"
#include "../../robot/kinematics/robotKinematicsDeviceInterface.h"

// Drivers
#include "../../drivers/clock/PCF8563.h"
//#include "../../drivers/clock/softClock.h"
#include "../../drivers/eeprom/24c512.h"

#include "../../drivers/motor/motorDriver.h"

// Direct implementation
#include "../../motion/motion.h"
#include "../../motion/simple/simpleMotion.h"
#include "../../motion/position/trajectory.h"
#include "../../motion/position/coders.h"

// #include "../../test/mathTest.h"
#include "../../test/motion/bspline/bsplinetest.h"

// The port used to send instruction if we connect MainBoard and MotorBoard via RS232
#define SERIAL_PORT_STANDARD  SERIAL_PORT_5

// The port for which we debug (we can send instruction too)
#define SERIAL_PORT_DEBUG     SERIAL_PORT_2

// I2C => PORT 1 (for All Peripherical, including Eeprom / Clock / Temperatur)
static I2cBus i2cBus;

// I2C Bus
static I2cBus mainBoardI2cBus;
static I2cBusConnection mainBoardI2cBusConnection;

// Eeprom
static Eeprom eeprom;
//static I2cBus eepromI2cBus;
static I2cBusConnection eepromI2cBusConnection;

// Clock
static Clock clock;
static I2cBusConnection clockI2cBusConnection;

// serial INSTRUCTION
static char standardInputBufferArray[MOTOR_BOARD_IN_BUFFER_LENGTH];
static Buffer standardInputBuffer;
static char standardOutputBufferArray[MOTOR_BOARD_OUT_BUFFER_LENGTH];
static Buffer standardOutputBuffer;
static OutputStream standardOutputStream;
static StreamLink standardSerialStreamLink;

// serial DEBUG 
static char debugInputBufferArray[MOTOR_BOARD_IN_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[MOTOR_BOARD_OUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// logs
static LogHandler logHandlerListArray[MOTOR_BOARD_LOG_HANDLER_LIST_LENGTH];

// i2c Link
static char i2cSlaveInputBufferArray[MOTOR_BOARD_IN_BUFFER_LENGTH];
static Buffer i2cSlaveInputBuffer;
static char i2cSlaveOutputBufferArray[MOTOR_BOARD_OUT_BUFFER_LENGTH];
static Buffer i2cSlaveOutputBuffer;
static StreamLink i2cSlaveStreamLink;

// I2C Debug
static char i2cMasterDebugOutputBufferArray[MOTOR_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH];
static Buffer i2cMasterDebugOutputBuffer;
static char i2cMasterDebugInputBufferArray[MOTOR_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH];
static Buffer i2cMasterDebugInputBuffer;

// Timers
static Timer timerListArray[MOTOR_BOARD_TIMER_LENGTH];
int currentTimeInSecond;
bool currentTimeChanged;

#define MOTOR_BOARD_PIC_NAME "MOTOR BOARD 32"

Buffer* getI2CSlaveOutputBuffer() {
    return &i2cSlaveOutputBuffer;
}

// I2C Debug
/*
static Buffer debugI2cInputBuffer;
static Buffer debugI2cOutputBuffer;
 */

// Devices
static Device deviceListArray[MOTOR_BOARD_DEVICE_LIST_LENGTH];

void initDevicesDescriptor() {
    initDeviceList(&deviceListArray, MOTOR_BOARD_DEVICE_LIST_LENGTH);
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getMotorDeviceInterface(), getMotorDeviceDescriptor());
    addLocalDevice(getCodersDeviceInterface(), getCodersDeviceDescriptor());
    //addLocalDevice(getPIDDeviceInterface(), getPIDDeviceDescriptor(&eeprom, false));
    //addLocalDevice(getMotionDeviceInterface(), getMotionDeviceDescriptor(&eeprom, false));
    addLocalDevice(getTrajectoryDeviceInterface(), getTrajectoryDeviceDescriptor());
    addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());
    addLocalDevice(getSerialDebugDeviceInterface(), getSerialDebugDeviceDescriptor());

    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&clock));
    addLocalDevice(getTimerDeviceInterface(), getTimerDeviceDescriptor());
    addLocalDevice(getADCDeviceInterface(), getADCDeviceDescriptor());

    // I2C_4
    addLocalDevice(getRobotKinematicsDeviceInterface(), getRobotKinematicsDeviceDescriptor(&eeprom));
    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom));

//    addLocalDevice(getLogDeviceInterface(), getLogDeviceDescriptor());
   //addLocalDevice(getI2cSlaveDebugDeviceInterface(), getI2cSlaveDebugDeviceDescriptor(&mainBoardI2cBusConnection));


    initDevices();
}

void waitForInstruction() {
    // I2C Stream
    //handleStreamInstruction(&i2cSlaveInputBuffer, &i2cSlaveOutputBuffer, NULL, &filterRemoveCRLF, NULL);

    // STANDARD UART Stream
    //handleStreamInstruction(&standardInputBuffer, &standardOutputBuffer, &standardOutputStream, &filterRemoveCRLF, NULL);

    // DEBUG UART Stream
    handleStreamInstruction(&debugInputBuffer, &debugOutputBuffer, &debugOutputStream, &filterRemoveCRLF, NULL);

    // Manage Motion
    handleInstructionAndMotion();
}



int runMotorBoard() {
    
    //Disable JTAG to free the PORTB
    DDPCONbits.JTAGEN=0;
    
    // configure for multi-vectored mode
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    // enable interrupts
    INTEnableInterrupts();

    setBoardName(MOTOR_BOARD_PIC_NAME);

    delaymSec(100);

    openSerialLink(&standardSerialStreamLink,
            &standardInputBuffer,
            &standardInputBufferArray,
            MOTOR_BOARD_IN_BUFFER_LENGTH,
            &standardOutputBuffer,
            &standardOutputBufferArray,
            MOTOR_BOARD_OUT_BUFFER_LENGTH,
            &standardOutputStream,
            SERIAL_PORT_STANDARD,
            DEFAULT_SERIAL_SPEED);

    openSerialLink(&debugSerialStreamLink,
            &debugInputBuffer,
            &debugInputBufferArray,
            MOTOR_BOARD_IN_BUFFER_LENGTH,
            &debugOutputBuffer,
            &debugOutputBufferArray,
            MOTOR_BOARD_OUT_BUFFER_LENGTH,
            &debugOutputStream,
            SERIAL_PORT_DEBUG,
            DEFAULT_SERIAL_SPEED);

    // Init the logs
    initLogs(DEBUG, (LogHandler(*)[]) &logHandlerListArray, MOTOR_BOARD_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);
    addLogHandler("UART", &debugOutputStream, DEBUG, LOG_HANDLER_CATEGORY_ALL_MASK);
    appendString(getDebugOutputStreamLogger(), getBoardName());
    appendCRLF(getDebugOutputStreamLogger());

    initTimerList(&timerListArray, MOTOR_BOARD_TIMER_LENGTH);

    initI2cBus(&mainBoardI2cBus, I2C_BUS_TYPE_SLAVE, I2C_BUS_PORT_4);
    initI2cBusConnection(&mainBoardI2cBusConnection, &mainBoardI2cBus, MOTOR_BOARD_I2C_ADDRESS);
    openSlaveI2cStreamLink(&i2cSlaveStreamLink,
            &i2cSlaveInputBuffer,
            &i2cSlaveInputBufferArray,
            MOTOR_BOARD_IN_BUFFER_LENGTH,
            &i2cSlaveOutputBuffer,
            &i2cSlaveOutputBufferArray,
            MOTOR_BOARD_OUT_BUFFER_LENGTH,
            // NULL, 
            &mainBoardI2cBusConnection
            );

    // Debug of I2C : Only if there is problems
    initI2CDebugBuffers(&i2cMasterDebugInputBuffer,
        (char(*)[]) &i2cMasterDebugInputBufferArray,
        MOTOR_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH,
        &i2cMasterDebugOutputBuffer,
        (char(*)[]) &i2cMasterDebugOutputBufferArray,
        MOTOR_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH);

    setDebugI2cEnabled(false);

    // Eeprom
    initI2cBus(&i2cBus, I2C_BUS_TYPE_MASTER, I2C_BUS_PORT_4);
    i2cMasterInitialize(&i2cBus);
    initI2cBusConnection(&eepromI2cBusConnection, &i2cBus, ST24C512_ADDRESS_0);
    init24C512Eeprom(&eeprom, &eepromI2cBusConnection);
    // -> Clock
    initI2cBusConnection(&clockI2cBusConnection, &i2cBus, PCF8563_WRITE_ADDRESS);
    initClockPCF8563(&clock, &clockI2cBusConnection);

    // init the devices
    initDevicesDescriptor();

    // Init the timers management
    startTimerList();

    while (1) {
        waitForInstruction();
    }
}

int main(void) {

    runMotorBoard();

    return (0);
}