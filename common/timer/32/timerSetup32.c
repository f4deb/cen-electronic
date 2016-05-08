#include "../timerSetup.h"
#include "../cenTimer.h"
#include "../timerList.h"

#include <plib.h>
//#include <timer.h>
#include <peripheral/timer.h>

/**
 * @private
 */
void _initTimers() {
    // The following instruction sets up Timer 3 to set the T3 Flag at a rate of 
    // 28 800 Hz assuming that the PBCLK is running at 8 MHz (PLL * 20) => 160 MHz / 4 / 256 / (4 + 1) => 28 800. This instruction 
    // sets the PR1 value to 4 (compute = period + 1).
    OpenTimer3((T3_ON | T3_SOURCE_INT | T3_PS_1_256), 4); 
 
    // The following enables the Timer 1 interrupt priority for 3 and the interrupt sub priority for 1.*/ 
    ConfigIntTimer3((T3_INT_ON | T3_INT_PRIOR_3 | T3_INT_SUB_PRIOR_1)); 
 
    
    
    OpenTimer1((T1_ON | T1_SOURCE_EXT | T1_PS_1_1), 4); 
    // The following enables the Timer 1 interrupt priority for 3 and the interrupt sub priority for 1.*/ 
    ConfigIntTimer1((T1_INT_ON | T1_INT_PRIOR_3 | T1_INT_SUB_PRIOR_1)); 
 
    
    // code to for additional interrupt initializations
    INTEnableSystemMultiVectoredInt(); // Required to enable all interrupts 
}


