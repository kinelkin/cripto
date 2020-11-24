#include <time.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "DES.h"

void convertToBinary(int n){
	int i, k, m;
	for (i = 7; i >= 0; i--) {
		m = 1 << i;
		k = n & m;
		if (k == 0)
			fprintf(out, "0");
		else
			fprintf(out, "1");
	}
}

static void genera_clave(unsigned int key){
    srand(time(NULL));

    int i, bit_paridad = 0;
    unsigned int aux_key[16];
    unsigned int next_key;
    aux_key[0] = key;

    for(i = 0; i < 64; i++){
        if(i % 8 == 7){
            if(bit_paridad == 1)
                key += (FIRSTBIT >> i);
            bit_paridad = 0; 
        }
        else{
            if(rand() % 2 == 1){
                key += (FIRSTBIT >> i);
                bit_paridad = bit_paridad == 0 ? 1 : 1;
            }
        }
    }

    for(i = 0; i < 16; i++){
        create16Keys();
        if(i != 15)
            aux_key[i + 1] = next_key;
    }

}

int main(){
    unsigned int key[64] = 0;
    FILE* out = fopen("key.txt", "rb");
    genera_clave(key);

    convertToBinary(key);


    return EXIT_SUCCESS;
}
