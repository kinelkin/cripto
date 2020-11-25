#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "DES.h"


int main(int argc, char *argv[]){

    FILE* file_in = NULL, *out = NULL;
    unsigned char *iv;
    int length, i;
    long int n, file_size;
    long long iv_long, bit;

    if(argc < 3) {
        printf("Args error, it should be like: <iv> <f_in>");
        return -1;
    }

    iv = (unsigned char *)argv[2];

	  length = strlen((char *)iv);

    iv_long = 0;
    /*Transfrom IV to a number*/
    printf("\n%s",argv[2]);
    iv_long = 0;
    bit = 1;
    for(i=0; i<64; i++){
      // printf("\nargv[%d] = %c", i, argv[2][i]);
      iv_long = iv_long << 1;
      if(argv[2][i] == '1')
        iv_long = iv_long^bit;
    }
    printf("\nIV == %lli or %llx", iv_long, iv_long);

    return -1;

    if(length > 64){
        printf("IV too long, it should be 64 characters long");
        return -1;
    }

    if((file_in = fopen(argv[3], "a")) == NULL){
		printf("Error reading file from args \n");
		return -1;
	}
    file_size = findFileSize(argv[3]);
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
	out = fopen("decrypted.txt", "wb+");
	fclose(out);

    if(strcmp(argv[1],"e") || strcmp (argv[1],"d")){
        create16Keys();
	    n = file_size / 8;
	    convertCharToBit(n, argv[3]);
	    encrypt(n, iv_long);
      decrypt(n, iv_long);
    }else{
        printf("Error, type e for encryption or d for decryption\n");
    }


	return 0;
}
