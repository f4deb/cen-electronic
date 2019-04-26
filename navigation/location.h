#ifndef LOCATION_H
#define LOCATION_H

#include <stdbool.h>

#include "../common/string/cenString.h"
#include "../common/io/outputStream.h"

#define MAX_COST                                20000.0f
#define COST_IF_OBSTACLE                        10000.0f
#define COST_DECREASE_STEP                       1000.0f
#define NO_COMPUTED_COST                           -1.0f
#define MAX_DISTANCE_NEAREST_LOCATION             100.0f

struct Location;
typedef struct Location Location;

/**
 * Encapsulates the location.
 */
struct Location {
    /** The name. */
    FixedCharArray name;
    /** The coordinates in x. */
    float x;
    /** The coordinates in y. */
    float y;
    /** Temporary information needed by path finding algorithm. */
    float tmpCost;
    /** Temporary information needed by path finding algorithm. */
    bool tmpHandled;
    /**Result information with the next location to follow the path */
    Location* resultNextLocation;
};

/**
 * Equals function on Location. The equals is based on the name of the location !
 */
bool locationEquals(Location* location1, Location* location2);

#endif
