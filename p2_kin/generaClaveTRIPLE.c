#include "DES.h"


int main(){

    FILE* output = fopen("keyTRIPLE.txt","w");
    unsigned char key[193];
    int i, parity_flag = 0;

    for (i=0; i<192; i++) {
        if(i % 8 == 7){
            if(parity_flag%2){
                key[i] = '0';
            }else{
                key[i] = '1';
            }
            parity_flag=0;
        }else{
            if(rand()%2){
                key[i] = '1';
                parity_flag+=1;
            }else{
                key[i] = '0';
            } 
        }
	}

    key[192] = '\0';

    printf("There is a key for you: \n");
    printf("%s \n", key);


    fprintf(output,"%s",key);


    return EXIT_SUCCESS;
}