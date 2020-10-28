#include "funciones.h"

int main(int argc, char **argv){

  if(argc < 3) {
    printf("Error con los argumentos, que deberia ser de la forma: <clave> <fichero entrada> <fichero salida>");
    return -1;
  }

	int entrada, salida, longitud, leidos = 1;;
	unsigned char *key;
	unsigned char caracter, clave, encriptado;

	if((entrada = open(argv[2], O_RDONLY)) == -1){
		printf("Error al abrir el fichero de entrada \n");
		return -1;
	}

	if((salida = open(argv[3], O_WRONLY | O_CREAT)) == -1){
		printf("Error al abrir el fichero de salida \n");
		return -1;
	}

	key = (unsigned char *)argv[1];
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
