#ifndef DES_H
#define DES_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define FIRSTBIT 0x8000000000000000 // 1000000000...
#define BITS_IN_PC1 56
#define BITS_IN_PC2 48
#define ROUNDS 16
#define BITS_IN_IP 64
#define BITS_IN_E 48
#define BITS_IN_P 32
#define NUM_S_BOXES 8
#define ROWS_PER_SBOX 4
#define COLUMNS_PER_SBOX 16



void anyadeBit(uint64_t *destino, uint64_t origen, int posicion_origen, int posicion_destino);
void permutacion(uint64_t* info, bool es_inicial);
void encripta(uint64_t* key, uint64_t* siguente_key, int ronda);
void rondas(uint64_t *info, uint64_t key);

#endif
