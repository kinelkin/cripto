#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "DES.h"


int main(int argc, char *argv[]){

    FILE* file_in = NULL, *out = NULL;
    unsigned char *iv;
    int length;
    long int n, file_size;

    if(argc < 3) {
        printf("Args error, it should be like: <iv> <f_in>");
        return -1;
    }

    /*iv = (unsigned char *)argv[2];

	length = strlen((char *)iv);

    if(length > 64){
        printf("IV too long, it should be 64 characters long");
        return -1;
    }*/

    if((file_in = fopen(argv[2], "a")) == -1){
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
	out = fopen("decrypted.txt", "wb+");
	fclose(out);

    if(strcmp(argv[1],"e") || strcmp (argv[1],"d")){
        create16Keys();
	    n = file_size / 8;
	    convertCharToBit(n, argv[2]);
	    encrypt(n);
        decrypt(n);
    }else{
        printf("Error, type e for encryption or d for decryption\n");
    }


	return 0;
}
