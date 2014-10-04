#include "../../common/commons.h"

#ifdef PROG_32
    #include <plib.h>
    #include "../../common/setup/32/picSetup32.h"
#else
    #include <i2c.h>
    #include "../../common/setup/30F/picSetup30F.h"
#endif

#include "MainJK330.h"

//include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cDebug.h"

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
#include "../../common/io/stream.h"
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

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

#include "../../device/device.h"
#include "../../device/deviceDebug.h"
#include "../../device/deviceUsage.h"
#include "../../device/deviceList.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"


#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"

#include "../../drivers/driverStreamListener.h"
#include "../../drivers/dispatcher/driverDataDispatcher.h"
#include "../../drivers/dispatcher/driverDataDispatcherDebug.h"
#include "../../drivers/dispatcher/i2cDriverDataDispatcher.h"
#include "../../drivers/dispatcher/localDriverDataDispatcher.h"

// SYSTEM
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// SYSTEM DEBUG
#include "../../device/system/systemDebugDevice.h"
#include "../../device/system/systemDebugDeviceInterface.h"

// I2C MASTER DEBUG
#include "../../device/i2c/master/i2cMasterDebugDevice.h"
#include "../../device/i2c/master/i2cMasterDebugDeviceInterface.h"

//CLOCK
#include "../../device/clock/clockDevice.h"
#include "../../device/clock/clockDeviceInterface.h"

#include "../../drivers/clock/PCF8563.h"

//KEYBOARD
#include "../../drivers/keyboard/74c922.h"

//SENSOR
#include "../../drivers/sensor/MCP9804.h"

// LCD
#include "../../drivers/lcd/lcd.h"
//#include "../../drivers/lcd/lcd4d.h"
#include "../../drivers/lcd/lcd24064.h"
#include "../../drivers/lcd/lcdProvider_24064.h"

#include "../../device/lcd/lcdDevice.h"
#include "../../device/lcd/lcdDeviceInterface.h"

//#include "../device/led/led.h"

//#include "../drivers/io/MCP9804.h"

//#include "../drivers/io/EEPROM_I2C.h"
//#include "../drivers/io/PCF8563.h"
//#include "../drivers/io/time.h"

//#include "../drivers/lcd/lcd24064.h"
//#include "../drivers/lcd/lcdOutputStream.h"
//#include "../drivers/lcd/lcdProvider_24064.h"



#include "../../menu/menu.h"

//#include "../setup/clockConstants.h"
//#include "drivers/IO/PCF8563.h"




//#ifndef MPLAB_SIMULATION
//    #ifdef PROG_32
        #define SERIAL_PORT_DEBUG         SERIAL_PORT_3
        #define SERIAL_PORT_PC             SERIAL_PORT_2
        #define SERIAL_PORT_LCD            SERIAL_PORT_5
//    #else
//        #define SERIAL_PORT_DEBUG         SERIAL_PORT_1
//        #define SERIAL_PORT_PC             SERIAL_PORT_2
//    #endif
//#else
    // We use the same port for both
 //   #define SERIAL_PORT_PC             SERIAL_PORT_1
 //   #define SERIAL_PORT_DEBUG         SERIAL_PORT_1
//#endif

// serial link DEBUG
static char debugInputBufferArray[MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// serial link PC
static char pcInputBufferArray[MAIN_BOARD_PC_INPUT_BUFFER_LENGTH];
static Buffer pcInputBuffer;
static char pcOutputBufferArray[MAIN_BOARD_PC_OUTPUT_BUFFER_LENGTH];
static Buffer pcOutputBuffer;
static OutputStream pcOutputStream;
static StreamLink pcSerialStreamLink;

// DRIVERS
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH];

//DRIVERS CLOCK
static Buffer driverClockBuffer;
static char driverClockBufferArray[CLOCK_BUFFER_LENGTH];


// DEBUG I2C
static char i2cMasterDebugOutputBufferArray[MAIN_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH];
static Buffer i2cMasterDebugOutputBuffer;
static char i2cMasterDebugInputBufferArray[MAIN_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH];
static Buffer i2cMasterDebugInputBuffer;



// DISPATCHER I2C

// i2c->Motor
static DriverDataDispatcher motorI2cDispatcher;
static char motorBoardInputBufferArray[MAIN_BOARD_LINK_TO_MOTOR_BOARD_BUFFER_LENGTH];
static Buffer motorBoardInputBuffer;
static InputStream motorBoardInputStream;
static OutputStream motorBoardOutputStream;

// i2c->Air Conditioning
static DriverDataDispatcher airConditioningI2cDispatcher;
static char airConditioningBoardInputBufferArray[MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH];
static Buffer airConditioningBoardInputBuffer;
static InputStream airConditioningBoardInputStream;
static OutputStream airConditioningBoardOutputStream;

// i2c->Mechanical 2
static DriverDataDispatcher mechanical2I2cDispatcher;
static char mechanical2BoardInputBufferArray[MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH];
static Buffer mechanical2BoardInputBuffer;
static InputStream mechanical2BoardInputStream;
static OutputStream mechanical2BoardOutputStream;

// lcd DEBUG
static OutputStream lcdOutputStream;

// logs
static LogHandler debugSerialLogHandler;
static LogHandler lcdLogHandler;


// Devices
static Device deviceListArray[MAIN_BOARD_DEVICE_LENGTH];

// Timers
static Timer timerListArray[MAIN_BOARD_TIMER_LENGTH];


// *****************************************************************************
// *****************************************************************************
// Section: Constant Data
// *****************************************************************************
// *****************************************************************************

static const char* HELLO_UART_PC = "JK330 with PIC32...on UART PC\r\n";
static const char* HELLO_UART_DEBUG = "JK330 with PIC32...on UART DEBUG\r\n";
static const char* HELLO_UART_TEST = "JK330 with PIC32...on UART TEZST\r\n";

// Variable Capteur de temperature MCP9804
int BCD1, BCD2, BCD3, BCD4;
int BCD10;

//#define ACK 1
//#define NACK 0

int Temperature;

/********************************************************************************************************************************
 *********************************************************************************************************************************
 *************************************************************** EN TEST *********************************************************
 *********************************************************************************************************************************
 ********************************************************************************************************************************/


/********************************************************************************************************************************
 *********************************************************************************************************************************
 ************************************************ INITIALISATION CONFIGURATION ET MAIN *******************************************
 *********************************************************************************************************************************
 ********************************************************************************************************************************/

/*******************************************************************************
 *  init									       *
 * initialise les differents peripheriquesdu projet                             *
 * @prarm : none                                                                *
 * @return : none                                                               *
 *******************************************************************************/

void Init(void) {

    //Initialise l'afficheur LCD et affiche l'image d'accueil

/*    outputStream = &lcdoutputStream;
    initLcdOutputStream(outputStream);
    outputStream->openOutputStream(outputStream, 0); //InitLCD();

        //Initialise port serie debug
    outputStream = &debugoutputStream;
    //initSerialOutputStream1(outputStream);
    initSerialOutputStream(outputStream, SERIAL_PORT_DEBUG);
    outputStream->openOutputStream(outputStream, 0);

        //Initialise port serie PC
    outputStream = &pcoutputStream;
    //initSerialOutputStream2(outputStream);
    initSerialOutputStream(outputStream, SERIAL_PORT_PC);
    outputStream->openOutputStream(outputStream, 0);



   // fais clignoter les leds de la facade
    InitLed07();




    // Initialise le capteur de temperature MCP9804
    initRegMCP9804 (0x00,0x18,0x01,0xE0,0x01,0x40,0x02,0x40); // 30C,20C,34C
 */
}



/**
 * @private
 */
void initDriversDescriptor() {
    // Init the drivers
    initDrivers(&driverRequestBuffer, &driverRequestBufferArray, MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH,
                &driverResponseBuffer, &driverResponseBufferArray, MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH);



    // Get test driver for debug purpose
//    addDriver(driverTestGetDescriptor(), TRANSMIT_LOCAL);

    // Direct Devantech Driver
//    addDriver(getMD22DriverDescriptor(), TRANSMIT_NONE);
}

/**
 * @private
 */
void initDevicesDescriptor() {
    initDeviceList(&deviceListArray, MAIN_BOARD_DEVICE_LENGTH);

    // Test & System
    // addI2CRemoteDevice(&testDevice, getTestDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getSystemDebugDeviceInterface(), getSystemDebugDeviceDescriptor());
    addLocalDevice(getI2cMasterDebugDeviceInterface(), getI2cMasterDebugDeviceDescriptor());

    // Local
    addLocalDevice(getLCDDeviceInterface(), getLCDDeviceDescriptor());
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor());
    // addLocalDevice(&servoDevice, getServoDeviceInterface(), getServoDeviceDescriptor());
/*    addLocalDevice(getRobotConfigDeviceInterface(), getRobotConfigDeviceDescriptor());
    addLocalDevice(getStartMatchDetectorDeviceInterface(), getStartMatchDetectorDeviceDescriptor());
    addLocalDevice(getEndMatchDetectorDeviceInterface(), getEndMatchDetectorDeviceDescriptor());
    addLocalDevice(getSonarDeviceInterface(), getSonarDeviceDescriptor());
    addLocalDevice(getRobotSonarDetectorDeviceInterface(), getRobotSonarDetectorDeviceDescriptor());
*/
    // Mechanical Board 2->I2C
    // Device* armDevice = addI2CRemoteDevice(getArm2012DeviceInterface(), MECHANICAL_BOARD_2_I2C_ADDRESS);
    // Device* infraredDetectorDevice = addI2CRemoteDevice(getRobotInfraredDetectorDeviceInterface(), MECHANICAL_BOARD_2_I2C_ADDRESS);

    // Motor Board->I2C
/*    addI2CRemoteDevice(getPIDDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2CRemoteDevice(getMotorDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2CRemoteDevice(getCodersDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    Device* trajectoryDevice = addI2CRemoteDevice(getTrajectoryDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    Device* motionDevice = addI2CRemoteDevice(getMotionDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
*/
    // Beacon Receiver Board->I2C
    // addI2CRemoteDevice(getBeaconReceiverDeviceInterface(), BEACON_RECEIVER_I2C_ADDRESS);

    // Strategy Board->I2C
    // addI2CRemoteDevice(getStrategyDeviceInterface(), STRATEGY_BOARD_I2C_ADDRESS);

    // Air Conditioning Board
/*   addI2CRemoteDevice(getAirConditioningDeviceInterface(), AIR_CONDITIONING_BOARD_I2C_ADDRESS);
*/
    // Init the devices
    initDevices();  

    // Manage the callback notification
/*    trajectoryDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    // testDevice.deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    motionDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    // infraredDetectorDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
 */
}




void waitForInstruction(void) {
    /*
    // Listen instruction from pcStream->Devices
    handleStreamInstruction(
            &pcInputBuffer,
            &pcOutputBuffer,
            &pcOutputStream,
            &filterRemoveCRLF,
            NULL);
    */
    // Listen instruction from debugStream->Devices
    handleStreamInstruction(
            &debugInputBuffer,
            &debugOutputBuffer,
            &debugOutputStream,
            &filterRemoveCRLF,
            NULL);

    // Listen instructions from Devices (I2C Slave) -> Main Board (I2C Master)
    /*
    while (handleNotificationFromDispatcherList(TRANSMIT_I2C)) {
        // loop for all notification
        // notification handler must avoid to directly information in notification callback
        // and never to the call back device
    }
    */

    /*
    // Notify to the strategy board the position of the robot
    if (isRobotPositionChanged()) {
        sentStrategyRobotPosition(0, getRobotPositionX(), getRobotPositionY(), getRobotAngle());
        resetRobotPositionChanged();
    }

    if (mustNotifyObstacle) {
        mustNotifyObstacle = false;
        // Obtain robot position
        // Ask the robot position from the MOTOR BOARD
        trajectoryDriverUpdateRobotPosition();

        // compute the obstacle position. If it's outside the table, does nothing
        int obstacleDistance = 350.0f;
        appendStringAndDec(getOutputStreamLogger(INFO), "\nInstruction Type:", instructionType);

        if (instructionType == INSTRUCTION_TYPE_BACKWARD) {
            obstacleDistance = -obstacleDistance;
        }
        if (isObstacleOutsideTheTable(obstacleDistance)) {
            appendString(getOutputStreamLogger(INFO), "\nObstacle OUT side the Table!\n");
        }
        else {
            appendString(getOutputStreamLogger(INFO), "\nObstacle !\n");
            // Send information to Strategy Board
            stopRobotObstacle();
            armDriver2012Up(ARM_LEFT);
            armDriver2012Up(ARM_RIGHT);
            // we are ready for next motion (next loop)
            setReadyForNextMotion(true);
        }
    }

    // Update the current Opponent Robot position
    if (useBalise) {
        updateOpponentRobotIfNecessary();
    }
    */
}

int main(void) {
  
    i2cMasterInitialize();
    
    setPicName("MAIN BOARD JK330");

    // Open the serial Link for debug
    openSerialLink(&debugSerialStreamLink,
            &debugInputBuffer,
            &debugInputBufferArray,
            MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH,
            &debugOutputBuffer,
            &debugOutputBufferArray,
            MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH,
            &debugOutputStream,
            SERIAL_PORT_DEBUG,
            DEFAULT_SERIAL_SPEED);

    // Open the serial Link for the PC
    openSerialLink(&pcSerialStreamLink,
            &pcInputBuffer,
            &pcInputBufferArray,
            MAIN_BOARD_PC_INPUT_BUFFER_LENGTH,
            &pcOutputBuffer,
            &pcOutputBufferArray,
            MAIN_BOARD_PC_OUTPUT_BUFFER_LENGTH,
            &pcOutputStream,
            SERIAL_PORT_PC,
            DEFAULT_SERIAL_SPEED);



   appendString(&pcOutputStream, "JK330 with PIC32...on UART PC\r");
   appendString(&debugOutputStream, "JK330 with PIC32...on UART DEBUG\r");



    //Configure les PIN de control de l'afficheur MGSLS24064
    SetupLCD_24064();
    initRegMCP9804 (0x00,0x18,0x01,0xE0,0x01,0x40,0x02,0x40); // 30C,20C,34C

    //creer le flux lcd
   //Initialise l'afficheur LCD et affiche l'image d'accueil

    initLCDOutputStream(&lcdOutputStream);

    initTimerList(&timerListArray, MAIN_BOARD_TIMER_LENGTH);

    // Init the logs
    initLog(DEBUG);
    addLogHandler(&debugSerialLogHandler, "UART", &debugOutputStream, DEBUG);
    addLogHandler(&lcdLogHandler, "LCD", &lcdOutputStream, ERROR);

    initBuffer(&driverClockBuffer, &driverClockBufferArray, CLOCK_BUFFER_LENGTH, "CLOCK_BUFFER", "");

    init74c922();

    appendString(getOutputStreamLogger(DEBUG), getPicName());
    println(getOutputStreamLogger(DEBUG));
   

    clearScreen();
    drawPicture();

    initDevicesDescriptor();
    initDriversDescriptor();

    //Affiche la liste des loggger sur DEBUG
    printLogger(getOutputStreamLogger(DEBUG));

    hor.ti_hour=0x18;
    hor.ti_min=0x54;
    hor.ti_sec=0x00;
    hor.ti_day=0x28;
    hor.ti_month=0x09;
    hor.ti_year=0x14;

   //setTime_8563(&driverClockBuffer);

   appendString(getOutputStreamLogger(DEBUG), "Lecture Horloge : \r");
  //CLOCK Read
  getTime_8563(&driverClockBuffer);
  // l'affiche sur le flux de sortie
  printTime(getOutputStreamLogger(DEBUG));
   appendCR(getOutputStreamLogger(DEBUG));


   clearScreen();
   setCursorAtHome();
   menu_P(&lcdOutputStream);
   while (1){
        setCursorPosition_24064(0,23);  //raw,col

        //CLOCK Read
        getTime_8563(&driverClockBuffer);
        // l'affiche sur le flux de sortie
        printTime(&lcdOutputStream);
        waitForInstruction();



        unsigned int c = readKey();
        appendHex2(&lcdOutputStream, c);

        setCursorPosition_24064(0,19);

        appendDec(&lcdOutputStream, ReadTempAmbMCP9804());

        

   }


 /*  appendString(&debugoutputStream, "Lecture Horloge \r");
   getTime(outputStream);
   appendCR(outputStream);
   
    clearScreen();
    setCursorAtHome();

    setCursorPosition_24064(7,39);  //raw,col
    outputStream = &lcdoutputStream;
    menu_P(&lcdoutputStream);


    outputStream = &debugoutputStream;


    //Effectue un test sur l'eeprom ecriture/lecture

    //ecriture
    
    //eepromI2CWrite (0x00,0x00);

    
 //   eepromI2CWrite (0x00,0x15);

    appendHex2( outputStream, eepromI2CRead (0x00));

    appendHex2( outputStream, eepromI2CRead (0x01));
    appendHex2( outputStream, eepromI2CRead (0x02));
    appendHex2( outputStream, eepromI2CRead (0x03));
    appendHex2( outputStream, eepromI2CRead (0x04));
    appendHex2( outputStream, eepromI2CRead (0x05));
    appendHex2( outputStream, eepromI2CRead (0x06));
    appendHex2( outputStream, eepromI2CRead (0x07));
    appendHex2( outputStream, eepromI2CRead (0x08));
    appendHex2( outputStream, eepromI2CRead (0x09));
    appendHex2( outputStream, eepromI2CRead (0x0A));
    appendHex2( outputStream, eepromI2CRead (0x0B));
    appendHex2( outputStream, eepromI2CRead (0x0C));
    appendHex2( outputStream, eepromI2CRead (0x0D));
    appendHex2( outputStream, eepromI2CRead (0x0E));
    appendHex2( outputStream, eepromI2CRead (0x0F));
    appendCR(outputStream);
    appendHex2( outputStream, eepromI2CRead (0x10));
    appendCR(outputStream);
    appendCR(outputStream);



    //lecture


    hor.ti_hour=0x17;
    hor.ti_min=0x23;
    hor.ti_sec=0x30;
    hor.ti_day=0x012;
    hor.ti_month=0x08;
    hor.ti_year=0x14;
    //setTime();
    while (1) {
    outputStream = &lcdoutputStream;
    setCursorPosition_24064(0,23);
    getTime(outputStream);

    
    setCursorPosition_24064(0,19);

    appendDec(outputStream, ReadTempAmbMCP9804());
    append(outputStream,'C');



    delaymSec(1000);
    }
 */
}




























////////////////////////////// MEMO.


/*
   outputStream = &debugoutputStream;


   appendString (outputStream,"TOTO\0");
   append(outputStream,'J');

 */

/*    while (1) {

        Temperature = ReadTempAmbMCP9804();
        BCD10 = (Temperature / 10) ;
        Temperature = (Temperature - (BCD10*10));
        BCD1 = Temperature + '0' ;
        BCD10 += '0';
        WriteCharUart(SERIAL_PORT_DEBUG, BCD10);
        WriteCharUart(SERIAL_PORT_DEBUG, BCD1 );
        WriteCharUart(SERIAL_PORT_DEBUG, CR );
        delaymSec(500);
    }
 */




//	outputStream->address=1;
//	initOutputStream(OutputStream *outputStream);
//	initOutputStream(&pcoutputStream);



/*
int main(void){
        Setup();
        Init();

         static	OutputStream pcoutputStream ;
	
        OutputStream *outputStream = &pcoutputStream;

        outputStream->x=0;

//	appendString(getOutputStreamLogger(ALWAYS), "Homologation:");
        SendDataBuffer (SERIAL_PORT_PC,HELLO_UART_PC);
        SendDataBuffer (SERIAL_PORT_DEBUG,HELLO_UART_DEBUG);
        }
 */

////////////////////////////// MEMO 
/*
int main(void){

        Setup();
        Init();


        OutputStream outputStream ;
	
        OutputStream *pointeur = &outputStream;


        pointeur->x=0;
        outputStream.x=1;
        outputStream.y=1;





//	appendString(getOutputStreamLogger(ALWAYS), "Homologation:");

        SendDataBuffer (SERIAL_PORT_PC,HELLO_UART_PC);
        SendDataBuffer (SERIAL_PORT_DEBUG,HELLO_UART_DEBUG);
	
        }
 */

////////////////////////////// MEMO 

/*
void Init(void) {
//	OpenUart(SERIAL_PORT_PC,BAUDERATE);
//	OpenUart(SERIAL_PORT_DEBUG,BAUDERATE);

        void (*toto)();
        toto = OpenUartDefaut;

        toto();
//	OpenUartDefaut();
//initLCD();
}
 */

/*
    OpenI2C();
    WriteCharI2C(0x30);
    WriteCharI2C(0x01);
    OpenI2C();
    WriteCharI2C(0x31);
    TempAmbMSB = ReadCharI2C(ACK);

    TempAmbLSB = MasterReadI2C1();NotAckI2C1();IdleI2C1();
    CloseI2C();

    OpenI2C();
    WriteCharI2C(0x30);
    WriteCharI2C(0x02);
    OpenI2C();
    WriteCharI2C(0x31);//AckI2C1();
    TempAmbMSB = MasterReadI2C1();AckI2C1();IdleI2C1();//AckI2C1();
    TempAmbLSB = MasterReadI2C1();NotAckI2C1();IdleI2C1();
    CloseI2C();

    OpenI2C();
    WriteCharI2C(0x30);
    WriteCharI2C(0x03);
    OpenI2C();
    WriteCharI2C(0x31);//AckI2C1();
    TempAmbMSB = MasterReadI2C1();AckI2C1();IdleI2C1();//AckI2C1();
    TempAmbLSB = MasterReadI2C1();NotAckI2C1();IdleI2C1();
    CloseI2C();

    OpenI2C();
    WriteCharI2C(0x30);
    WriteCharI2C(0x04);
    OpenI2C();
    WriteCharI2C(0x31);//AckI2C1();
    TempAmbMSB = MasterReadI2C1();AckI2C1();IdleI2C1();//AckI2C1();
    TempAmbLSB = MasterReadI2C1();NotAckI2C1();IdleI2C1();
    CloseI2C();

    OpenI2C();
    WriteCharI2C(0x30);
    WriteCharI2C(0x05);
    OpenI2C();
    WriteCharI2C(0x31);//AckI2C1();
    TempAmbMSB = MasterReadI2C1();AckI2C1();IdleI2C1();//AckI2C1();
    TempAmbLSB = MasterReadI2C1();NotAckI2C1();IdleI2C1();
    CloseI2C();

    OpenI2C();
    WriteCharI2C(0x30);
    WriteCharI2C(0x06);
    OpenI2C();
    WriteCharI2C(0x31);//AckI2C1();
    TempAmbMSB = MasterReadI2C1();AckI2C1();IdleI2C1();//AckI2C1();
    TempAmbLSB = MasterReadI2C1();NotAckI2C1();IdleI2C1();
    CloseI2C();

    OpenI2C();
    WriteCharI2C(0x30);
    WriteCharI2C(0x07);
    OpenI2C();
    WriteCharI2C(0x31);//AckI2C1();
    TempAmbMSB = MasterReadI2C1();AckI2C1();IdleI2C1();//AckI2C1();
    TempAmbLSB = MasterReadI2C1();NotAckI2C1();IdleI2C1();
    CloseI2C();
 */