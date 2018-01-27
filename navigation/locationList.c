#include <stdlib.h>
#include <string.h>

#include "locationList.h"
#include "location.h"

#include "../common/2d/2d.h"

#include "../common/error/error.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/printTableWriter.h"

#include "../common/string/cenString.h"

void initLocationList(LocationList* locationList, Location(*locationListArray)[], unsigned int locationListSize) {
    if (locationList == NULL) {
        writeError(LOCATION_LIST_NULL);
        return;
    }
    locationList->locations = locationListArray;
    locationList->maxSize = locationListSize;
}

void clearLocationList(LocationList* locationList) {
    locationList->size = 0;
}

bool isEmptyLocationList(LocationList* locationList) {
    return locationList->size == 0;
}

Location* getLocation(LocationList* locationList, unsigned int index) {
    if (locationList == NULL || locationList->maxSize == 0) {
        writeError(LOCATION_LIST_NOT_INITIALIZED);
        return NULL;
    }
    if (index < 0 || index >= locationList->maxSize) {
        writeError(LOCATION_LIST_INDEX_OUT_OF_BOUNDS);
        return NULL;
    }
    Location* result = (Location*)locationList->locations;
    // we don't need use sizeof because our pointer is a Location* pointer, so the shift
    // is already of the structure, we just have to shift of index.
    result += index;

    return result;
}

void copyLocation(Location* sourceLocation, Location* targetLocation) {
    copyFixedCharArray(&(sourceLocation->name), &(targetLocation->name));
    targetLocation->tmpCost = sourceLocation->tmpCost;
    targetLocation->tmpHandled = sourceLocation->tmpHandled;
    targetLocation->tmpPreviousLocation = sourceLocation->tmpPreviousLocation;
    targetLocation->resultNextLocation = sourceLocation->resultNextLocation;
    targetLocation->x = sourceLocation->x;
    targetLocation->y = sourceLocation->y;
}

void initLocation(Location* location, char* name, int x, int y) {
    FixedCharArray* existingLocationName = &(location->name);
    stringToFixedCharArray(name, existingLocationName);
    location->x = x;
    location->y = y;
    location->tmpCost = NO_COMPUTED_COST;
    location->tmpHandled = false;
    location->tmpPreviousLocation = NULL;
    location->resultNextLocation = NULL;
}

Location* addNamedLocation(LocationList* locationList, char* name, int x, int y) {
    if (locationList == NULL || locationList->maxSize == 0) {
        writeError(LOCATION_LIST_NOT_INITIALIZED);
        return NULL;
    }

    unsigned int size = locationList->size;
    if (size < locationList->maxSize) {
        Location* location = getLocation(locationList, size);
        initLocation(location, name, x, y);
        locationList->size++;
        return location;
    }
    else {
        writeError(TOO_MUCH_LOCATIONS);
        return NULL;
    }
}

Location* addLocation(LocationList* locationList, const FixedCharArray* s, int x, int y) {
    Location* result = addNamedLocation(locationList, NULL, x, y);
    if (result != NULL) {
        FixedCharArray* target = &(result->name);
        copyFixedCharArray(s, target);
    }
    return NULL;
}

Location* findLocationByStringName(LocationList* locationList, char* name) {
    FixedCharArray tempFixedCharArray;
    stringToFixedCharArray(name, &tempFixedCharArray);
    Location* result = findLocationByName(locationList, &tempFixedCharArray);
    return result;
}

Location* findLocationByName(LocationList* locationList, const FixedCharArray* locationName) {
    unsigned int i;
    unsigned int size = locationList->size;
    for (i = 0; i < size; i++) {
        Location* location = getLocation(locationList, i);
        FixedCharArray* locationName2 = &(location->name);
        if (fixedCharArrayEquals(locationName, locationName2)) {
            return location;
        }
    }
    return NULL;
}

bool containsLocation(LocationList* locationList, Location* locationToFind, bool handled) {
    if (locationToFind == NULL) {
        return false;
    }    
    int i;
    int size = locationList->size;
    for (i = 0; i < size; i++) {
        Location* location = getLocation(locationList, i);
        if (location->tmpHandled != handled) {
            continue;
        }
        if (locationEquals(location, locationToFind)) {
            return true;
        }
    }
    return false;
}

Location* getNearestLocation(LocationList* locationList, int x, int y) {
    Location* result = NULL;
    int i;
    int size = locationList->size;
    int min = MAX_COST;

    for (i = 0; i < size; i++) {
        Location* location = getLocation(locationList, i);
        // We can have hole because of "remove"
        if (location == NULL) {
            continue;
        }
        int distance = (int) distanceBetweenPoints2((float) location->x, (float) location->y, (float) x, (float) y);
        if (distance < min) {
            min = distance;
            result = location;
        }
    }
    return result;
}

void removeFirstLocation(LocationList* locationList) {
    // TODO : Implementation is not Optimized ! Use linked list ?
    int size = locationList->size;
    if (size == 0) {
        return;
    }
    int i;
    for (i = 1; i < size; i++) {
        Location* location1 = getLocation(locationList, i - 1);
        Location* location2 = getLocation(locationList, i);
        copyLocation(location2, location1);
    }
    size--;
    locationList->size = size;
}

unsigned int getLocationCount(LocationList* locationList) {
    return locationList->size;
}

// CLEAR


void clearLocationTmpInfo(LocationList* locationList) {
    unsigned int i;
    unsigned int size = locationList->size;
    for (i = 0; i < size; i++) {
        Location* location = getLocation(locationList, i);
        location->tmpCost = NO_COMPUTED_COST;
        location->tmpPreviousLocation = NULL;
        location->tmpHandled = false;
    }
}


// DEBUG

void printLocationLinkedPath(OutputStream* outputStream, Location* startPoint) {
    Location* currentLocation = startPoint;

    while (startPoint != NULL) {
        printLocation(outputStream, currentLocation);
        startPoint = currentLocation->resultNextLocation;
    }
}

// DEBUG AS TABLE

#define LOCATION_LIST_LOCATION_NAME_COLUMN_LENGTH     12
#define LOCATION_LIST_LOCATION_NAME_HEX_COLUMN_LENGTH 12
#define LOCATION_LIST_LOCATION_X_COLUMN_LENGTH        10
#define LOCATION_LIST_LOCATION_Y_COLUMN_LENGTH        10
#define LOCATION_LIST_LOCATION_X_HEXA_COLUMN_LENGTH   10
#define LOCATION_LIST_LOCATION_Y_HEXA_COLUMN_LENGTH   10
#define LOCATION_LIST_LOCATION_LAST_COLUMN_LENGTH     37

/**
* Private.
*/
void printLocationListHeader(OutputStream* outputStream) {
	println(outputStream);
	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "name", LOCATION_LIST_LOCATION_NAME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "name (hex)", LOCATION_LIST_LOCATION_NAME_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "x (mm)", LOCATION_LIST_LOCATION_X_COLUMN_LENGTH);
	appendStringHeader(outputStream, "y (mm)", LOCATION_LIST_LOCATION_Y_COLUMN_LENGTH);
	appendStringHeader(outputStream, "xHex (mm)", LOCATION_LIST_LOCATION_X_HEXA_COLUMN_LENGTH);
	appendStringHeader(outputStream, "xHex (mm)", LOCATION_LIST_LOCATION_Y_HEXA_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, LOCATION_LIST_LOCATION_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

void printLocationTable(OutputStream* outputStream, Location* location) {
	appendFixedCharArrayTableData(outputStream, &(location->name), LOCATION_LIST_LOCATION_NAME_COLUMN_LENGTH);
	appendHexFixedCharArrayTableData(outputStream, &(location->name), LOCATION_LIST_LOCATION_NAME_COLUMN_LENGTH);
	appendDecTableData(outputStream, location->x, LOCATION_LIST_LOCATION_X_COLUMN_LENGTH);
	appendDecTableData(outputStream, location->y, LOCATION_LIST_LOCATION_Y_COLUMN_LENGTH);
	appendHex4TableData(outputStream, location->x, LOCATION_LIST_LOCATION_X_HEXA_COLUMN_LENGTH);
	appendHex4TableData(outputStream, location->y, LOCATION_LIST_LOCATION_Y_HEXA_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, LOCATION_LIST_LOCATION_LAST_COLUMN_LENGTH);
}

void printLocationListTable(OutputStream* outputStream, LocationList* locationList) {
	int i;
	int size = locationList->size;
	printLocationListHeader(outputStream);
	for (i = 0; i < size; i++) {
		Location* location = getLocation(locationList, i);
		printLocationTable(outputStream, location);
	}
	appendTableHeaderSeparatorLine(outputStream);
}

// Tests Data

void addLocationListTestsData(LocationList* locationList) {
	addNamedLocation(locationList, "STAR", 10, 20);
	addNamedLocation(locationList, "OBJ1", 200, 300);
	addNamedLocation(locationList, "OBJ2", 400, 700);
	addNamedLocation(locationList, "END", 1500, 2000);
}
