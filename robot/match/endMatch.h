#ifndef END_MATCH_H
#define END_MATCH_H

#include <stdbool.h>

// forward declaration
struct EndMatch;
typedef struct EndMatch EndMatch;

#include "../../common/timer/cenTimer.h"

#include "../../robot/config/robotConfig.h"

/** We take 5 seconds to be sure that it will be ok . */
#define MATCH_DURATION                    95

/**
* Defines the index for the timer which detects end of the match.
*/
#define END_MATCH_DETECTOR_TIMER_CODE     20

/**
 * All elements to manage the end of the match
 */
struct EndMatch {
    /** To get the configuration. */
    RobotConfig* robotConfig;
    /** The match duration. */
    int matchDurationInSecond;
    /** Current Time In Second. */
    int currentTimeInSecond;
    /** Avoid that it does not take any instruction at the end. */
    bool doNotEnd;
    /** The timer struct to detect the end of the match. */
    Timer* endMatchDetectorDeviceTimer;
};

/**
 * Initializes the end Match structure.
 */
void initEndMatch(EndMatch* endMatch, RobotConfig* robotConfig, unsigned int matchDurationInSecond);

/**
 * Start the match.
 */
void markStartMatch(EndMatch* endMatch);

/**
 * Reset the match.
 */
void resetStartMatch(EndMatch* endMatch);

/**
 * Show to an output Stream the result of the match
*/
void showEnd(EndMatch* endMatch, OutputStream* outputStream);

/**
 * Returns how much time was passed
 */
int getCurrentTimeInSecond(EndMatch* endMatch);

/**
 * Return true if this is the end of the match.
 */
bool isEnd(EndMatch* endMatch);

#endif