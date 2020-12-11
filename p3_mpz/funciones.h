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

void modularExponentiation(mpz_t result, mpz_t base, mpz_t exponent, mpz_t module);
void mulmod(mpz_t result, mpz_t a, mpz_t b, mpz_t mod);

#endif