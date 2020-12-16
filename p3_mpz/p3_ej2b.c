#include "funciones.h"

#define MAX_ARGS 7
#define MIN_ARGS 5



int main(int argc, char *argv[]){
  int arg = 1;
  int b, rounds, i, isPrime, isPrimeGMP, bits, max_tries;
  mpf_t sec, p;
  mpf_t numer_gmp, div_gmp, aux;

  mpz_t num;
  long double p_d;
  char *fname_out = NULL;
  FILE *F_OUT = NULL;

  if(argc != MAX_ARGS && argc != MIN_ARGS){
    printf("\nProgram with incorrect args\n");
    printf("\nExpected: primo -%c bits -%c sec [-o file_out ]\n", BITS, SEC);
    return ERR;
  }
  else{
    /************************ bits ************************/
    if( argv[arg][1] != BITS){
      printf("\nExpected -%c but recieved %s\n",BITS, argv[arg]);
      return ERR;
    }
    else b = atoi(argv[++arg]);     /*arg= 2*/

    /************************ SEC ************************/
    if( argv[++arg][1] != SEC){    /*arg= 3*/
      printf("\nExpected -%c but recieved %s\n",SEC, argv[arg]);
      return ERR;
    }
    else {
      mpf_init(sec);
      mpf_set_str(sec, argv[++arg], 10); /*arg= 4*/
    }

  /************************ input/output files ************************/
  if(argc == MAX_ARGS){
    if( argv[++arg][1] != 'o' ){      /*arg=4 */
      printf("\nExpected -o but recieved %s\n", argv[arg]);
      return ERR;
    }
    else fname_out = argv[++arg];              /*arg=5 */

    if(fname_out){
      F_OUT = fopen(fname_out, "w");
      if(F_OUT == NULL){
        printf("\n%s failed to open, setting F_OUT to stdout\n", fname_out);
        F_OUT = stdout;
      }
    }
  }
  else{
    printf("\nSetting F_OUT to stdout");
    F_OUT = stdout;
  }
}

  // printf("\n-%c = %d", BITS, b);
  // gmp_printf("\n-%c = %.10Ff", SEC, p);
  // printf("\nFOUT == %s",fname_out);
  p_d = mpf_get_d(sec);
  mpz_init2(num, b);
  gen_odd_num(num, b);

  rounds = ceil((log((b*log(2) - (1-p_d)*b*log(2))/(1-p_d))/log(4)));
  // printf("\nROUNDS == %d", rounds);

  /*FIND A PRIME*/
  bits = mpz_sizeinbase(num, 2);
  max_tries = (int) log(pow(2, bits));
  max_tries /= 2;
  max_tries++;
  srand(time(NULL));
  for(i = 0; i < max_tries; i++){
    isPrime = MillerRabin(num, rounds);
    if(isPrime == FALSE)
      gen_odd_num_bits(num, bits);
    else break;
  }

  if(i == max_tries)
    printf("\nPRIME NUMBER NOT FOUND");
  else{
    printf("\n\n");
    gmp_fprintf(F_OUT, "NUMBER FOUND: %Zd", num);
    mpf_init(numer_gmp);
    mpf_set_ui(numer_gmp, pow(4, isPrime));
    mpf_init (div_gmp);
    /*mpz_sizeinbase(num, 2) gives us number of bits*/
    mpf_set_d(div_gmp, mpz_sizeinbase(num, 2)*log(2));

    mpf_init(p);
    mpf_init(aux);
    mpf_div(aux, numer_gmp, div_gmp);
    mpf_add_ui(p, aux, 1);
    mpf_ui_div(aux, 1, p);
    mpf_ui_sub(p, 1, aux);
    gmp_fprintf(F_OUT, "\nMY TEST: Prime with probability: %.30Ff", p);
    fprintf(F_OUT, "\nMY TEST: ROUNDS Passed = %d", isPrime);

    isPrimeGMP = mpz_probab_prime_p(num,rounds);
    printf("\nHere is the comprobation using GMP:");
    if(isPrimeGMP == 0){
        gmp_printf("\nDefinitely not prime\n");
    }else if(isPrimeGMP == 1){
        gmp_printf("\nProbably prime\n");
    }else{
        gmp_printf("\nDefinitely prime\n");
    }
  }


  if(F_OUT != stdout)
    fclose(F_OUT);
  return OK;

}
