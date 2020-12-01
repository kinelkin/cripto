#ifndef FUNCIONES_H
#define FUCNIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <gmp.h>

#define MAX_DIGITS 4096

void ClearInputBuffer();
void getIntegerFromStdin(long long*inputInteger);
long modularExponentiation(long long base, long long exponent, long long module);

#endif