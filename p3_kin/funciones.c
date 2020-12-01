#include "funciones.h"

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************Apartado 2a****************************************
*******************************************************************************
*******************************************************************************/

void ClearInputBuffer() {
	char c = 0;
	while ((c = getchar()) != '\n' && c != EOF);
}

void getIntegerFromStdin(long long *inputInteger) {
	char *inputBuffer = malloc(sizeof(char) * MAX_DIGITS);
	memset(inputBuffer, 0, MAX_DIGITS);
	char *input = NULL;
	while (input == NULL) {
		input = fgets(inputBuffer, MAX_DIGITS, stdin);
		if (inputBuffer[strlen(inputBuffer) - 1] != '\n') {
			fprintf(stderr, "[ERROR]: Too many characters: max input is %d chars.\n", MAX_DIGITS);
			ClearInputBuffer();
			input = NULL;
			continue;
		}
		errno = 0;
		char *endptr = NULL;
		*inputInteger = strtol(input, &endptr, 10);
		if (input == endptr) {
			input[strcspn(input, "\n")] = 0;
			printf("Invalid input: no integer found in %s.\n", input);
			input = NULL;
		}
		if (errno != 0) {
			fprintf(stderr, "[ERROR]: Not a long integer.\n");
			input = NULL;
		}
	}
	free(inputBuffer);
}

long long mulMod(long long a, long long b, long long mod){
    long long x = 0,y = a % mod;
    
	while (b > 0){
        if (b % 2 == 1){    
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}

long long modularExponentiation(long long base, long long exponent, long long module){
	long long result = 1;
	
    if (1 & exponent)
		result = base;

	while (1) {
		if (!exponent) break;
		exponent >>= 1;
		base = mulMod(base,base,module);
		if (exponent & 1)
			result = mulMod(result, base, module);
	}
	return result;
}


/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************Apartado 2b****************************************
*******************************************************************************
*******************************************************************************/

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


/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************Apartado 2c****************************************
*******************************************************************************
*******************************************************************************/