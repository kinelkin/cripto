#include "DES.h"

/* "permutaci�n" PC1 */
static const unsigned short PC1[BITS_IN_PC1] = {
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4
};

/* "permutaci�n" PC2 */
static const unsigned short PC2[BITS_IN_PC2] = {
	14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

/* n�mero de bits que hay que rotar cada semiclave seg�n el n�mero de ronda */
static const unsigned short ROUND_SHIFTS[ROUNDS] = {
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

/* permutaci�n IP */
static const unsigned short IP[BITS_IN_IP] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

/* inversa de IP */
static const unsigned short IP_INV[BITS_IN_IP] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25
};

/* expansi�n E */
static const unsigned short E[BITS_IN_E] = {
	32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1
};

/* permutaci�n P */
static const unsigned short P[BITS_IN_P] = {
	16, 7, 20, 21,
	29, 12, 28, 17,
	1, 15, 23, 26,
	5, 18, 31, 10,
	2, 8, 24, 14,
	32, 27, 3, 9,
	19, 13, 30, 6,
	22, 11, 4, 25
};

/* cajas S */
static const unsigned short S_BOXES[NUM_S_BOXES][ROWS_PER_SBOX][COLUMNS_PER_SBOX] = {
	{	{ 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
		{ 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
		{ 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
		{ 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 } 	},
	{
		{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
		{ 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
		{ 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
		{ 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }	},

	{	{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
		{ 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
		{ 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
		{ 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }	},

	{	{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
		{ 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
		{ 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
		{ 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }	},
	{
		{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
		{ 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
		{ 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
		{ 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }	},
	{
		{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
		{ 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
		{ 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
		{ 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }	},
	{
 		{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
		{ 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
		{ 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
		{ 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }	},
	{
		{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
		{ 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
		{ 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
		{ 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }	}
};



//uint64_t unsigned integer type with width of exactly 8, 16, 32 and 64 bits respectively
//Coge el bit posicion_origen de origen y lo coloca en la posicion_destino de destino
void cambiaBit(uint64_t *destino, uint64_t origen, int posicion_origen, int posicion_destino){
    uint64_t bit_origen = 0, bit_destino = 0;

    bit_origen = origen & (1 << posicion_origen);
    bit_destino = origen & (1 << posicion_destino);

    origen ^= bit_origen;
    origen ^= bit_destino;

    if(posicion_destino >= posicion_origen){
        origen |= bit_origen << (posicion_destino - posicion_origen);
        origen |= bit_destino >> (posicion_destino - posicion_origen);
    }
    else{
        origen |= bit_origen >> (posicion_origen - posicion_destino);
        origen |= bit_destino << (posicion_origen - posicion_destino);
    }

    *destino = origen;

}


// Realiza la permutacion IP o IP_INV dependiendo del valor de es_inicial
void permutacion(uint64_t* info, bool es_inicial){
    uint64_t aux = 0;
    int i;
    for(i = 0; i < 64; i++){
        if(es_inicial)
            cambiaBit(&aux, *info, IP[i] - 1, i);
        else
            cambiaBit(&aux, *info, IP_INV[i] - 1, i);
    }
    *info = aux;
}

//Genera las subkeys para cada ronda
void creaSubkeys(uint64_t* key, uint64_t* siguente_key, int ronda){
    uint64_t key_izq = 0, key_dcha = 0, key_izq_aux = 0, key_dcha_aux = 0, aux = 0;
    int i;
    *siguente_key = 0;

    // Primera ronda? Entonces => PC-1 
    if(ronda == 0){
        for(i = 0; i < 56; i++){
            if(i < 28){
                aux = 1 << (PC1[i] - 1); 
                printf("UNO %ld\n",aux);
                aux &= *key;
                printf("DOS %ld\n",aux);
                aux = (1 >> (PC1[i] - 1));
                printf("TRES %ld\n",aux);
                aux = (aux << i);
                printf("CUATRO %ld\n",aux);
                key_dcha |= aux;
            }
            else{
                aux = 1 << (PC1[i] - 1); 
                printf("UNO %ld\n",aux);
                aux &= *key;
                printf("DOS %ld\n",aux);
                aux = (1 >> (PC1[i] - 1));
                printf("TRES %ld\n",aux);
                aux = (aux << (i % 28));
                printf("CUATRO %ld\n",aux);
                key_izq |= aux;
            }
        }
        printf("%ld\n", key_izq);
        printf("%ld\n", key_dcha);
    }

    // Otras rondas que no es la primera? => Separa la key en dos mitades.
    else
    {
        for(i = 0; i < 56; i++){
            if(i < 28)
                cambiaBit(&key_dcha, *key, i, i);
            else
                cambiaBit(&key_izq, *key, i, i % 28);
        }
    }

    // Rotaciones (utilizando auxiliares)
    key_izq_aux = ROUND_SHIFTS[ronda] == 1 ? FIRSTBIT : 0xC000000000000000;
    key_dcha_aux = ROUND_SHIFTS[ronda] == 1 ? FIRSTBIT : 0xC000000000000000;
    key_izq_aux = (key_izq & key_izq_aux) >> (28 - ROUND_SHIFTS[ronda]);
    key_dcha_aux = (key_dcha & key_dcha_aux) >> (28 - ROUND_SHIFTS[ronda]);

    key_izq_aux += (key_izq << ROUND_SHIFTS[ronda]);
    key_dcha_aux += (key_dcha << ROUND_SHIFTS[ronda]);

    // Combina 2 keys en 1 (siguiente_key) que será usada en las próximas rondas
    for(i = 0; i < 56; i++){
        if(i < 28)
            cambiaBit(siguente_key, key_izq_aux, i, i);
        else
            cambiaBit(siguente_key, key_dcha_aux, (i % 28), i);
    }

    // PC-2 como último paso antes de devolverla
    *key = 0;

    for(i = 0; i < 48; i++)
        cambiaBit(key, *siguente_key, PC2[i] - 1, i);
}

void rondas(uint64_t *info, uint64_t key){
    uint64_t bi = 0, x = 0, y = 0, sustitucion = 0, bloque_derecho = 0, resultado = 0;
    int i;

    // Expandimos el bloque (función E)
    for(i = 0; i < 48; i++)
        cambiaBit(&bloque_derecho, *info, E[i], i);

    // Hacemos XOR con la key 
    bloque_derecho = bloque_derecho ^ key;

    // Hacemos la sustitucion
    for(i = 0; i < 8; i++){
        
        bi = ((63 << (6 * i)) & bloque_derecho) >> (6 * i);
        y = ((15 << 1) & bi) >> 1;
        cambiaBit(&x, bloque_derecho, 1, 5);
        x &= 3;

        sustitucion = S_BOXES[i][x][y];
        resultado |= sustitucion << (4 * i);
    }

    // Ya tendríamos el bloque derecho terminado
    bloque_derecho = resultado;

    // Permutamos
    resultado = 0;

    for(i = 0; i < 32; i++)
        cambiaBit(&resultado, bloque_derecho, P[i] - 1, i);

    bloque_derecho = resultado;

    // XOR con el bloque izquierdo
    bloque_derecho = bloque_derecho ^ *info;

    // Combina el nuevo bloque y el bloque derecho
    *info = (*info << 32) + (bloque_derecho >> 32);
}
