#ifndef HOMOLOGATION_2012_H
#define HOMOLOGATION_2012_H

// INITIAL POSITION

#define ROBOT_POSITION_VIOLET_X                    174.0f
#define ROBOT_POSITION_VIOLET_Y                    174.0f
#define ROBOT_POSITION_VIOLET_ANGLE                679.0f

#define    GAME_BOARD_WIDTH                        2000.0f
#define    GAME_BOARD_HEIGHT                        3000.0f

#define    GAME_BOARD_MIDDLE_WIDTH                    (GAME_BOARD_WIDTH / 2.0f)
#define    GAME_BOARD_MIDDLE_HEIGHT                (GAME_BOARD_HEIGHT / 2.0f)



#define ROBOT_POSITION_RED_X                    ROBOT_POSITION_VIOLET_X
#define ROBOT_POSITION_RED_Y                    (GAME_BOARD_HEIGHT - ROBOT_POSITION_VIOLET_Y)
#define ROBOT_POSITION_RED_ANGLE                -688.0f

/**
 * Define the initial Position
 */
void setInitialPosition(unsigned int color);

/**
 * Do the homologation.
 * @param homologationIndex the index of strategy
 */
void homologation(unsigned int homologationIndex, unsigned int color);

#endif
