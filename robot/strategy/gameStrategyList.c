#include "gameStrategyList.h"
#include "gameStrategy.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

/**
 * Strategy list.
 */
static GameStrategyList strategies;

GameStrategyList* getGameStrategyList(void) {
    return &strategies;
}

void clearGameStrategies() {
    int size = strategies.size;
    int i;
    for (i = 0; i < size; i++) {
        GameStrategy* strategy = strategies.strategies[i];
        clearGameStrategy(strategy);
    }
    strategies.size = 0;
}

void addGameStrategy(GameStrategy* strategy, char* strategyName) {
    unsigned char size = strategies.size;
    if (size < MAX_STRATEGY) {
        strategy->name = strategyName;
        strategies.strategies[size] = strategy;
        strategies.size++;
    }
    else {
        writeError(TOO_MUCH_STRATEGIES);
    }
}

GameStrategy* getGameStrategy(int index) {
    return strategies.strategies[index];
}

int getGameStrategyCount(void) {
    return strategies.size;
}
