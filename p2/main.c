#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include "DES.h"

static FILE * salida = NULL;

// Usage
static void usage(int status)
{
    if(status == EXIT_SUCCESS)
    {
        fprintf(stdout,"Forma de uso: desCBC [OPTION] -k=KEY FILE\n"
                "Cifrar/Descifrar con DES.\n\n"
                " -k, --key=KEY     64 bits key\n"
                " -d, --decrypt     Descifrar con DES\n"
                " -e, --encrypt     Cifrar con DES\n"
                " -o, --output=FILE Escribe el resultado en el fichero de salida\n"
                " -h, --help        Ayuda\n");
    }
    else
    {
        fprintf(stderr, "Escribe 'desCBC --help' para más información.\n");
    }
    exit(status);
}


int main(int argc, char ** argv){
    uint64_t key = 0;
    bool encrypt = true;
    FILE * input = NULL;
	int i, c, contador=0;
    int optc = 0;
    const char* short_opts = "dehk:o:";
    const struct option long_opts[] =
    {
        {"decrypt",        no_argument, NULL, 'd'},
        {"encrypt",        no_argument, NULL, 'e'},
        {"help",           no_argument, NULL, 'h'},
        {"output",   required_argument, NULL, 'o'},
        {"key",      required_argument, NULL, 'k'},
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
                    for(int i = 0; optarg[i] != '\0'; i++){
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
            

        default : //Salida sin argumentos
            usage(EXIT_FAILURE);
        }
    }

    if(key == 0){
        fprintf(stderr, "Error: Clave no válida\n");
        usage(EXIT_FAILURE);
    }


    if(argv[optind] == NULL){
        fprintf(stderr, "Error: Falta el archivo de entrada\n");
        usage(EXIT_FAILURE);
    }


    //Si el fichero de entrada no es múltiplo de 64, lo rellenamos para que así sea de 0 y 1 aleatoriamente
    input = fopen(argv[optind], "a+");
    //capitalize? y entonces añadir 0-1 al final
    c = fgetc(input);
    contador += 1;
    while (c != EOF){
        c = fgetc(input);
        contador += 1;
    }

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
    }

    
    uint64_t a_key[16], siguiente_key, data;
    size_t amount; 
    a_key[0] = key;


    //Obtenemos las 16 subkeys
    for(i = 0; i < 16; i++){
        creaSubkeys(&a_key[i], &siguiente_key, i);
        if(i != 15)
            a_key[i + 1] = siguiente_key;
    }
    
    while((amount = fread(&data, 1, 8, input)) > 0){
        if(amount != 8)
            data = data << (8 * (8 - amount));

        //Permutacion inicial
        permutacion(&data, true);

        //Rondas de cifrado
        if(encrypt){
            for(i = 0; i < 16; i++){
                rondas(&data, a_key[i]);
            }
        }
        //Rondas de descifrado
        else
        {
            //Switch bloques
            data = (data << 32) + (data >> 32);

            for(i = 15; i >= 0; i--)
                rondas(&data, a_key[i]);

            //Deshacer el switch de bloques
            data = (data << 32) + (data >> 32);
        }

        //Permutacion final
        permutacion(&data, false);

        if(amount != 8)
            data = data << (8 * (8 - amount));


        //Lo escribimos en el fichero de salida
        fprintf(salida,"%ln",&data);
        data = 0;
    }
 
    fclose(input);
    fclose(salida);

    return EXIT_SUCCESS;
}


