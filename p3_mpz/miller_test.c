#include "funciones.h"

int main(){

    char *num;
    int rounds, len;
    // long double p, div;
    num = (char*)malloc(sizeof(char)*MAX_DIGITS);
    mpz_t num_gmp;
    mpf_t numer_gmp, div_gmp, p, aux;
    int isPrimeMiller, isPrimeGMP;
    // long long testing;

    puts("Enter an integer to test its primality with Miller-Rabin Algorithm: ");
    scanf("%s", num);
    mpz_init_set_str(num_gmp,num,10);
    len = strlen(num);
    puts("Enter the number of iterations of the Miller-Rabin Algorithm: ");
    scanf("%d", &rounds);

    isPrimeMiller = MillerRabin(num_gmp, rounds);
    if(isPrimeMiller == FALSE)
      printf("\nMiller says that it is not prime");
    else{
      printf("\nPassed the test %d times", isPrimeMiller);
      mpf_init(numer_gmp);
      mpf_set_ui(numer_gmp, pow(4, isPrimeMiller));
      mpf_init (div_gmp);
      mpf_set_d(div_gmp, len*log(2));

      mpf_init(p);
      mpf_init(aux);
      mpf_div(aux, numer_gmp, div_gmp);
      mpf_add_ui(p, aux, 1);
      mpf_ui_div(aux, 1, p);
      mpf_ui_sub(p, 1, aux);

      gmp_printf("\nThis means it's prime with a probability of %.30Ff", p);
    }
    isPrimeGMP = mpz_probab_prime_p(num_gmp,rounds);


    printf("\nHere is the comprobation using GMP\n");
    if(isPrimeGMP == 0){
        gmp_printf("\n%Zd is definitely not prime\n", num_gmp);
    }else if(isPrimeGMP == 1){
        gmp_printf("\n%Zd is probably prime\n", num_gmp);
    }else{
        gmp_printf("\n%Zd is definitely prime\n", num_gmp);
    }

    mpz_clear(num_gmp);

    return 0;
}
