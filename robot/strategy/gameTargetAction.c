#include <stdlib.h>

#include "gameTargetAction.h"
#include "gameTargetActionItemList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void clearTargetAction(GameTargetAction* targetAction) {
    targetAction->startLocation = NULL;
    targetAction->endLocation = NULL;
    targetAction->timeToAchieve = 0;
    targetAction->pathData = NULL;
    if (targetAction->actionItemList != NULL) {
        clearTargetActionItemList(targetAction->actionItemList);
    }
}

void printGameTargetAction(OutputStream* outputStream, GameTargetAction* targetAction, bool includeItems) {
    appendString(outputStream, "\taction:");
    appendKeyAndName(outputStream, "startLocation=", targetAction->startLocation->name);
    appendKeyAndName(outputStream, ", end=", targetAction->endLocation->name);
    appendStringAndDecf(outputStream, ", timeToAchieve=", targetAction->timeToAchieve);
    println(outputStream);
    GameTargetActionItemList* actionItemList = targetAction->actionItemList;
    if (actionItemList != NULL && includeItems) {
        printGameTargetActionItemList(outputStream, actionItemList);
    }
}
