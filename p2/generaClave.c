#include <time.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "DES.h"

// Funcion para imprimir uint64_t en binario

void imprime_bits(uint64_t v){
    int i;
    for(i = 0; i < 64; i++){
        if( ((v << i) & FIRSTBIT) == (uint64_t)0)
            printf("0");
        else
            printf("1");
    }
}



//Genera una clave random de 64 bits, añadiendo los bits de paridad correspondientes (último bit de cada byte)
//Además, comprueba si las claves son débiles usando encripta

static void genera_clave(uint64_t* key){
    srand(time(NULL));

    int i, bit_paridad = 0;
    uint64_t aux_key[16];
    uint64_t next_key;
    aux_key[0] = *key;

    for(i = 0; i < 64; i++){

        if(i % 8 == 7){
            if(bit_paridad == 1)
                *key += (FIRSTBIT >> i);
            bit_paridad = 0; 
        }
        else{
            if(rand() % 2 == 1){
                *key += (FIRSTBIT >> i);
                bit_paridad = bit_paridad == 0 ? 1 : 1;
            }
        }
    }


    for(i = 0; i < 16; i++){
        encripta(&aux_key[i], &next_key, i);
        if(i != 15)
            aux_key[i + 1] = next_key;
    }


    bool clave_debil = false;

    for(i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            if(j != i){
                if(aux_key[i] == aux_key[j])
                    clave_debil = true;
            }
        }
    }

    // Si la clave generada es débil, realizamos otra vez el algoritmo
    if(clave_debil){
        genera_clave(key);
    }
}

int main(){
    uint64_t key = 0;

    genera_clave(&key);

    printf("Hemos generado una clave para ti: \n");
    imprime_bits(key);
    printf("\n");

    return EXIT_SUCCESS;
}
