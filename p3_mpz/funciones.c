#include "funciones.h"

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************Apartado 2a****************************************
*******************************************************************************
*******************************************************************************/

void modularExponentiation(mpz_t result, mpz_t base, mpz_t exponent, mpz_t module){
	mpz_t zero;
	mpz_t one;
	mpz_t two;
	mpz_t exponent_comprobation, base_aux, exponent_aux;
	mpz_init_set_ui(zero,0);
	mpz_init_set_ui(one,1);
	
	if (mpz_cmp_ui(module,1) == 0){
		mpz_set(result,zero);
		mpz_clear(zero);
		mpz_clear(one);
		return;
	}
	mpz_init_set(base_aux,base);
	mpz_init_set(exponent_aux, exponent);
	mpz_init(exponent_comprobation);
	mpz_init_set_ui(two,2);
	mpz_set(result,one);
	mpz_mod(base_aux,base_aux,module);


	do{
		mpz_mod(exponent_comprobation,exponent_aux,two);
		if(mpz_cmp_ui(exponent_comprobation,1)>=0){
			mpz_mul(result,result,base_aux);
			mpz_mod(result,result,module);
		}
		mpz_div(exponent_aux,exponent_aux,two);
		mpz_mul(base_aux,base_aux,base_aux);
		mpz_mod(base_aux,base_aux,module);
	} while (mpz_cmp_ui(exponent_aux,0) > 0);

	mpz_clear(base_aux);
	mpz_clear(exponent_aux);
	mpz_clear(exponent_comprobation);
	mpz_clear(zero);
	mpz_clear(one);
	mpz_clear(two);
	return;
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