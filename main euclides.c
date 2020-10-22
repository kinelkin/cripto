#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(){

  mpz_t a,b,m;

  mpz_init(a);
  mpz_init(b);
  mpz_init(m);

  mpz_set_str (a,"5",10);
  mpz_set_str (b,"125",10);

  euclidean(m,a,b);
  gmp_printf("%Zd \n",m);

  euclideanExtended(m,a,b);
  gmp_printf("%Zd \n",m);

  mpz_set_str (a,"123452345234523452352352345112341234213",10);
  mpz_set_str (b,"234562344341234123421341234441234213421",10);

  euclidean(m,a,b);
  gmp_printf("%Zd \n",m);

  euclideanExtended(m,a,b);
  gmp_printf("%Zd \n",m);

  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(m);

}
