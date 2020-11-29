#include "funciones.h"

int main(){
    long base = 0, exponent = 0, mod = 0;
	mpz_t base_gmp, exponent_gmp, mod_gmp, result_gmp;

	printf("This program called Potencia computes base to the power exponent module m\n");
	puts("Enter base:");
	getIntegerFromStdin(&base);
	puts("Enter exponent:");
	getIntegerFromStdin(&exponent);
	puts("Enter module:");
	getIntegerFromStdin(&mod);
	printf("%ld to the power %ld ≡ %ld (mod%ld)\n", base, exponent, modularExponentiation(base, exponent, mod), mod);

	mpz_init(base_gmp);
	mpz_init(exponent_gmp);
	mpz_init(mod_gmp);
	mpz_init(result_gmp);
	mpz_set_ui (base_gmp, base);
	mpz_set_ui (exponent_gmp, exponent);
	mpz_set_ui (mod_gmp, mod);
	mpz_powm (result_gmp, base_gmp, exponent_gmp, mod_gmp);
	gmp_printf("You can compare the results. Here is the result using the GMP library. RESULT = %Zd\n", result_gmp);
	mpz_clear(base_gmp);
	mpz_clear(exponent_gmp);
	mpz_clear(mod_gmp);
	mpz_clear(result_gmp);
	return 0;
}