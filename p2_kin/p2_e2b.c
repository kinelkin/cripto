#include "DES.h"

/*int main(int argc, char *argv[]){
    FILE* file_in = NULL;
    unsigned int key[192];
    long int n, file_size;

    if(argc < 3) {
        printf("Args error, it should be like: <program> <option> <iv> <f_in>");
        return -1;
    }

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
    
    if(strcmp(argv[1],"e") || strcmp (argv[1],"d")){

        create16KeysTRIPLEDES(key);
        n = file_size / 8;
        convertCharToBitTRIPLEDES(n, argv[2]);

        // We will encrypt with K1, decrypt with K2, then encrypt with K3
        key64to48(key);
        // convert temporal1 to temporal2 using K1
        encryptTRIPLEDES(n, "temporal1.txt");	
        key64to48(key + 64);
        // convert temporal2 to temporal1 using K2
        decryptTRIPLEDES(n, "temporal2.txt");	
        key64to48(key + 128);
        // convert temporal1 to temporal2 using K3
        encryptTRIPLEDES(n, "temporal1.txt");	

        // For decryption, we do it the other way around, we will decrypt with K3, encrypt with K2, then decrypt with K1.
        key64to48(key + 128);
        // convert temporal2 to temporal1 using K3
        decryptTRIPLEDES(n, "temporal2.txt");	
        // convert temporal1 to temporal2 using K2
        key64to48(key + 64);
        encryptTRIPLEDES(n, "temporal1.txt");	
        // convert temporal2 to temporal1 using K1
        key64to48(key);
        decryptTRIPLEDES(n, "temporal2.txt");
    }else{
        printf("Error, type e for encryption or d for decryption\n");
    }

	return 0;
}*/