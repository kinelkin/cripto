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

/*int MillerRabin(mpz_t prime, int accuracy){

    int i;
		mpz_t q, a, mod;
		mpz_t zero, one, two;
		mpz_t res, aux, prime_minus;
		gmp_randstate_t state;
		// mp_bitcnt_t n;
		mpz_init_set_ui(zero,0);
		mpz_init_set_ui(one,1);
		mpz_init_set_ui(two,2);

		mpz_init(aux);
		mpz_init(res);
		mpz_init(prime_minus);
		mpz_sub(prime_minus, prime, one);
		mpz_mod(res, prime, two);
    // if (prime =< 2 || prime % 2 == 0)
		if(mpz_cmp(prime, two) <= 0 || mpz_cmp(res, zero) == 0)
        return FALSE;

		// q = prime - 1;
		mpz_init(q);
		mpz_sub(q, prime, one);
		mpz_mod(res, q, two);
    // while (q % 2 == 0){
		while(mpz_cmp(res, zero) == 0){
        // q /= 2;
				mpz_div(q, q, two);
				mpz_mod(res, q, two);
		}

		mpz_init(a);
		mpz_init(mod);
    for (i = 0; i < accuracy; i++){
				// long long a = rand() % (prime - 1) + 1, aux = q;
				gmp_randinit_default(state);
				mpz_urandomb (a, state, MAX_DIGITS);
				mpz_mod(a, a, prime_minus);
				mpz_add_ui (a, a, 1);
				mpz_set(aux, q);
        modularExponentiation(mod, a, aux, prime);

        // while (aux != prime - 1 && mod != 1 && mod != prime - 1){
				while(mpz_cmp(aux, prime_minus) != 0 && mpz_cmp(mod, one) != 0 && mpz_cmp(mod, prime_minus) != 0){
            // mod = mulMod(mod, mod, prime);
						mpz_mul(aux, aux, two);
            // aux *= 2;
        }
        if (mpz_cmp(mod, prime_minus) != 0 && mpz_cmp(aux, two) == 0)
            return FALSE;
    }
    return i;
}
*/
int MillerRabinTest(mpz_t n, mpz_t m, mpz_t k){
	gmp_randstate_t state;
	mpz_t a, x, n_minus, aux;
	unsigned long i, k_long;
	mpz_t one, two;

	mpz_init_set_ui(one,1);
	mpz_init_set_ui(two,2);
	mpz_init(x);
	mpz_init(a);
	mpz_init(aux);

	mpz_init(n_minus);
	mpz_sub(n_minus, n, one);


	/*Obtain a 1 < a < n-1*/
	gmp_randinit_default(state);
	mpz_urandomb (a, state, MAX_DIGITS);
	mpz_sub_ui(aux, n_minus, 1);
	mpz_mod(a, a, aux);
	mpz_add_ui(a, a, 1);


	modularExponentiation(x, a, m, n);
	/*Posible Prime*/
	if(mpz_cmp(x, one) == 0 || mpz_cmp(x, n_minus) == 0){
		mpz_clear(a);
		mpz_clear(x);
		mpz_clear(n_minus);
		mpz_clear(aux);
		mpz_clear(one);
		mpz_clear(two);
		return TRUE;
	}

	k_long = mpz_get_ui(k);
	for(i = 0; i < k_long; i++){
		mpz_powm(x, x, two, n);
		/*NOT PRIME*/
		if(mpz_cmp(x, one) == 0){
			mpz_clear(a);
			mpz_clear(x);
			mpz_clear(n_minus);
			mpz_clear(aux);
			mpz_clear(one);
			mpz_clear(two);
			return FALSE;
		}
		/*Posible Prime*/
		if(mpz_cmp(x, n_minus) == 0){
			mpz_clear(a);
			mpz_clear(x);
			mpz_clear(n_minus);
			mpz_clear(aux);
			mpz_clear(one);
			mpz_clear(two);
			return TRUE;
		}
	}


	/*Not Prime*/
	mpz_clear(a);
	mpz_clear(x);
	mpz_clear(n_minus);
	mpz_clear(aux);
	mpz_clear(one);
	mpz_clear(two);
	return FALSE;


}


int MillerRabin(mpz_t n, int rounds){
	int i, isPrimeMiller;
	mpz_t aux, mod, n_minus, m, k;
	mpz_t zero, one, two;

	mpz_init_set_ui(zero,0);
	mpz_init_set_ui(one,1);
	mpz_init_set_ui(two,2);

	mpz_init(n_minus);
	mpz_sub(n_minus, n, one);

	mpz_init(k);
	mpz_init(m);
	mpz_init(mod);

	/*Obtain k*/
	mpz_init(aux);
	mpz_mod(mod, n_minus, two);
	mpz_set(k, zero);
	mpz_set(aux, n_minus);
	while(mpz_cmp(mod, one) != 0){
		mpz_divexact(aux, aux, two);
		mpz_add_ui(k, k, 1);
		mpz_mod(mod, aux, two);
	}

	/*Obtain m*/
	mpz_powm (aux, two, k, n);
	mpz_divexact(m, n_minus, aux);
	// gmp_printf("\n%Zd = 2^(%Zd)*%Zd", n_minus, k, m);

	for(i = 0; i < rounds; i++){
		isPrimeMiller = MillerRabinTest(n, m, k);
		if(isPrimeMiller == FALSE){
			mpz_clear(aux);
			mpz_clear(zero);
			mpz_clear(one);
			mpz_clear(two);
			mpz_clear(mod);
			mpz_clear(m);
			mpz_clear(k);
			mpz_clear(n_minus);
			return FALSE;
		}
	}
	mpz_clear(aux);
	mpz_clear(zero);
	mpz_clear(one);
	mpz_clear(two);
	mpz_clear(mod);
	mpz_clear(m);
	mpz_clear(k);
	mpz_clear(n_minus);
	return i;
}

void gen_odd_num(mpz_t num, int bits){
	gmp_randstate_t state;
	mpz_t mod;

	gmp_randinit_default(state);
	gmp_randseed_ui(state, rand());
	// gmp_printf("STATE: %Zd", state);
	mpz_urandomb (num, state, bits);
	// /*set msb to 1*/
	// mpz_setbit(num, 0);
	mpz_init(mod);
	mpz_mod_ui(mod, num, 2);
	/*If even number --> change to odd*/
	if(mpz_cmp_ui(mod, 0) == 0){
		mpz_add_ui(num, num, 1);
	}
	mpz_clear(mod);
	return;
}

void gen_odd_num_bits(mpz_t num, int bits){
	gen_odd_num(num, bits);
	// /*set msb to 1*/
	mpz_setbit(num, bits - 1);
}

void gen_prime_bits(mpz_t prime, int bits){
	gen_odd_num(prime, bits);
	while(MillerRabin(prime, MAX_ROUNDS) == FALSE){
		gen_odd_num(prime, bits);
	}
	return;
}


double gmp_get_ln(mpz_t num) {
	signed long int e;
	// double res;
	double di;
	di = mpz_get_d_2exp(&e, num );

	return log(di) + log(2) * (double) e;
	// res = log(di) + log(2) * (double) e;
	// return res*log(2)
}



	// gmp_printf("\n%Zd/%Zd = %Zd*%Zd + %Zd",n_minus, two, k, two, m);








int isPrime(int a){
	int i, b;

	b = (int) sqrt(a) + 1;
	for(i=2; i<b; i++)
		if(a%i == 0)
			return FALSE;

	return TRUE;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************Apartado 2c****************************************
*******************************************************************************
*******************************************************************************/
