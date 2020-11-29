#ifndef FUNCIONES_H
#define FUCNIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <gmp.h>

#define MAX_DIGITS 256

void ClearInputBuffer();
void getIntegerFromStdin(long *inputInteger);
long modularExponentiation(long base, long exponent, long module);

#endif