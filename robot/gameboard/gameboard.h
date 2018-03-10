#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gameboardElement.h"

#include "../../common/io/outputStream.h"

#define CHAR_NO_DRAW                ' '

#define GAMEBOARD_COLUMN_COUNT        80
#define GAMEBOARD_LINE_COUNT          60

#define GAMEBOARD_WIDTH                2000.0f
#define GAMEBOARD_HEIGHT            3000.0f

#define GAMEBOARD_MIDDLE_WIDTH        (GAMEBOARD_WIDTH / 2)    
#define GAMEBOARD_MIDDLE_HEIGHT        (GAMEBOARD_HEIGHT / 2)

/**
 * Print function of the gameboard.
 */
char gameboardPrint(int* element, int column, int line);

/**
 * Print the gameboard in the serial console.
 */
void printGameboard(OutputStream* outputStream);

#endif
