#ifndef PCF8563_H
#define	PCF8563_H

#define CLOCK_REGISTER          0x02

struct Horloge {
    int ti_hour;
    int ti_min;
    int ti_sec;
    int ti_day;
    int ti_wday;
    int ti_month;
    int ti_year;
}hor;

#endif

