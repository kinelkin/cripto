#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>


#define N 256

unsigned char s[N];
int cifrado_i;
int cifrado_j;


void swap(unsigned char *x, unsigned char *y){
	char aux;
  aux=*x;
	*x=*y;
	*y=aux;
}

int cifradoFlujo(void){
	int i;

	for(i=0 ; i<N; i++){
		s[i] = i;
  }
  /*Reseteamos el valor*/
	cifrado_i=0;
  cifrado_j=0;

	return 1;
}


int generateKey(unsigned char *key, int longitud){

	for(cifrado_i=0; cifrado_i<N; cifrado_i++){
		cifrado_j = (cifrado_j + s[cifrado_i] + key[cifrado_i % longitud])% N;
		swap(&s[cifrado_i], &s[cifrado_j]);
	}

	cifrado_i = 0;
  cifrado_j = 0;
}

char permutacion(void){
	cifrado_i = (cifrado_i +1 ) % N;
	cifrado_j = (cifrado_j + s[cifrado_i]) % N;
	swap(&s[cifrado_i], &s[cifrado_j]);

	return s[(s[cifrado_i] + s[cifrado_j]) % N];
}


int main(int argc, char **argv){

  if(argc < 3) {
    printf("Error con los argumentos, que deberia ser de la forma: <fichero entrada> <fichero salida> <clave>");
    return -1;
  }

	int entrada, salida, longitud, leidos = 1;;
	unsigned char *key;
	unsigned char caracter, clave, encriptado;

	if((entrada = open(argv[1], O_RDONLY)) == -1){
		printf("Error al abrir el fichero de entrada \n");
		return -1;
	}

	if((salida = open(argv[2], O_WRONLY | O_CREAT)) == -1){
		printf("Error al abrir el fichero de salida \n");
		return -1;
	}

	key = (unsigned char *)argv[3];
	longitud = strlen((char *)key);

	cifradoFlujo();

	generateKey(key, longitud);

	while((leidos = read(entrada, &caracter, 1)) > 0){

		clave = permutacion();

		encriptado = caracter ^ clave;

		write(salida, &encriptado, 1);
	}

	close(entrada);
	close(salida);

	return 1;
}
