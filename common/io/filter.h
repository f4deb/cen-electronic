#ifndef FILTER_H
#define FILTER_H

#include <stdbool.h>

/**
 * Filter function
 * @param input the char as input
 * @param output a pointer on a char
 * @return true if the output must be added, false else
 */
typedef bool filterCharFunction(char input, char* output);

/**
 * A filter which transforms ASCII value to decimal value.
 * @param c the ASCII char to transform to decimalValue
 * @return true if the output must be added, false else
 */
bool filterBinaryToValueChar(char c, char* output);

/**
 * A filter which removes LF and CR.
 * @param c the char to filter
 * @param output the output char !
 * @return true if the output must be added, false else
 */
bool filterRemoveCRLF(char c, char* output);

bool filterRemoveCRLF_255(char c, char* output);

#endif

