#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>


int main(){
    mpz_t a,b,m;
    char fichero[100]="fichero.txt";
    char cifrado[100]="cifrado.txt";
    char plano[100]="plano.txt";
    char comprobacion1[100]="comprobacion1.txt";
    int inyectiva;



    mpz_init(a);
    mpz_init(b);
    mpz_init(m);

    mpz_set_str (a,"5",10);
    mpz_set_str (b,"1",10);
    mpz_set_str (m,"27",10);


    inyectiva = comprobarInyectividad(a,b,m,comprobacion1);

    if(inyectiva!=1){
      printf("NO ES INYECTIVA");
      mpz_clear(a);
      mpz_clear(b);
      mpz_clear(m);
      return -1;
    }

    cifrarAfin(a,b,m,fichero,cifrado);
    descifrarAfin(a,b,m,cifrado,plano);



    #include "funciones.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <gmp.h>
return 0

    ;
}
