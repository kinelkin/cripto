#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>


int main(){
    char fichero[100]="fichero.txt";
    char cifrado[100]="cifrado.txt";
    char plano[100]="plano.txt";

    cifrarAfin(27,5,1,fichero,cifrado);
    descifrarAfin(27,5,1,cifrado,plano);



return 0;
}
