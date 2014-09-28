/*
 * File:   PCF8563.h
 * Author: f4deb
 *
 * Created on 8 avril 2014, 23:56
 */

#ifndef PCF8563_H
#define	PCF8563_H

//I2C address
#define PCF8563 0xA2


struct Horloge {
    int ti_hour;
    int ti_min;
    int ti_sec;
    int ti_day;
    int ti_wday;
    int ti_month;
    int ti_year;
}hor;



#endif	/* PCF8563_H */

