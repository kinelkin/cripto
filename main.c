#include "funciones.h"

int main(){
  mpz_t a,b,m;

  mpz_init(a);
  mpz_init(b);
  mpz_init(m);

  mpz_set_str (a,"5",10);
  mpz_set_str (b,"125",10);
  Euclidean(m,a,b);
  gmp_printf("%Zd \n",m);

  euclideanExtended(m,a,b);
  gmp_printf("%Zd \n",m);

  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(m);

}
