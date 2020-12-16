#include "funciones.h"

int main(){
	char *base, *exponent, *mod;
	base = (char*)malloc(sizeof(char)*10000);
	exponent = (char*)malloc(sizeof(char)*10000);
	mod = (char*)malloc(sizeof(char)*10000);
	mpz_t base_gmp, exponent_gmp, mod_gmp, result_gmp;
	mpz_t base_comprobation, exponent_comprobation, mod_comprobation, result_comprobation;

	printf("This program called Potencia computes base to the power exponent module m\n");
	printf("Enter base:\n");
	scanf("%s", base);
	printf("Enter exponent:\n");
	scanf("%s", exponent);
	printf("Enter module:\n");
	scanf("%s", mod);
	mpz_init(result_gmp);
	mpz_init_set_str(base_gmp,base,10);
	mpz_init_set_str(exponent_gmp,exponent,10);
	mpz_init_set_str(mod_gmp,mod,10);
	modularExponentiation(result_gmp,base_gmp, exponent_gmp, mod_gmp);
	gmp_printf("%Zd to the power %Zd ≡ %Zd (mod%Zd)\n", base_gmp, exponent_gmp, result_gmp, mod_gmp);

	mpz_init(result_comprobation);
	mpz_init_set_str(base_comprobation,base,10);
	mpz_init_set_str(exponent_comprobation,exponent,10);
	mpz_init_set_str(mod_comprobation,mod,10);
	mpz_powm (result_comprobation, base_comprobation, exponent_comprobation, mod_comprobation);
	gmp_printf("You can compare the results. Here is the result using the GMP library. RESULT = %Zd\n", result_comprobation);
	mpz_clear(base_gmp);
	mpz_clear(exponent_gmp);
	mpz_clear(mod_gmp);
	mpz_clear(result_gmp);
	mpz_clear(base_comprobation);
	mpz_clear(exponent_comprobation);
	mpz_clear(mod_comprobation);
	mpz_clear(result_comprobation);
	free(base);
	free(exponent);
	free(mod);
	return 0;
}
