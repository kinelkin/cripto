#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "DES.h"


int main(){

    FILE* output = fopen("keyTRIPLE.txt","w");
    unsigned char key[193];
    int i, flag_paridad = 0;

    for (i=0; i<192; i++) {
        if(i % 8 == 7){
            if(flag_paridad%2){
                key[i] = '0';
            }else{
                key[i] = '1';
            }
            flag_paridad=0;
        }else{
            if(rand()%2){
                key[i] = '1';
                flag_paridad+=1;
            }else{
                key[i] = '0';
            } 
        }
	}

    key[192] = '\0';

    printf("Hemos generado una clave para ti: \n");
    printf("%s \n", key);


    fprintf(output,"%s",key);


    return EXIT_SUCCESS;
}