#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "funciones.h"
/* Constantes para el DES */

#define LEN_W 64

int main(int argc, char *argv[]){
	long long orig_w_in, orig_c_in, mod_w_in, mod_c_in, aux_out, aux_in;
	long long bits_orig[DES_ROUNDS + 1], bits_mod[DES_ROUNDS + 1];
	long long bit, modifier, aux_cmp;
	int round, changes[DES_ROUNDS + 1] = {0}, i;

	modifier = 1; /*00000.......000001*/

	/*USING ORIGINAL TEXT AND KEY*/
	aux_in = origin_w_in;
	for(round=0; round<DES_ROUNDS; round++){
		bits_orig[round] = aux_in;						/*Store block at each round to track differences*/
		aux_out = round_des(aux_in);
		aux_in = aux_out;
	}
	bits_orig[round] = aux_in;						/*Final Output also stored*/

	/*Modifying 1 bit in original text*/
	mod_w_in = orig_w_in^modifier;
	/*USING MODIFIED TEXT*/
	aux_in = mod_w_in;
	for(round=0; round<DES_ROUNDS; round++){
		bits_mod[round] = aux_in;						/*Store block at each round to track differences*/
		aux_out = round_des(aux_in);
		aux_in = aux_out;
	}
	bits_mod[round] = aux_in;						/*Final Output also stored*/

	/*Comparing modified bits round by round*/
	for(round=0; round<=DES_ROUNDS; round++){
		aux_cmp = (bits_orig[round])^(bits_mod[round]);
		/*counting the number of changes in each round*/
		bit = 1;
		for(i=0; i<LEN_W; i++){
			if((bit & aux_cmp) == bit)
				changes[round]++;
			bit << 1;
		}
	}





	return 0;
}
