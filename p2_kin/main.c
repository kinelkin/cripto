#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include "DES.h"

/*static void usage(int status)
{
    if(status == EXIT_SUCCESS)
    {
        fprintf(stdout,"Forma de uso: desCBC [OPTION] -k=KEY FILE\n"
                "Cifrar/Descifrar con DES.\n\n"
                " -k, --key=KEY     64 bits key\n"
                " -d, --decrypt     Descifrar con DES\n"
                " -e, --encrypt     Cifrar con DES\n"
                " -o, --output=FILE Escribe el resultado en el fichero de salida\n"
                " -i, --iv=IV       Vector de inicialización\n"
                " -h, --help        Ayuda\n");
    }
    else
    {
        fprintf(stderr, "Escribe 'desCBC --help' para más información.\n");
    }
    exit(status);
}*/

int main(){
    /*uint64_t key = 0, iv = 0;
    bool encrypt = true;
    FILE * input = NULL;
	int i, contador=0;
    int optc = 0;
    const char* short_opts = "dehk:o:";
    const struct option long_opts[] =
    {
        {"decrypt",        no_argument, NULL, 'd'},
        {"encrypt",        no_argument, NULL, 'e'},
        {"help",           no_argument, NULL, 'h'},
        {"output",   required_argument, NULL, 'o'},
        {"key",      required_argument, NULL, 'k'},
        {"iv",       required_argument, NULL, 'iv'}
        {NULL,                       0, NULL,   0}
    };


    while((optc = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1){
        switch(optc){
			case 'e':
				encrypt = true;
				break;
            case 'd': 
                encrypt = false;
                break;

            case 'h': 
                usage(EXIT_SUCCESS);
                break;

            case 'o': 
                salida = fopen(optarg, "w");
                if(salida == NULL){
                    fprintf(stderr, "Error en el fichero de salida");
                    exit(EXIT_FAILURE);
                }
                break;

            case 'k': 
                if(optarg){
                    // Convertimos la cadena leída por pantalla en un uint_t
                    for(i = 0; optarg[i] != '\0'; i++){
                        if(i > 64){
                            printf("Error la clave es mayor a 64\n");
                            exit(EXIT_FAILURE);
                        }
                        if(optarg[i] == '1')
                            key += (FIRSTBIT >> i);
                    }
                }
                else{
                    usage(EXIT_FAILURE);
                }
                break;

            case 'iv': 
                if(optarg){
                    // Convertimos la cadena leída por pantalla en un uint_t
                    for(i = 0; optarg[i] != '\0'; i++){
                        if(i > 64){
                            printf("Error la clave es mayor a 64\n");
                            exit(EXIT_FAILURE);
                        }
                        if(optarg[i] == '1')
                            iv += (FIRSTBIT >> i);
                    }
                }
                else{
                    usage(EXIT_FAILURE);
                }
                break;
            

        default : //Salida sin argumentos
            usage(EXIT_FAILURE);
        }
    }

    if(key == 0){
        fprintf(stderr, "Error: Clave no válida\n");
        usage(EXIT_FAILURE);
    }

    if(iv == 0){
        fprintf(stderr, "Error: Vector de inicialización no válido\n");
        usage(EXIT_FAILURE);
    }

    if(argv[optind] == NULL){
        fprintf(stderr, "Error: Falta el archivo de entrada\n");
        usage(EXIT_FAILURE);
    }

    //Si el fichero de entrada no es múltiplo de 64, lo rellenamos para que así sea de 0 y 1 aleatoriamente
    input = fopen(argv[optind], "a+");
    fseek(input, 0, SEEK_END);
    contador = ftell(input);
    rewind(input);

    while((contador % 65) != 0){
        contador +=1;
        fprintf(input,"%d", rand()%2);
    }

    if(input == NULL){
        fprintf(stderr, "Error abriendo el fichero de entrada\n");
        usage(EXIT_FAILURE);
    }


    if(salida == NULL)
        salida = fopen("salida.txt", "w");


    if(salida == NULL){
        fprintf(stderr, "Error al abrir el fichero de salida\n");
        exit(EXIT_FAILURE);
    }*/

    FILE* out;
	// destroy contents of these files (from previous runs, if any)
	out = fopen("result.txt", "wb+");
	fclose(out);
	out = fopen("decrypted.txt", "wb+");
	fclose(out);
	out = fopen("cipher.txt", "wb+");
	fclose(out);

	create16Keys();

	long int n = findFileSize() / 8;

	convertCharToBit(n);

	encrypt(n);
	decrypt(n);

	return 0;
}