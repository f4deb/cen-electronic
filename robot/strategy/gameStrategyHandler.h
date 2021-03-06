#ifndef GAME_STRATEGY_HANDLER
#define GAME_STRATEGY_HANDLER

#include "../../navigation/location.h"
#include "../../navigation/path.h"

#include "gameStrategyContext.h"

/** Use flag to know if we trace Handler strategy. */
#define DEBUG_STRATEGY_HANDLER

/** Use flag to know if we trace Opponent Robot management. */
#define DEBUG_OPPONENT_ROBOT

/** Minimum angle to add a rotation in degrees. */
#define ANGLE_ROTATION_MIN_DEGREE 5.0f

/** Distance of the opponent to a path to make it unavailable in mm. */
#define DISTANCE_OPPONENT_TO_PATH 200.0f

/** Distance of a detected obstacle in mm. */
#define DISTANCE_OBSTACLE 250.0f

/**
 * Define the time in second for which, if there is no collision, we can reset All path to available. 
 * This time must be > to the notification Collision time, to avoid that it reset it.
 */
#define RESET_OBSTACLE_COLLISION_TIME_SECOND        5.0f

// Init

/**
 * Init the Game Strategy Context.
 */
void initStrategyHandler(GameStrategyContext* gmeStrategyContext);

/**
 * Returns the next target to reach by computing the next target to reach.
 */
GameTarget* findNextTarget(GameStrategyContext* gameStrategyContext);

/**
 * Do the next step in the strategy. Returns false if nothing was done.
 */
bool nextStep(GameStrategyContext* gmeStrategyContext);

// MAIN FUNCTION

/**
 * Function which must be called by the main function to continuously find a next target and after launch the step.
 */
bool nextTargetOrNextStep(GameStrategyContext* gameStrategyContext);

#endif

