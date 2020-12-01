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

long modularExponentiation(long long base, long long exponent, long long module){
	long long result = 1;
	
    if (1 & exponent)
		result = base;

	while (1) {
		if (!exponent) break;
		exponent >>= 1;
		base = (base * base) % module;
		if (exponent & 1)
			result = (result * base) % module;
	}
	return result;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************Apartado 2b****************************************
*******************************************************************************
*******************************************************************************/