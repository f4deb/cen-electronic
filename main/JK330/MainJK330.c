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

// LCD
//#include "../../drivers/lcd/lcd.h"
//#include "../../drivers/lcd/lcd4d.h"
//#include "../../device/lcd/lcdDevice.h"
//#include "../../device/lcd/lcdDeviceInterface.h"

//#include "../device/led/led.h"

//#include "../drivers/io/MCP9804.h"

//#include "../drivers/io/EEPROM_I2C.h"
//#include "../drivers/io/PCF8563.h"
//#include "../drivers/io/time.h"

//#include "../drivers/lcd/lcd24064.h"
//#include "../drivers/lcd/lcdOutputStream.h"
//#include "../drivers/lcd/lcdProvider_24064.h"



//#include "../menu/menu.h"

//#include "../setup/clockConstants.h"
//#include "drivers/IO/PCF8563.h"


// definition des bits de configuration.
// Quartz externe, PLL x 20/2

/*#pragma config FNOSC    = PRIPLL        // Oscillator Selection
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (PIC32 Starter Kit: use divide by 2 only)
#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
#pragma config FPLLODIV = DIV_1         // PLL Output Divider
#pragma config FPBDIV   = DIV_2         // Peripheral Clock divisor
#pragma config FWDTEN   = OFF           // Watchdog Timer
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale
#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = OFF           // CLKO Enable
#pragma config POSCMOD  = XT            // Primary Oscillator
#pragma config IESO     = OFF           // Internal/External Switch-over
#pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable
#pragma config CP       = OFF           // Code Protect
#pragma config BWP      = OFF           // Boot Flash Write Protect
#pragma config PWP      = OFF           // Program Flash Write Protect
#pragma config ICESEL   = ICS_PGx1      // ICE/ICD Comm Channel Select
#pragma config DEBUG    = ON           // Debugger Disabled for Starter Kit


#define SERIAL_PORT_PC		2
#define SERIAL_PORT_DEBUG 	3


//Definition I2C
#define I2C_CLOCK_FREQ 		(100000)    //100Khz
#define BRG_VAL 0xc6	//100khz
*/

#ifndef MPLAB_SIMULATION
    #ifdef PROG_32
        #define SERIAL_PORT_DEBUG         SERIAL_PORT_2
        #define SERIAL_PORT_PC             SERIAL_PORT_6
        #define SERIAL_PORT_LCD            SERIAL_PORT_5
    #else
        #define SERIAL_PORT_DEBUG         SERIAL_PORT_1
        #define SERIAL_PORT_PC             SERIAL_PORT_2
    #endif
#else
    // We use the same port for both
    #define SERIAL_PORT_PC             SERIAL_PORT_1
    #define SERIAL_PORT_DEBUG         SERIAL_PORT_1
#endif

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

/************************************************************
 * setup														*
 * configure les ports du PIC32 pour les fonctions du projet *
 * @param : none												*
 * @return : none											
 ************************************************************/
void Setup() {

    //Active CONNEXION I2C1
 //   OpenI2C1(I2C_ON, BRG_VAL); //Enable I2C channel
    //   I2C1CONbits.ACKDT=1;
    //   I2C1CONbits.ACKEN=0;

    //Configure les PIN de control de l'afficheur MGSLS24064
//    SetupLCD_24064();

}


int main(void) {
    
    setPicName("MAIN BOARD");

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

    // LCD (LCD03 via Serial interface)
   // initLCDOutputStream(&lcdOutputStream);

    //    UINT32 actualClock;
    Setup();
    Init();

 /*  outputStream = &pcoutputStream;
   appendString(outputStream, "JK330 with PIC32...on UART PC\r");
   outputStream = &debugoutputStream;
   appendString(outputStream, "JK330 with PIC32...on UART DEBUG\r");

   outputStream = &debugoutputStream;
   appendString(outputStream, "Lecture Horloge \r");
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