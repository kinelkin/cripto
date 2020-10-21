/*

   Programa ejemplo para la librería gmp

   A) Compilar con si esta instalado en la maquina

        gcc -o ejemploGMP ejemploGMP.c -lgmp -L.

   B) Si no esta instalado y en la máquina NO podéis hacer: sudo apt-get install libgmp3-dev

	1) Descargar gmp-6.0.0a.tar.bz2 de http://gmplib.org/ o la última versión y descomprimirlo,
	2) y a instalar como cualquier otro programa
		./configure
		make
	3) copiaros la librería libgmp.a (que esta en ...../gmp-6.0.0/.libs/) y
           gmp.h (que está en ...../gmp-6.0.0/) en el directorio de
           vuestras fuentes y a compilar y ejecutar como siempre

        gcc -o ejemploGMP  ejemploGMP.c -L. libgmp.a

        */

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
/*#include "gmp.h"*/



/* PROGRAMA PRINCIPAL */
int main (int argc,char *argv[]) {
  mpz_t a,b,m;
  int modo;

  FILE *entrada,*salida;

  mpz_init (a);
  mpz_init (b);
  mpz_init (m);

  mpz_set_str (a,"123452345234523452352352345112341234213",10);
  mpz_set_str (b,"234562344341234123421341234441234213421",10);

  mpz_add    (m,a,b);

  gmp_printf ("El resultado de la suma es %Zd\n", m);

  mpz_clear (a);
  mpz_clear (b);
  mpz_clear (m);

  return(0);
}
