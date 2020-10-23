#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gmp.h>
#include <ctype.h>

void euclidean(mpz_t resultado, mpz_t a, mpz_t b);
void euclideanExtended(mpz_t resultado, mpz_t a, mpz_t b);
void cifrarAfin(mpz_t a, mpz_t b, mpz_t m, FILE* entrada, FILE* salida);
void descifrarAfin(mpz_t a, mpz_t b, mpz_t m, FILE* entrada, FILE* salida);


#endif
