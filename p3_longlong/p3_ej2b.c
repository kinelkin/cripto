#include "funciones.h"

int main(){

    int isPrimeMiller, isPrimeGMP;
    long long testing, accuracy;

    mpz_t test;

    puts("Enter an integer to test its primality with Miller-Rabin Algorithm: ");
    getIntegerFromStdin(&testing);

    puts("Enter the number of iteration of the Miller-Rabin Algorithm: ");
    getIntegerFromStdin(&accuracy);

    isPrimeMiller = MillerRabin(testing, accuracy);
    if (isPrimeMiller)
        printf("\n%lld is prime\n", testing);
    else
        printf("\n%lld is not prime\n", testing);
    
    mpz_init(test);
    mpz_set_ui(test,testing);
    isPrimeGMP = mpz_probab_prime_p(test,accuracy);


    printf("Here is the comprobation using GMP\n");
    if(isPrimeGMP == 0){
        gmp_printf("\n%Zd is definitely not prime\n", test);
    }else if(isPrimeGMP == 1){
        gmp_printf("\n%Zd is probably prime\n", test);
    }else{
        gmp_printf("\n%Zd is definitely prime\n", test);
    }
    
    mpz_clear(test);
    
    return 0;
}