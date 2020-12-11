#include "funciones.h"

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************Apartado 2a****************************************
*******************************************************************************
*******************************************************************************/


void mulMod(mpz_t result, mpz_t a, mpz_t b, mpz_t mod){
    mpz_t x;
	mpz_t y;
	mpz_t two;
	mpz_set_ui(two,2);
	mpz_mod(y,a,mod);
    
	while (mpz_cmp_ui(b,0)){
		mpz_mod(b,b,two);
        if (mpz_cmp_ui(b,1)){    
			mpz_add(x,x,y);
			mpz_mod(x,x,mod);
        }
		mpz_mul(y,y,two);
		mpz_mod(y,y,mod);
		mpz_div(b,b,two);
    }
	mpz_mod(x,x,mod);
	mpz_set(result,x);

}

void modularExponentiation(mpz_t result, mpz_t base, mpz_t exponent, mpz_t module){
	mpz_t result_mulmod;
	mpz_t one;
	mpz_t two;
	mpz_t condition;
	mpz_init(result_mulmod);
	mpz_init(condition);
	mpz_init_set_ui(one,1);
	mpz_init_set_ui(two,2);
	mpz_set_ui(result,1);
    mpz_and(condition, exponent, one);
	if (mpz_cmp_ui(exponent,0))
		 mpz_set(result,base);

	while (1) {
		if (mpz_cmp_ui(exponent,0)) break;
		mpz_div(exponent, exponent, two);
		mulMod(result_mulmod,base,base,module);
		mpz_set(base,result_mulmod);
		mpz_and(condition,exponent,one);
		if (mpz_cmp_ui(condition,0)){
			mulMod(result_mulmod,result,base,module);
			mpz_set(result,result_mulmod);
		}

	}

}


/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************Apartado 2b****************************************
*******************************************************************************
*******************************************************************************/
/*
int MillerRabin(long long prime, int accuracy){

    int i;
    long long q;

    if (prime < 2)
        return 0;
    
    if (prime != 2 && prime % 2 == 0)
        return 0;
    
    q = prime - 1;
    while (q % 2 == 0){
        q /= 2;
    }

    for (i = 0; i < accuracy; i++){

        long long a = rand() % (prime - 1) + 1, aux = q;
        long long mod = modularExponentiation(a, aux, prime);

        while (aux != prime - 1 && mod != 1 && mod != prime - 1){
            mod = mulMod(mod, mod, prime);
            aux *= 2;
        }
        if (mod != prime - 1 && aux % 2 == 0)
            return 0;
    }
    return 1;
}
*/

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************Apartado 2c****************************************
*******************************************************************************
*******************************************************************************/