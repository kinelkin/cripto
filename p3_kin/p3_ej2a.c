#include "funciones.h"

int main(){
    long base = 0, exponent = 0, mod = 0;
	printf("This program called Potencia computes base to the power exponent module m\n");
	puts("Enter base:");
	getIntegerFromStdin(&base);
	puts("Enter exponent:");
	getIntegerFromStdin(&exponent);
	puts("Enter module:");
	getIntegerFromStdin(&mod);
	printf("%ld to the power %ld ≡ %ld (mod%ld)\n", base, exponent, modularExponentiation(base, exponent, mod), mod);
	return 0;
}