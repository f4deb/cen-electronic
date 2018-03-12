#include "PCF8563.h"

#ifdef PROG_32
    #include <peripheral/legacy/i2c_legacy.h>
#endif
#ifdef PROG_30
    #include <i2c.h>
#endif

#include "../../common/clock/clock.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

I2cBusConnection* _pcf8563GetI2cBusConnection(Clock* clock) {
    I2cBusConnection* result = (I2cBusConnection*) clock->object;

    return result;
}

/**
 * @see clock.h
 * @private
 * Read the hour and the date from the Pcf8563, and store in the structure.
 * @param clock the clock
 */
ClockData* _readPcf8563Clock(Clock* clock) {
    I2cBusConnection* i2cBusConnection = _pcf8563GetI2cBusConnection(clock);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    ClockData* clockData = &(clock->clockData);
    
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, PCF8563_WRITE_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, PCF8563_CLOCK_REGISTER);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, PCF8563_READ_ADDRESS);
    WaitI2C(i2cBus);

    clockData->second = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    clockData->minute = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    clockData->hour = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    clockData->day = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    clockData->dayofweek = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    clockData->month = portableMasterReadI2C(i2cBusConnection);
    portableMasterAckI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    clockData->year = portableMasterReadI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    
    clockData->second = clockData->second & 0b01111111;
    clockData->minute = clockData->minute & 0b01111111;
    clockData->hour = clockData->hour & 0b00111111;
    clockData->day = clockData->day & 0b00111111;
    clockData->dayofweek = clockData->dayofweek & 0b00001111;
    clockData->month = clockData->month & 0b00011111;

    return clockData;
}

/**
 * @see clock.h
 * @private
 * Set the Clock into the Pcf8563.
 * @param clock the new value of clock
 */
void _writePcf8563Clock(Clock* clock) {
    I2cBusConnection* i2cBusConnection = _pcf8563GetI2cBusConnection(clock);
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    ClockData* clockData = &(clock->clockData);

    portableMasterWaitSendI2C(i2cBusConnection);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, PCF8563_WRITE_ADDRESS);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, PCF8563_CLOCK_REGISTER);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, clockData->second);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, clockData->minute);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, clockData->hour);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, clockData->day);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, clockData->dayofweek);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, clockData->month);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, clockData->year);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
}

void initClockPCF8563(Clock* clock, I2cBusConnection* i2cBusConnection) {
    initClock(clock, _writePcf8563Clock, _readPcf8563Clock, (int*) i2cBusConnection);
}
