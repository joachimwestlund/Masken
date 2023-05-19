#ifndef __HISCORE_H__
#define __HISCORE_H__

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

FILE* file;

/** Return value for the cypher functions */
char ret[16];

/**
 * @brief This function initializes the hiscore. Creates the file if no one exists.
 * @return TRUE if success and FALSE if failure.
 */
char init_hiscore(void);

/**
 * @brief scrambles the string.
 * @return the scrambled text.
 */
char* scramble(char *str);

/**
 * @brief unscrambles the string.
 * @return the unscrambled string.
 */
char* unscramble(char* str);

#endif // __HISCORE_H__
