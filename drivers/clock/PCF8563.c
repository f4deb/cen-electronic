//#include <plib.h>
//#include <peripheral/i2c.h>
#include <peripheral/legacy/i2c_legacy.h>

#include "PCF8563.h"
//#include "../../common/I2C/I2Ccommon.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/io/buffer.h"




/**
 * getTime_8563
 * lit l'heure et la date et la stock dans la structure "hor"
 * @param  : none
 * @return : none
 **/
void getTime_8563 (Buffer* buffer){

    i2cMasterRegisterReadBuffer(PCF8563, 0x02, 7 ,  buffer);
            int d = bufferReadChar(buffer);
        hor.ti_sec = d & 0b01111111;
        d = bufferReadChar(buffer);
        hor.ti_min = d & 0b01111111;
        d = bufferReadChar(buffer);
        hor.ti_hour = d & 0b00111111;
        d = bufferReadChar(buffer);
        hor.ti_day = d & 0b00111111;
        d = bufferReadChar(buffer);
        hor.ti_wday = d & 0b00001111;
        d = bufferReadChar(buffer);
        hor.ti_month = d & 0b00011111;
        d = bufferReadChar(buffer);
        hor.ti_year = d ;
}

void setTime_8563 (Buffer* buffer){
    
    // charge dans le buffer
    append(getOutputStream(buffer),0x02);
    append(getOutputStream(buffer),hor.ti_sec);//s
    append(getOutputStream(buffer),hor.ti_min);//m
    append(getOutputStream(buffer),hor.ti_hour);//h
    append(getOutputStream(buffer),hor.ti_day);//d
    append(getOutputStream(buffer),hor.ti_wday);//dayweek
    append(getOutputStream(buffer),hor.ti_month);//m
    append(getOutputStream(buffer),hor.ti_year);//y

    //envoie le buffer sur l'I2C
    i2cMasterWriteBuffer(PCF8563, buffer );
}

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