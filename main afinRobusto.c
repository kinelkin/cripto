#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(){
    char fichero[100]="fichero.txt";
    char cifrado[100]="cifrado.txt";
    char plano[100]="plano.txt";
    int modulo;

    printf("Elija un módulo (Sugerencia: Cuanto mayor sea, más robusto será su cifrado):\n");
    scanf("%d", &modulo);


    cifrarAfinRobusto(modulo,5,1,fichero,cifrado);
    descifrarAfinRobusto(modulo,5,1,cifrado,plano);


    return 0;
}
