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
void cifrarAfin(int m, int a, int b, char* entrada, char* salida);
void descifrarAfin(int m, int a, int b, char* entrada, char* salida);
long int findSize(const char* file_name);
int comprobarInyectividad(mpz_t a, mpz_t b, mpz_t m);
void cifrarAfinRobusto(int m, int a, int b, char* entrada, char* salida);
void descifrarAfinRobusto(int m, int a, int b, char* entrada, char* salida);



#endif
