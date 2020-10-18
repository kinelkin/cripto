#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <stdio.h>
#include <unistd.h>
#include <gmp.h>

void Euclidean(mpz_t resultado, mpz_t a, mpz_t b);
void euclideanExtended(mpz_t resultado, mpz_t a, mpz_t b);

#endif
