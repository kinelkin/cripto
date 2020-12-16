#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <gmp.h>
#include <math.h>

#define MAX_DIGITS 8192
#define TRUE 1
#define FALSE 0
#define ERR -1
#define OK 1
#define BITS 'b'
#define SEC 'p'
#define MAX_ROUNDS 24

void modularExponentiation(mpz_t result, mpz_t base, mpz_t exponent, mpz_t module);
int millerRabin(mpz_t n, int rounds);
void gen_odd_num(mpz_t num, int bits);
void gen_odd_num_bits(mpz_t num, int bits);
double gmp_get_ln(mpz_t num);
void gen_prime_bits(mpz_t prime, int bits);


#endif
