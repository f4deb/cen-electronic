//#include <plib.h>
//#include <peripheral/i2c.h>
#include <peripheral/legacy/i2c_legacy.h>

#include "PCF8563.h"
//#include "../../common/I2C/I2Ccommon.h"
#include "../../common/i2c/i2cCommon.h"


/**
 * getTime_8563
 * lit l'heure et la date et la stock dans la structure "hor"
 * @param  : none
 * @return : none
 **/
void getTime_8563 (void){

    //Registre pour acceder a l'horloge
    i2cMasterWriteChar(PCF8563_W,0x02);

    //lecture des data
    portableStartI2C();//OpenI2C();
    MasterWriteI2C1(PCF8563_R);
    hor.ti_sec = MasterReadI2C1() & 0b01111111;   AckI2C1();WaitI2C();
    hor.ti_min = MasterReadI2C1() & 0b01111111;   AckI2C1();WaitI2C();
    hor.ti_hour = MasterReadI2C1() & 0b00111111;   AckI2C1();WaitI2C();
    hor.ti_day = MasterReadI2C1() & 0b00111111;   AckI2C1();WaitI2C();
    hor.ti_wday = MasterReadI2C1() ;AckI2C1();WaitI2C();  //A MODIFIER NON CONFORME
    hor.ti_month = MasterReadI2C1()& 0b00011111;AckI2C1();WaitI2C();
    hor.ti_year = MasterReadI2C1();AckI2C1();WaitI2C();
    portableStopI2C();//CloseI2C();
}

void setTime_8563 (void){
    portableStartI2C();//OpenI2C();
    MasterWriteI2C1(PCF8563_W);
    MasterWriteI2C1(0x02);
    MasterWriteI2C1(hor.ti_sec);
    MasterWriteI2C1(hor.ti_min);
    MasterWriteI2C1(hor.ti_hour);
    MasterWriteI2C1(hor.ti_day);
    MasterWriteI2C1(hor.ti_wday);
    MasterWriteI2C1(hor.ti_month);
    MasterWriteI2C1(hor.ti_year);
    portableStopI2C();//CloseI2C();



}

/*    OpenI2C();
    WriteCharI2C(PCF8563_W);
    WriteCharI2C(0x00);
    WriteCharI2C(hor.ti_hour);
    WriteCharI2C(hor.ti_min);
    WriteCharI2C(hor.ti_day);
    WriteCharI2C(hor.ti_month);
    CloseI2C();
 */
void printTime(OutputStream* outputStream){
    appendHex2(outputStream, hor.ti_hour); //heure
    appendString(outputStream, ":");
    appendHex2(outputStream, hor.ti_min); //min
    appendString(outputStream, ":");
    appendHex2(outputStream, hor.ti_sec); //sec

    appendString(outputStream, " ");
    appendHex2(outputStream, hor.ti_day); //day

    append(outputStream, '/');
    appendHex2(outputStream, hor.ti_month); //month
    append(outputStream, '/');
    appendHex2(outputStream, hor.ti_year); //month
}