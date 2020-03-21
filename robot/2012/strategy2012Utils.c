#include <stdlib.h>

#include "strategy2012Utils.h"
#include "strategy2012.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../navigation/locationList.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"
#include "../../navigation/navigation.h"

#include "../../robot/gameboard/gameBoard.h"


#include "../../robot/strategy/gameStrategy.h"
#include "../../robot/strategy/gameStrategyHandler.h"
#include "../../robot/strategy/gameStrategyList.h"
#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/gameTargetAction.h"
#include "../../robot/strategy/gameTargetActionItem.h"
#include "../../robot/strategy/gameTargetActionList.h"

#include "armDeviceInterface2012.h"
#include "armDriver2012.h"

// COLOR MANAGEMENT

bool isGreen() {
    return getStrategyContext()->color == COLOR_GREEN;
}

/**
 * Change the location for color.
 */
void changeLocationsForColor() {
    if (isGreen()) {
        return;
    }
    LocationList* locationList = getNavigationLocationList();
    unsigned int i;
    unsigned int size = locationList->size;
    for (i = 0; i < size; i++) {
        Location* location = getLocation(locationList, i);
        location->y = (int) (GAMEBOARD_HEIGHT - location->y);
    }
}

int changeAngleForColor(int angle) {
    if (isGreen()) {
        return angle;
    } else {
        return -angle;
    }
}


// ARM

void armLeftUp() {
    if (isGreen()) {
        armDriver2012Up(ARM_LEFT);
    } else {
        armDriver2012Up(ARM_RIGHT);
    }
}

void armLeftDown() {
    if (isGreen()) {
        armDriver2012Down(ARM_LEFT);
    } else {
        armDriver2012Down(ARM_RIGHT);
    }
}

void armRightUp() {
    if (isGreen()) {
        armDriver2012Up(ARM_RIGHT);
    } else {
        armDriver2012Up(ARM_LEFT);
    }
}

void armRightDown() {
    if (isGreen()) {
        armDriver2012Down(ARM_RIGHT);
    } else {
        armDriver2012Down(ARM_LEFT);
    }
}
