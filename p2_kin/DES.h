#ifndef DES_H
#define DES_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define BITS_IN_PC1 56
#define BITS_IN_PC2 48
#define ROUNDS 16
#define BITS_IN_IP 64
#define BITS_IN_E 48
#define BITS_IN_P 32

//DES
void expansion(int pos, int text);
int initialPermutation(int pos, int text);
int F(int i);
long long XOR(long long a, long long b);
int ToBits(int value);
int SBox(int XORtext[]);
int PBox(int pos, int text);
void cipher(int Round, int mode);
void finalPermutation(int pos, int text);
void convertToBinary(int n);
int convertCharToBit(long int n, char* filename);
long long array_to_long(long int array[], int len);
void Encryption(long int plain[], long int iv);
void Decryption(long int plain[]);
void convertToBits(int ch[]);
int bitToChar(char* filename);
void bitToChar_dec(FILE *out, long long a);
void key56to48(int round, int pos, int text);
int key64to56(int pos, int text);
void key64to48(unsigned int key[]);
void encrypt(long int n, long int iv);
void decrypt(long int n, long int iv);
void create16Keys();
long int findFileSize(char* filename);

//TRIPLE DES
void create16KeysTRIPLEDES();
void encryptTRIPLEDES(long int n, char* string);
void decryptTRIPLEDES(long int n, char* string);
void EncryptionTRIPLEDES(long int plain[]);
void DecryptionTRIPLEDES(long int plain[]);
int convertCharToBitTRIPLEDES(long int n, char* filename);

#endif
