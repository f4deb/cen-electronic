#include "../../common/commons.h"

#include "../../common/setup/32/picSetup32.h"

#include <plib.h>
#include <stdlib.h>
#include <math.h>

#include "mainBoard32.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/eeprom/eeprom.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cDebug.h"
#include "../../common/i2c/i2cBusList.h"
#include "../../common/i2c/i2cBusConnectionList.h"

#include "../../common/i2c/master/i2cMaster.h"
#include "../../common/i2c/master/i2cMasterSetup.h"

#include "../../common/i2c/master/i2cMasterOutputStream.h"
#include "../../common/i2c/master/i2cMasterInputStream.h"

#include "../../common/io/buffer.h"
#include "../../common/io/compositeOutputStream.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/streamLink.h"
#include "../../common/io/pin.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

#include "../../common/pwm/pwmPic.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"
#include "../../common/serial/serialLinkList.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

#include "../../common/system/system.h"

#include "../../device/device.h"
#include "../../device/deviceDebug.h"
#include "../../device/deviceUsage.h"
#include "../../device/deviceList.h"
#include "../../device/transmitMode.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"


#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"

#include "../../drivers/driverStreamListener.h"
#include "../../drivers/dispatcher/driverDataDispatcher.h"
#include "../../drivers/dispatcher/driverDataDispatcherDebug.h"
#include "../../drivers/dispatcher/i2cDriverDataDispatcher.h"
#include "../../drivers/dispatcher/localDriverDataDispatcher.h"
#include "../../drivers/dispatcher/uartDriverDataDispatcher.h"

// CLOCK
#include "../../device/clock/clockDevice.h"
#include "../../device/clock/clockDeviceInterface.h"

// DATA DISPATCHER
#include "../../device/dispatcher/dataDispatcherDevice.h"
#include "../../device/dispatcher/dataDispatcherDeviceInterface.h"

// EEPROM
#include "../../device/eeprom/eepromDevice.h"
#include "../../device/eeprom/eepromDeviceInterface.h"

// SERIAL
#include "../../device/serial/serialDebugDevice.h"
#include "../../device/serial/serialDebugDeviceInterface.h"

// TIMER
#include "../../device/timer/timerDevice.h"
#include "../../device/timer/timerDeviceInterface.h"

// SYSTEM
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// LOG
#include "../../device/log/logDevice.h"
#include "../../device/log/logDeviceInterface.h"

// I2C
#include "../../device/i2c/i2cCommonDebugDevice.h"
#include "../../device/i2c/i2cCommonDebugDeviceInterface.h"

// I2C MASTER DEBUG
#include "../../device/i2c/master/i2cMasterDebugDevice.h"
#include "../../device/i2c/master/i2cMasterDebugDeviceInterface.h"

// TEST
#include "../../device/test/testDevice.h"
#include "../../device/test/testDeviceInterface.h"

// TEST
#include "../../device/test/test2Device.h"
#include "../../device/test/test2DeviceInterface.h"

// TIMER
#include "../../device/timer/timerDevice.h"
#include "../../device/timer/timerDeviceInterface.h"

// SENSOR->TEMPERATURE
#include "../../device/sensor/temperature/temperatureSensorDevice.h"
#include "../../device/sensor/temperature/temperatureSensorDeviceInterface.h"

// SERVO
#include "../../device/servo/servoDevice.h"
#include "../../device/servo/servoDeviceInterface.h"

// LCD
#include "../../drivers/lcd/lcd.h"
#include "../../device/lcd/lcdDevice.h"
#include "../../device/lcd/lcdDeviceInterface.h"

// Motor
#include "../../device/motor/pwmMotorDeviceInterface.h"

// Motion
#include "../../device/motion/pid/pidDeviceInterface.h"
#include "../../device/motion/position/codersDeviceInterface.h"
#include "../../device/motion/position/trajectoryDeviceInterface.h"
#include "../../device/motion/simple/motionDeviceInterface.h"

// Sonar
#include "../../device/sonar/sonarDevice.h"
#include "../../device/sonar/sonarDeviceInterface.h"

// Strategy
#include "../../device/strategy/strategyDevice.h"
#include "../../device/strategy/strategyDeviceInterface.h"

#include "../../device/adc/adcDevice.h"
#include "../../device/adc/adcDeviceInterface.h"

// Air conditioning
#include "../../device/airconditioning/airConditioningDeviceInterface.h"

// Beacon Receiver
#include "../../device/beacon/beaconReceiverDeviceInterface.h"

// Drivers
#include "../../drivers/clock/PCF8563.h"
#include "../../drivers/eeprom/24c512.h"
#include "../../drivers/io/pcf8574.h"
#include "../../drivers/clock/PCF8563.h"
#include "../../drivers/test/testDriver.h"
#include "../../drivers/system/systemDriver.h"
#include "../../drivers/motion/motionDriver.h"
#include "../../drivers/motion/trajectoryDriver.h"
#include "../../drivers/motor/md22.h"
#include "../../drivers/driverTransmitter.h"
#include "../../drivers/sensor/temperature/LM75A.h"
#include "../../drivers/strategy/strategyDriver.h"

// Robot
#include "../../robot/config/robotConfig.h"
#include "../../robot/config/robotConfigDevice.h"
#include "../../robot/config/robotConfigDeviceInterface.h"
#include "../../robot/config/32/robotConfigPic32.h"

#include "../../robot/kinematics/robotKinematicsDeviceInterface.h"

#include "../../robot/match/startMatch.h"
#include "../../robot/match/32/startMatchDetector32.h"
#include "../../robot/match/startMatchDevice.h"
#include "../../robot/match/startMatchDeviceInterface.h"
#include "../../robot/match/endMatchDetectorDevice.h"
#include "../../robot/match/endMatchDetectorDeviceInterface.h"

#include "../../robot/opponent/robotInfraredDetectorDeviceInterface.h"
#include "../../robot/opponent/robotInfraredDetectorDriver.h"
#include "../../robot/opponent/robotSonarDetectorDevice.h"
#include "../../robot/opponent/robotSonarDetectorDeviceInterface.h"
#include "../../robot/opponent/opponentRobot.h"

// Other boards interface
#include "../../main/motorBoard/motorBoard32.h"
#include "../../main/meca2/mechanicalBoard2.h"
#include "../../main/airconditioning/airConditioningMain.h"

#include "../../motion/simple/simpleMotion.h"

#include "../../robot/robot.h"

#include "../../drivers/sonar/srf02.h"

// I2C => PORT 1 (for All Peripherical, including Eeprom / Clock / Temperatur)
static I2cBus i2cBusListArray[MAIN_BOARD_I2C_BUS_LIST_LENGTH];
static I2cBusConnection i2cBusConnectionListArray[MAIN_BOARD_I2C_BUS_CONNECTION_LIST_LENGTH];
static I2cBus* i2cBus;

// EEPROM
static Eeprom eeprom;
static I2cBusConnection* eepromI2cBusConnection;

// CLOCK
static Clock clock;
static I2cBusConnection* clockI2cBusConnection;

// TEMPERATURE
static Temperature temperature;
static I2cBusConnection* temperatureI2cBusConnection;

// StartMatch
static StartMatch startMatch;

// SERIAL
static SerialLink serialLinkListArray[MAIN_BOARD_SERIAL_LINK_LIST_LENGTH];

// serial link DEBUG 
static char debugInputBufferArray[MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// serial link Motor
static char motorInputBufferArray[MAIN_BOARD_MOTOR_INPUT_BUFFER_LENGTH];
static Buffer motorInputBuffer;
static char motorOutputBufferArray[MAIN_BOARD_MOTOR_OUTPUT_BUFFER_LENGTH];
static Buffer motorOutputBuffer;
static OutputStream motorOutputStream;
static StreamLink motorSerialStreamLink;

// serial link PC
static char pcInputBufferArray[MAIN_BOARD_PC_INPUT_BUFFER_LENGTH];
static Buffer pcInputBuffer;
static char pcOutputBufferArray[MAIN_BOARD_PC_OUTPUT_BUFFER_LENGTH];
static Buffer pcOutputBuffer;
static OutputStream pcOutputStream;
static StreamLink pcSerialStreamLink;

// serial Link MechanicalBoard
/*
static char mechanicalBoard2InputBufferArray[MAIN_BOARD_MECA2_INPUT_BUFFER_LENGTH];
static Buffer mechanicalBoard2InputBuffer;
static char mechanicalBoard2OutputBufferArray[MAIN_BOARD_MECA2_OUTPUT_BUFFER_LENGTH];
static Buffer mechanicalBoard2OutputBuffer;
static OutputStream mechanicalBoard2OutputStream;
static StreamLink mechanicalBoard2SerialStreamLink;
*/

// DRIVERS
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH];

// DEBUG I2C
static char i2cMasterDebugOutputBufferArray[MAIN_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH];
static Buffer i2cMasterDebugOutputBuffer;
static char i2cMasterDebugInputBufferArray[MAIN_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH];
static Buffer i2cMasterDebugInputBuffer;

// DISPATCHER I2C

static DriverDataDispatcher driverDataDispatcherListArray[MAIN_BOARD_DRIVER_DATA_DISPATCHER_LIST_LENGTH];

// i2c->Motor
static I2cBusConnection* motorI2cBusConnection;
static char motorBoardI2cInputBufferArray[MAIN_BOARD_I2C_INPUT_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH];
static Buffer motorBoardI2cInputBuffer;
static InputStream motorBoardI2cInputStream;
static OutputStream motorBoardI2cOutputStream;

// i2c->Air Conditioning
/*
static I2cBusConnection* airConditioningI2cBusConnection;
static char airConditioningBoardInputBufferArray[MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH];
static Buffer airConditioningBoardInputBuffer;
static InputStream airConditioningBoardInputStream;
static OutputStream airConditioningBoardOutputStream;
*/

// i2c->Mechanical 2
static I2cBusConnection* mechanicalBoard2I2cBusConnection;
static char mechanical2BoardInputBufferArray[MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH];
static Buffer mechanical2BoardInputBuffer;
static InputStream mechanical2BoardInputStream;
static OutputStream mechanical2BoardOutputStream;

// DISPATCHER UART
// uart->Motor
// static char motorBoardUartInputBufferArray[MAIN_BOARD_UART_INPUT_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH];
// static Buffer motorBoardUartInputBuffer;
// static InputStream motorBoardUartInputStream;
// static OutputStream motorBoardUartOutputStream;

// Robot Configuration
static RobotConfig robotConfig;

// lcd DEBUG 
static OutputStream lcdOutputStream;

// Logs
static LogHandler logHandlerListArray[MAIN_BOARD_LOG_HANDLER_LIST_LENGTH];

// Devices
static Device deviceListArray[MAIN_BOARD_DEVICE_LENGTH];

// Timers
static Timer timerListArray[MAIN_BOARD_TIMER_LENGTH];

static long counter;
static int instructionIndex;

/**
 * @private
 */
void initMainBoardDriversDescriptor() {
    // Init the drivers
    initDrivers(&driverRequestBuffer, &driverRequestBufferArray, MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH,
                &driverResponseBuffer, &driverResponseBufferArray, MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH);

    // Get test driver for debug purpose
    addDriver(testDriverGetDescriptor(), TRANSMIT_LOCAL);
}

/**
 * @private.
 */
void addLocalDevices(void) {
    // SYSTEM & DEBUG
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getLogDeviceInterface(), getLogDeviceDescriptor());
    addLocalDevice(getSerialDebugDeviceInterface(), getSerialDebugDeviceDescriptor());
    addLocalDevice(getTimerDeviceInterface(), getTimerDeviceDescriptor());
    addLocalDevice(getTest2DeviceInterface(), getTest2DeviceDescriptor());
    addLocalDevice(getDataDispatcherDeviceInterface(), getDataDispatcherDeviceDescriptor());
    addLocalDevice(getI2cCommonDebugDeviceInterface(), getI2cCommonDebugDeviceDescriptor());
    addLocalDevice(getI2cMasterDebugDeviceInterface(), getI2cMasterDebugDeviceDescriptor());

    // LOCAL
    addLocalDevice(getLCDDeviceInterface(), getLCDDeviceDescriptor());
    addLocalDevice(getRobotConfigDeviceInterface(), getRobotConfigDeviceDescriptor(&robotConfig));

    initStartMatch(&startMatch, isMatchStarted32, mainBoardWaitForInstruction, &eeprom);
    addLocalDevice(getStartMatchDeviceInterface(), getStartMatchDeviceDescriptor(&startMatch, &robotConfig));
    addLocalDevice(getEndMatchDetectorDeviceInterface(), getEndMatchDetectorDeviceDescriptor(&robotConfig));
    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom));
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&clock));
    addLocalDevice(getTemperatureSensorDeviceInterface(), getTemperatureSensorDeviceDescriptor(&temperature));
    addLocalDevice(getADCDeviceInterface(), getADCDeviceDescriptor());
    addLocalDevice(getServoDeviceInterface(), getServoDeviceDescriptor());

    addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());

    /*
    addLocalDevice(getSonarDeviceInterface(), getSonarDeviceDescriptor(i2cBus));
    addLocalDevice(getRobotSonarDetectorDeviceInterface(), getRobotSonarDetectorDeviceDescriptor(i2cBus));
    */
}

/**
 * @private
 */
void addMotorRemoteDevices(void) {

    // Motor Board->I2C
    addI2cRemoteDevice(getTestDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2cRemoteDevice(getMotorDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2cRemoteDevice(getCodersDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2cRemoteDevice(getPIDDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2cRemoteDevice(getTrajectoryDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2cRemoteDevice(getMotionDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);

    /*
    // MOTOR BOARD -> UART
    // addUartRemoteDevice(getTestDeviceInterface(), SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getMotorDeviceInterface(), MAIN_BOARD_SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getCodersDeviceInterface(), MAIN_BOARD_SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getPIDDeviceInterface(), MAIN_BOARD_SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getTrajectoryDeviceInterface(), MAIN_BOARD_SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getMotionDeviceInterface(), MAIN_BOARD_SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getRobotKinematicsDeviceInterface(), MAIN_BOARD_SERIAL_PORT_MOTOR);
    */
}

/**
 * @private. 
 */
void addMeca2RemoteDevices(void) {
    // Mechanical Board 2->I2C
    // Device* armDevice = addI2cRemoteDevice(getArm2012DeviceInterface(), MECHANICAL_BOARD_2_I2C_ADDRESS);
    // Device* infraredDetectorDevice = addI2cRemoteDevice(getRobotInfraredDetectorDeviceInterface(), MECHANICAL_BOARD_2_I2C_ADDRESS);
    // addI2cRemoteDevice(getServoDeviceInterface(), MECHANICAL_BOARD_2_I2C_ADDRESS);
    // addUartRemoteDevice(getRobotInfraredDetectorDeviceInterface(), SERIAL_PORT_MECA2);
}

/**
 * @private.
 */
void addStrategyBoardDevices(void) {
    // Strategy Board->I2C
    // addI2cRemoteDevice(getStrategyDeviceInterface(), STRATEGY_BOARD_I2C_ADDRESS);
}

/**
 * @private.
 */
void addBeaconBoardReceiverBoardDevices(void) {
    // Beacon Receiver Board->I2C
    // addI2cRemoteDevice(getBeaconReceiverDeviceInterface(), BEACON_RECEIVER_I2C_ADDRESS);
}

/**
 * @private.
 */
void initNotifications(void) {
    // Manage the callback notification
    // trajectoryDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    // testDevice.deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    // motionDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    // infraredDetectorDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
}

/**
 * @private
 */
void initMainBoardDevicesDescriptor() {
    initDeviceList(&deviceListArray, MAIN_BOARD_DEVICE_LENGTH);

    addLocalDevices();
    addMotorRemoteDevices();

    // addMeca2RemoteDevices();
    // addStrategyBoardDevices();
    // addBeaconBoardReceiverBoardDevices();

    // Init the devices
    initDevices();

    initNotifications();  
}

void initMainBoardDriverDataDispatcherList(void) {
    // Initializes the DriverDataDispatcherList
    initDriverDataDispatcherList(&driverDataDispatcherListArray, MAIN_BOARD_DRIVER_DATA_DISPATCHER_LIST_LENGTH);

    // Configure data dispatcher
    addLocalDriverDataDispatcher();

    // I2C

    addI2CDriverDataDispatcher("MOTOR_BOARD_I2C_DISPATCHER",
        &motorBoardI2cInputBuffer, 
        (char(*)[]) &motorBoardI2cInputBufferArray,
        MAIN_BOARD_I2C_INPUT_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH,
        &motorBoardI2cOutputStream,
        &motorBoardI2cInputStream,
        motorI2cBusConnection
        );

    // Stream for Mechanical Board 2
    addI2CDriverDataDispatcher(
            "MECHANICAL_BOARD_2_DISPATCHER",
            &mechanical2BoardInputBuffer,
            &mechanical2BoardInputBufferArray,
            MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH,
            &mechanical2BoardOutputStream,
            &mechanical2BoardInputStream,
            mechanicalBoard2I2cBusConnection);

    // SERIAL

    // Uart Stream for motorBoard
    addUartDriverDataDispatcher(
        &motorSerialStreamLink,
        "MOTOR_BOARD_UART_DISPATCHER",
        MAIN_BOARD_SERIAL_PORT_MOTOR);

    // Uart Stream for mechanicalBoard
    /*
    addUartDriverDataDispatcher(
        &mechanicalBoard2SerialStreamLink,
        "MECA2_UART_DISPATCHER",
        SERIAL_PORT_MECA2);
    */
    /*
    // Stream for Air Conditioning
    addI2CDriverDataDispatcher(
            "AIR_CONDITIONING_DISPATCHER",
            &airConditioningBoardInputBuffer,
            &airConditioningBoardInputBufferArray,
            MAIN_BOARD_LINK_TO_AIR_CONDITIONING_BOARD_BUFFER_LENGTH,
            &airConditioningBoardOutputStream,
            &airConditioningBoardInputStream,
            i2cBusConnection);
    */
}

void doInstruction() {
    int currentTime = getCurrentTimeInSecond();

    if (instructionIndex == 0 && currentTime > 1) {
        motionDriverForward(600.0f);
        instructionIndex++;
    }
    else if (instructionIndex == 1 && currentTime > 10) {
        motionDriverLeft(1800.0f);
    }
    else if (instructionIndex == 2 && currentTime > 20) {
        motionDriverForward(600.0f);
    }
}

bool mainBoardWaitForInstruction(StartMatch* startMatchParam) {
    // Listen instruction from pcStream->Devices
    handleStreamInstruction(
            &pcInputBuffer,
            &pcOutputBuffer,
            &pcOutputStream,
            &filterRemoveCRLF,
            NULL);

    // Listen instruction from debugStream->Devices
    handleStreamInstruction(
            &debugInputBuffer,
            &debugOutputBuffer,
            &debugOutputStream,
            &filterRemoveCRLF,
            NULL);

    return true;
}

int main(void) {
    setBoardName("MAIN BOARD");
    setRobotMustStop(false);

    // LOG Global Configuration
    initLogs(LOG_LEVEL_DEBUG, &logHandlerListArray, MAIN_BOARD_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);

    // LCD (LCD via Parallel interface)
    initLCDOutputStream(&lcdOutputStream);
    addLogHandler("LCD", &lcdOutputStream, LOG_LEVEL_ERROR, LOG_HANDLER_CATEGORY_ALL_MASK);

    // CONFIG
    initRobotConfigPic32(&robotConfig);

    // Backlight the LCD is needed
    setBacklight(isConfigSet(&robotConfig, CONFIG_LCD_MASK));

    // SERIAL

    initSerialLinkList(&serialLinkListArray, MAIN_BOARD_SERIAL_LINK_LIST_LENGTH);

    // Open the serial Link for the PC : No Log, only instruction
    openSerialLink(&pcSerialStreamLink,
                   "SERIAL_PC", 
                    &pcInputBuffer, &pcInputBufferArray, MAIN_BOARD_PC_INPUT_BUFFER_LENGTH,
                    &pcOutputBuffer, &pcOutputBufferArray, MAIN_BOARD_PC_OUTPUT_BUFFER_LENGTH,
                    &pcOutputStream,
                    MAIN_BOARD_SERIAL_PORT_PC,
                    DEFAULT_SERIAL_SPEED);

    // Open the serial Link for debug and LOG !
    openSerialLink(&debugSerialStreamLink, 
            "SERIAL_DEBUG",
            &debugInputBuffer, &debugInputBufferArray, MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH,
            &debugOutputBuffer, &debugOutputBufferArray, MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH,
            &debugOutputStream,
            MAIN_BOARD_SERIAL_PORT_DEBUG,
            DEFAULT_SERIAL_SPEED);
    // Serial Debug LOG
    addLogHandler("UART", &debugOutputStream, LOG_LEVEL_DEBUG, LOG_HANDLER_CATEGORY_ALL_MASK);

    // LOG the BoardName
    appendString(getAlwaysOutputStreamLogger(), getBoardName());
    println(getAlwaysOutputStreamLogger());
    
    // Open the serial Link for the Motor Board
    openSerialLink(&motorSerialStreamLink,
                   "SERIAL_MOTOR", 
                   &motorInputBuffer, &motorInputBufferArray, MAIN_BOARD_MOTOR_INPUT_BUFFER_LENGTH,
                   &motorOutputBuffer, &motorOutputBufferArray, MAIN_BOARD_MOTOR_OUTPUT_BUFFER_LENGTH,
                   &motorOutputStream,
                   MAIN_BOARD_SERIAL_PORT_MOTOR,
                   DEFAULT_SERIAL_SPEED);

    // Open the serial Link for the Mechanical Board
    /*
    openSerialLink(&mechanicalBoard2SerialStreamLink,
                   "SERIAL_MECA_2", 
                   &mechanicalBoard2InputBuffer, &mechanicalBoard2InputBufferArray, MAIN_BOARD_MECA2_INPUT_BUFFER_LENGTH,
                   &mechanicalBoard2OutputBuffer, &mechanicalBoard2OutputBufferArray, MAIN_BOARD_MECA2_OUTPUT_BUFFER_LENGTH,
                   &mechanicalBoard2OutputStream,
                   SERIAL_PORT_MECA2,
                   DEFAULT_SERIAL_SPEED);
    */

    // MAIN I2C
    initI2cBusList((I2cBus(*)[]) &i2cBusListArray, MAIN_BOARD_I2C_BUS_LIST_LENGTH);
	initI2cBusConnectionList((I2cBusConnection(*)[]) &i2cBusConnectionListArray, MAIN_BOARD_I2C_BUS_CONNECTION_LIST_LENGTH);

    i2cBus = addI2cBus(I2C_BUS_TYPE_MASTER, I2C_BUS_PORT_1);
    i2cMasterInitialize(i2cBus);
    motorI2cBusConnection = addI2cBusConnection(i2cBus, MOTOR_BOARD_I2C_ADDRESS, true);
    mechanicalBoard2I2cBusConnection = addI2cBusConnection(i2cBus, MECHANICAL_BOARD_2_I2C_ADDRESS, true);

    // I2C Debug
    initI2CDebugBuffers(&i2cMasterDebugInputBuffer,
                        &i2cMasterDebugInputBufferArray,
                        MAIN_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH,
                        &i2cMasterDebugOutputBuffer,
                        &i2cMasterDebugOutputBufferArray,
                        MAIN_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH);
    setDebugI2cEnabled(false);

    // -> Eeproms
    eepromI2cBusConnection = addI2cBusConnection(i2cBus, ST24C512_ADDRESS_0, true);
    init24C512Eeprom(&eeprom, eepromI2cBusConnection);
    // -> Clock
    clockI2cBusConnection = addI2cBusConnection(i2cBus, PCF8563_WRITE_ADDRESS, true);
    initClockPCF8563(&clock, clockI2cBusConnection);
    // -> Temperature
    temperatureI2cBusConnection = addI2cBusConnection(i2cBus, LM75A_ADDRESS, true);
    initTemperatureLM75A(&temperature, temperatureI2cBusConnection);

    // TIMERS
    initTimerList(&timerListArray, MAIN_BOARD_TIMER_LENGTH);

    // DEVICES, DRIVERS, DISPATCHERS
    initMainBoardDevicesDescriptor();
    initMainBoardDriversDescriptor();
    initMainBoardDriverDataDispatcherList();


    // Start interruptions
    startTimerList();

    loopUntilStart(&startMatch);

    counter = 1;

    // clearBuffer(&mechanicalBoard1InputBuffer);

    // enableNotificationRobotInfraredDetector(DETECTOR_GROUP_TYPE_FORWARD);


    while (1) {
        if (!mainBoardWaitForInstruction(&startMatch)) {
            break;
        }
    }

    showEnd(getAlwaysOutputStreamLogger());

    while (1) {
        // Avoid reboot even at end
    }
}
