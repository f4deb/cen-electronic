#include "../timerInterrupt.h"
#include "../timerList.h"

#include <plib.h>
#include <sys/attribs.h>     /* For __ISR definition */
static UINT64 frequency_Counter;
/**
 * @private
 * @interrupt
 * Function called by the timer.
 * Example Code inspired from : http://learn.digilentinc.com/Documents/216
 */
void __ISR(_TIMER_3_VECTOR, IPL3SOFT) Timer3Handler(void) {
    _internalUpdateTimerListValues(1);
    
    // clear the interrupt flag
    mT3ClearIntFlag();
}

/**
 * @private
 * @interrupt
 * Function called by the timer.
 * Example Code inspired from : http://learn.digilentinc.com/Documents/216
 */
void __ISR(_TIMER_1_VECTOR, IPL3SOFT) Timer1Handler(void) {
    _internalUpdateTimerListValues(1);
    //frequency_Counter++;
    // clear the interrupt flag
    mT1ClearIntFlag();
}
