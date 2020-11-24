#ifndef DES_H
#define DES_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define FIRSTBIT 0x8000000000000000
#define BITS_IN_PC1 56
#define BITS_IN_PC2 48
#define ROUNDS 16
#define BITS_IN_IP 64
#define BITS_IN_E 48
#define BITS_IN_P 32

void expansion_function(int pos, int text);
int initialPermutation(int pos, int text);
int F1(int i);
int XOR(int a, int b);
int ToBits(int value);
int SBox(int XORtext[]);
int PBox(int pos, int text);
void cipher(int Round, int mode);
void finalPermutation(int pos, int text);
void convertToBinary(int n);
int convertCharToBit(long int n);
void Encryption(long int plain[]);
void Decryption(long int plain[]);
void convertToBits(int ch[]);
int bittochar();
void key56to48(int round, int pos, int text);
int key64to56(int pos, int text);
void key64to48(unsigned int key[]);
void decrypt(long int n);
void encrypt(long int n);
void create16Keys();
long int findFileSize();

#endif