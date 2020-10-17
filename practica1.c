#include <stdio.h>
#include <unistd.h>
#include <gmp.h>

void Euclidean(mpz_t resultado, mpz_t a, mpz_t b){

  mpz_gcd(resultado,a,b);

  return;

}

void euclideanExtended(mpz_t resultado, mpz_t a, mpz_t b){

  mpz_t x,y,d;
  mpz_t x2,x1,y2,y1,q,r,mul;
  mpz_init(x);
  mpz_init(y);
  mpz_init(d);

  mpz_init(x2);
  mpz_init(x1);
  mpz_init(y2);
  mpz_init(y1);
  mpz_init(q);
  mpz_init(r);
  mpz_init(mul);


  while(mpz_sgn(b)){
    mpz_divexact(q,a,b);
    mpz_mod(r,a,b);
    mpz_mul(mul,q,x1);
    mpz_sub(x,x2,mul);
    mpz_mul(mul,q,y1);
    mpz_sub(y,y2,mul);
    mpz_set(a,b);
    mpz_set(b,r);
    mpz_set(x2,x1);
    mpz_set(y2,y1);
    mpz_set(y1,y);
    mpz_set(d,a);
  }

  mpz_set(x,x2);
  mpz_set(y,y2);
  mpz_set(resultado,d);

}


int main(){
  mpz_t a,b,m;

  mpz_init(a);
  mpz_init(b);
  mpz_init(m);

  mpz_set_str (a,"35002136253",10);
  mpz_set_str (b,"15246984520",10);
  Euclidean(m,a,b);
  gmp_printf("%Zd \n", m);

  euclideanExtended(m,a,b);
  gmp_printf("%Zd \n",m);



  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(m);

}
