#include <stdio.h>
#include <unistd.h>
#include <gmp.h>

void Euclidean(mpz_t resultado, mpz_t a, mpz_t b){
  mpz_t modulo;
  mpz_init(modulo);

  if(mpz_sgn(a)==0){
    mpz_set(resultado,b);
    return;
  }
  mpz_mod(modulo,b,a);
  Euclidean(resultado,modulo,a);
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

  mpz_clear(x);
  mpz_clear(y);
  mpz_clear(d);
  mpz_clear(x2);
  mpz_clear(x1);
  mpz_clear(y2);
  mpz_clear(y1);
  mpz_clear(q);
  mpz_clear(r);
  mpz_clear(mul);

}


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
