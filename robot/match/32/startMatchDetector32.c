#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include "startMatchDetector32.h"
#include "../startMatch.h"

#include <stdbool.h>
#include <plib.h>

bool isMatchStarted32(StartMatch* startMatch) {
    // The match is started if the pin is to 0V
    return PORTGbits.RG3 == 0;
}
