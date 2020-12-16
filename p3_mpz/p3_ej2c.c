#include "funciones.h"

#define MIN_BITS 100
#define EXP_ARGS 7

int main(int argc, char *argv[]){
  mpz_t p, q, n, ed_minus, phi_n, p_minus, q_minus, e, d, k, m, a, x, y;
  mpz_t aux, aux_s, aux_t, mod, p_guess, q_guess;
  int bits;
  gmp_randstate_t state;
  mpz_t zero, one, two;
  unsigned long k_long, i;

  mpz_init_set_ui(zero,0);
  mpz_init_set_ui(one,1);
  mpz_init_set_ui(two,2);

  mpz_init(p);
  mpz_init(q);
  mpz_init(n);
  mpz_init(e);
  mpz_init(d);
  gmp_randinit_default(state);
  gmp_randseed_ui(state, rand());
  if(argc == 1){


    /*Find a prime for p*/
    srand(time(NULL));
    bits = rand()%MIN_BITS;
    if(bits < 2)
      bits += 2;
    if(bits > MIN_BITS - 2)
      bits -= 2;

    /*generate p*/
    printf("\nBITS == %d", bits);
    gen_prime_bits(p, bits);
    /*generate q*/
    gen_prime_bits(q, MIN_BITS - bits);
    /*n = pq*/
    mpz_mul(n, p, q);
  }
  else if(argc == EXP_ARGS){
    if(argv[1][1] != 'n'){
      printf("\nError: Expected -n but recieved %s", argv[1]);
      return ERR;
    }
    else{
      mpz_set_str(n, argv[2], 10); /*arg= 4*/
    }
    if(argv[3][1] != 'e'){
      printf("\nError: Expected -e but recieved %s", argv[3]);
      return ERR;
    }
    else{
      mpz_set_str(e, argv[4], 10); /*arg= 4*/
    }
    if(argv[5][1] != 'd'){
      printf("\nError: Expected -d but recieved %s", argv[5]);
      return ERR;
    }
    else{
      mpz_set_str(d, argv[6], 10); /*arg= 4*/
    }
  }
  else{
    printf("\nINCORRECT ARGS: Expected ./primo_rsa [-n vn -e ve -d vd]");
  }

  mpz_init(p_minus);
  mpz_init(q_minus);
  mpz_sub_ui(p_minus, p, 1);
  mpz_sub_ui(q_minus, q, 1);
  mpz_init(phi_n);
  mpz_mul(phi_n, p_minus, q_minus);

  mpz_init(aux_s);
  mpz_init(aux_t);
  mpz_init_set_ui(aux, 0);
  /*e: mcd(e,phi(n)) = 1 */
  if(argc == 1){
    while(mpz_cmp_ui(aux, 1) != 0){
      mpz_urandomm (e, state, phi_n);
      mpz_gcdext(aux, aux_s, aux_t, e, phi_n);
    }

    /*d = e^(-1) mod(phi(n))*/

      mpz_invert(d, e, phi_n);
  }

  /*Ya tengo clave publica (e,n) y privada (d,n)*/
  // mpz_init(p);
  // mpz_init(q);
  // mpz_init(n);
  // mpz_init(e);
  // mpz_init(d);
  // mpz_set_ui(p, 929);
  // mpz_set_ui(q, 641);
  // mpz_set_ui(n, 595489);
  // mpz_set_ui(e, 99357);
  // mpz_set_ui(d, 273973);
  // // mpz_set_ui(p, 7);
  // // mpz_set_ui(q, 11);
  // // mpz_set_ui(n, 77);
  // // mpz_set_ui(e, 7);
  // // mpz_set_ui(d, 43);
  gmp_printf("\nP = %Zd\nQ = %Zd\nN = %Zd\nE = %Zd\nD = %Zd", p,q,n,e,d);
  gmp_printf("\nTam en bits de N: %d", mpz_sizeinbase(n, 2));
  printf("\nComenzando VEGAS:\n");


  /*1 obtain k*/
  mpz_init(ed_minus);
  mpz_mul(ed_minus, e, d);
  mpz_sub_ui(ed_minus, ed_minus, 1);


  mpz_init(k);
  mpz_init(mod);
  mpz_mod_ui(mod, ed_minus, 2);
  mpz_set(k, zero);
  mpz_set(aux, ed_minus);
  while(mpz_cmp(mod, one) != 0){
    mpz_divexact(aux, aux, two);
    mpz_add_ui(k, k, 1);
    mpz_mod(mod, aux, two);

  }




  /*1b Obtain m*/
  mpz_init(m);
  mpz_set(m, aux);



  /*2 Obtain a 1 < a < n-1*/
  mpz_init(a);
  mpz_urandomb(a, state, MAX_DIGITS);
  mpz_sub_ui(aux, ed_minus, 1);
  mpz_mod(a, a, aux);
  mpz_add_ui(a, a, 1);

  /*3*/
  mpz_gcdext(aux, aux_s, aux_t, a, n);
  mpz_init(p_guess);
  mpz_init(q_guess);
  if(mpz_cmp_ui(aux, 1) > 0){
    printf("\nP o Q es mcd(a,n)");
    mpz_set(p_guess, aux);
    mpz_divexact(q_guess, n, p_guess);
    gmp_printf("\nP_GUESS = %Zd\nQ_GUESS = %Zd\n", p_guess, q_guess);
    mpz_mul(aux, p_guess, q_guess);
    // if(mpz_cmp(p_guess,p) == 0 || mpz_cmp(p_guess,q) == 0)
    if(mpz_cmp(aux, n) == 0)
      printf("\nYour Guesses are correct");
    else
      printf("\nYour Guesses are incorrect");

    mpz_clears(zero, one, two, NULL);
    mpz_clears(p, q, n, ed_minus, phi_n, p_minus, q_minus, e, d, k, m, a, NULL);
    mpz_clears(aux, aux_s, aux_t, mod, p_guess, q_guess, NULL);
    gmp_randclear(state);
    return OK;
  }


  /*4*/
  mpz_init(x);
  // modularExponentiation(x, a, m, n);
  mpz_powm(x, a, m, n);
  mpz_sub_ui(aux, n, 1);
  if(mpz_cmp_ui(x,1) == 0 || mpz_cmp(x, aux) == 0){
    printf("\nNo Responde\n");
    mpz_clears(zero, one, two, NULL);
    mpz_clears(p, q, n, ed_minus, phi_n, p_minus, q_minus, e, d, k, m, a, x, NULL);
    mpz_clears(aux, aux_s, aux_t, mod, p_guess, q_guess, NULL);
    gmp_randclear(state);
    return ERR;
  }

  /*5*/
  k_long = mpz_get_ui(k);
  mpz_init(y);
  for(i = 1; i < k_long; i++){
    mpz_set(y, x);
    mpz_powm(x, x, two, n);
    if(mpz_cmp_ui(x,1) == 0){
      printf("\nP o Q es mcd(y+1,n)");
      mpz_add_ui(aux, y, 1);
      mpz_gcdext(p_guess, aux_s, aux_t, aux, n);
      mpz_divexact(q_guess, n, p_guess);
      gmp_printf("\nP_GUESS = %Zd\nQ_GUESS = %Zd\n", p_guess, q_guess);
      mpz_mul(aux, p_guess, q_guess);
      // if(mpz_cmp(p_guess,p) == 0 || mpz_cmp(p_guess,q) == 0)
      if(mpz_cmp(aux, n) == 0)
        printf("\nYour Guesses are correct");
      else
        printf("\nYour Guesses are incorrect");
      mpz_clears(zero, one, two, NULL);
      mpz_clears(p, q, n, ed_minus, phi_n, p_minus, q_minus, e, d, k, m, a, x, y, NULL);
      mpz_clears(aux, aux_s, aux_t, mod, p_guess, q_guess, NULL);
      gmp_randclear(state);
      return OK;
    }
    mpz_sub_ui(aux, n, 1);
    if(mpz_cmp(x,aux) == 0){
      printf("\nNO responde");
      mpz_clears(zero, one, two, NULL);
      mpz_clears(p, q, n, ed_minus, phi_n, p_minus, q_minus, e, d, k, m, a, x, y, NULL);
      mpz_clears(aux, aux_s, aux_t, mod, p_guess, q_guess, NULL);
      gmp_randclear(state);
      return ERR;
    }
  }
  printf("\nP o Q es mcd(x+1, n)");
  mpz_add_ui(aux, x, 1);
  mpz_gcdext(p_guess, aux_s, aux_t, aux, n);
  mpz_divexact(q_guess, n, p_guess);
  gmp_printf("\nP_GUESS = %Zd\nQ_GUESS = %Zd\n", p_guess, q_guess);
  mpz_mul(aux, p_guess, q_guess);
  // if(mpz_cmp(p_guess,p) == 0 || mpz_cmp(p_guess,q) == 0)
  if(mpz_cmp(aux, n) == 0)
    printf("\nYour Guesses are correct");
  else
    printf("\nYour Guesses are incorrect");



  mpz_clears(zero, one, two, NULL);
  mpz_clears(p, q, n, ed_minus, phi_n, p_minus, q_minus, e, d, k, m, a, x, y, NULL);
  mpz_clears(aux, aux_s, aux_t, mod, p_guess, q_guess, NULL);
  gmp_randclear(state);
  return OK;

}
