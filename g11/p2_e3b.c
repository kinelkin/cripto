#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "DES.h"
#include "funciones.h"
/* Constantes para el DES */

#define LEN_W 64


int main(int argc, char *argv[]){
	long long orig_w_in, orig_c_in, mod_w_in, mod_c_in, aux_out, aux_in;
	long long bits_orig[ROUNDS + 1], bits_mod[ROUNDS + 1];
	long long bit, modifier, aux_cmp;
	int round, changes[ROUNDS + 1] = {0}, i, j;
  FILE* file_in = NULL, *out = NULL;
  int length;
  long int n, file_size;
	long long *hist = NULL;

	if(argc < 3) {
			printf("Args error, it should be like: -i <f_in>");
			return -1;
	}

	if((file_in = fopen(argv[2], "a")) == NULL){
	printf("Error reading file from args \n");
	return -1;
}
	file_size = findFileSize(argv[2]);
	while(file_size % 8 != 0){
			fprintf(file_in,"%c",(rand()%36)+65);
			file_size += 1;
	}
	fclose(file_in);

	// destroy contents of these files (from previous runs, if any)
	out = fopen("cipher.txt", "wb+");
	fclose(out);
	out = fopen("result.txt", "wb+");
	fclose(out);


	if(strcmp(argv[1],"e") || strcmp (argv[1],"d")){
			create16Keys();
		n = file_size / 8;
		convertCharToBit(n, argv[2]);
		encrypt(n);
	}else{
			printf("Error, type e for encryption\n");
	}

	/*GET ORIGINAL VALUES*/
	hist = get_des_hist();
	for(i=0; i<ROUNDS +1; i++)
		bits_orig[i] = hist[i];

	av_mode_on();
	encrypt(n);
	/*GET ORIGINAL VALUES*/
	hist = get_des_hist();
	for(i=0; i<ROUNDS +1; i++)
		bits_mod[i] = hist[i];

	for(i=0; i<ROUNDS +1; i++){
		aux_cmp = (bits_mod[i])^(bits_orig[i]);
		/*COUNT THE NUMBER OF 1s*/
		for(j=0; j<LEN_W; j++){
			if((aux_cmp & 1) == 1)
				changes[i]++;
			aux_cmp = aux_cmp >> 1;
		}
	}
	printf("\nChange in Plaintext:");
	for(i=0; i<ROUNDS +1; i++){
		printf("\nROUND %d: %d bits", i, changes[i]);
	}



	// modifier = 1; /*00000.......000001*/
	//
	// /*USING ORIGINAL TEXT AND KEY*/
	// aux_in = origin_w_in;
	// for(round=0; round<DES_ROUNDS; round++){
	// 	bits_orig[round] = aux_in;						/*Store block at each round to track differences*/
	// 	aux_out = round_des(aux_in);
	// 	aux_in = aux_out;
	// }
	// bits_orig[round] = aux_in;						/*Final Output also stored*/
	//
	// /*Modifying 1 bit in original text*/
	// mod_w_in = orig_w_in^modifier;
	// /*USING MODIFIED TEXT*/
	// aux_in = mod_w_in;
	// for(round=0; round<DES_ROUNDS; round++){
	// 	bits_mod[round] = aux_in;						/*Store block at each round to track differences*/
	// 	aux_out = round_des(aux_in);
	// 	aux_in = aux_out;
	// }
	// bits_mod[round] = aux_in;						/*Final Output also stored*/
	//
	// /*Comparing modified bits round by round*/
	// for(round=0; round<=DES_ROUNDS; round++){
	// 	aux_cmp = (bits_orig[round])^(bits_mod[round]);
	// 	/*counting the number of changes in each round*/
	// 	bit = 1;
	// 	for(i=0; i<LEN_W; i++){
	// 		if((bit & aux_cmp) == bit)
	// 			changes[round]++;
	// 		bit << 1;
	// 	}
	// }

	return 0;
}
