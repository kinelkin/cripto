#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gmp.h>
#include <ctype.h>

#define ERR -1
#define OK 1
#define NO_PUNCT 0
#define TRUE 1
#define FALSE 0

#define MAX_KEY 20
#define MAX_WORDS 25
#define MAX_MCDS 100
#define MAX_REP_LEN 4
#define MIN_REP_LEN 3
#define K_ANALYSIS "k_analysis.txt"
#define ENGLISH_FREQUENCIES [8.04, 1.54, 3.06, 3.99, 12.51, 2.3, 1.96, 5.49, 7.26, 0.16, 0.67, 4.14, 2.53, 7.09, 7.6, 2.0, 0.11, 6.12, 6.54, 9.25, 2.71, 0.99, 1.92, 0.19, 1.73, 0.19]
#define ENGLIS_IC 0.065769
#define ALFABET_LEN 26
#define TOO_SMALL 0.001

#define MAX_PERM 100
#define PAD_LETTER 'X'

void euclidean(mpz_t resultado, mpz_t a, mpz_t b);
void euclideanExtended(mpz_t resultado, mpz_t a, mpz_t b);
void cifrarAfin(int m, int a, int b, char* entrada, char* salida);
void descifrarAfin(int m, int a, int b, char* entrada, char* salida);
long int findSize(const char* file_name);
int comprobarInyectividad(mpz_t a, mpz_t b, mpz_t m);
void cifrarAfinRobusto(int m, int a, int b, char* entrada, char* salida);
void descifrarAfinRobusto(int m, int a, int b, char* entrada, char* salida);

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************GENERAL********************************************
*******************************************************************************
*******************************************************************************/

/******************************************************************************
*******************************************************************************
Function
Name: get_pos
IN:   int *array  - array of ints
      int len     - lenght of array
      int num     - number to look for
OUT:  int i - position of num in array
      ERR   - number not found in array
Desc: Returns the position of Num in the array or ERR if not found
*******************************************************************************
*******************************************************************************/
int get_pos(int *array, int len, int num);
/******************************************************************************
*******************************************************************************
Function
Name: capitalize
IN:   FILE *F_IN    -- Open Filestrean to set in Capital Letters
      char *fname   -- name of file
OUT:  void
Desc: takes the input file, creates another file with the original contents in
      capital letters.
      Name of new file is 'cap_'+fname
*******************************************************************************
*******************************************************************************/
char *capitalize(FILE *F_IN, char *fname);

/******************************************************************************
*******************************************************************************
Function
Name:   file_to_var
IN:     FILE *F_IN  --  Open filestream to read from
        int punct   --  0 means no punctuation, 1 means punctuation included
OUT:    char *var   --  char * with all the chars from the file
                    --  in case of error NULL
*******************************************************************************
*******************************************************************************/
char *file_to_var(FILE *F_IN, int punct, long *len);

/******************************************************************************
*******************************************************************************
Function
Name: mcd
DESC: calculates the mcd of two numbers
*******************************************************************************
*******************************************************************************/
long mcd(long a, long b);

/******************************************************************************
*******************************************************************************
Function
Name: most_probable_mcd
DESC: takes a list of ints and sees the number that divides the greates amount
      of ints in the list
*******************************************************************************
*******************************************************************************/
int most_probable_mcd(int *mcd_list, int total);

/******************************************************************************
*******************************************************************************
Function
Name: check_word
DESC: checks to see if a given word is in the all_words matrix
*******************************************************************************
*******************************************************************************/
int check_word(char all_words[MAX_WORDS][MAX_REP_LEN+1], char word[MAX_REP_LEN], int num_w, int len_word);

/******************************************************************************
*******************************************************************************
Function
Name: absol
DESC: returns absolute value of double a
*******************************************************************************
*******************************************************************************/
double absol(double a);

/******************************************************************************
*******************************************************************************
Function
Name: avg
IN:   double *list -  list of doubles
      int len      -  length of list
DESC: returns absolute value of a list of doubles
*******************************************************************************
*******************************************************************************/
double avg(double *list, int len);

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************VIGENERE*******************************************
*******************************************************************************
*******************************************************************************/

/******************************************************************************
*******************************************************************************
Function
Name:   vigenere
IN:     int mode    --  'C'|'D' Encrypt/Decrypt
        char *k     --  string key used to encrypt/decrypt (letters between A and z)
        FILE *F_IN  --  open filestream to read from
        FILE *F_OUT --  open filestream to write to
OUT:    void
Desc:   Mode == 'C' --> Encrypt
          Encrypts the contents of F_IN by Vigenere using the key stored in k
          Writes the output in F_OUT
        Mode == 'D'  --> Decrypt
          Decrypts the contents of F_IN by Vigenere using the key stored in k
          Writes the output in F_OUT
          Only works correctly if the same key is used as to encrypt originally
*******************************************************************************
*******************************************************************************/
void vigenere(int mode, char *k, FILE *F_IN, FILE *F_OUT);

/****************************KASISKI*******************************************/

/******************************************************************************
*******************************************************************************
Function
Name: all_instances
IN:   FILE *F_analysis  - Open Filestream to write table in
      int len_word      - Length of word looking for
      long i_0:         - position of initial instance in string
      long i_1:         - position of second instance in string
      char *string      - string to analyse
      long len_str      - length of string to analyse
OUT:  int - mcd of all the distances between an instance and the original
DESC: scrolls through the string looking for exac copies of the original string
      once it has found an instance it computes the distance to the original
      len_word lettered instance and computes its mcd with the previous mcd;
*******************************************************************************
*******************************************************************************/
int all_instances(FILE *F_analysis, int len_word, long i_0, long i_1, char *string, long len_str);



/******************************************************************************
*******************************************************************************
Function
Name:   find_key_len_kasiski
IN:     FILE *F_IN  --  Open filestream of encrypted Text
OUT:    int ---> ERR if no length found
            ---> length of key
Desc:   Takes the input text. Copies it to an aux file.
        Superpositions the same text shifted by 1 char.
        Counts the number of incidences and repeats until MAX_KEY. At this point
        it returns the shift which had the most amount of incidences.
*******************************************************************************
*******************************************************************************/
int find_key_len_kasiski(FILE *F_IN);


/****************************COINCIDENCE INDEX*********************************/

/******************************************************************************
*******************************************************************************
Function
Name:   ic_sum
IN:     double *alfabet - array of doubles with the frequencies of each letter of the alfabet
        int len - len of the alfabet
OUT:    double sum - IC of the alfabet
Desc:   Takes the input list of doubles
        Adds each value squared
*******************************************************************************
*******************************************************************************/
double ic_sum(double *alfabet, int len);



/******************************************************************************
*******************************************************************************
Function
Name:   calculate_ic
IN:     char *t1  - text on which to caclculate the coincidence Index
        long len_str  - length of the text
        int m - number of columns to divide text in
OUT:    double - the average IC of the m columns
Desc:   Takes the input text (t1), divides it into m columns
        For each column it calculates the Coincidence Index (IC) by counting
        the frequency of each letter in the column and then calling ic_sum
        Finally it returns the average of all these columns
        So if m = 3 and the 3 results are [0.046, 0.044, 0.045] it will return
        0.045
*******************************************************************************
*******************************************************************************/
double calculate_ic(char *t1, long len_str, int m);



/******************************************************************************
*******************************************************************************
Function
Name:   find_key_len_ic
IN:     FILE *F_IN  - Open Filestream of vigenere encrypted file from which we
                      wish to find the length of the vigenere key by CI
                      (Coincidence Index)
OUT:    int candidate - keylen which has been found
Desc:   Takes the input file and transfers it to a variable (cipher) for simpler
        handling
        Tries MAX_KEY number of columns to divide the cipher into:
        m=i=1,2,3....MAX_KEY
        Calls calculate_ic to obtain the CI with i columns and filters to
        retain the IC closest to the ENGLISH IC.
        If there are many columns that result close to the ENGLISH IC then
        it is probably the case of them being related by a common mcd.
        The function stores them in an array and later determines the mcd.
        Finally it returns the candidate length for the key.
*******************************************************************************
*******************************************************************************/
int find_key_len_ic(FILE *F_IN);


/******************************************************************************
*******************************************************************************
Function
Name:   break_vigenere
IN:     FILE *F_IN  - Open Filestream of vigenere encrypted file from which we
                      wish to find the length vigenere key
        int keylen  - length of key used to encrypt the file
OUT:    int candidate - keylen which has been found
Desc:   Takes the input file and transfers it to a variable (cipher) for simpler
        handling
        Divides the text into keylen columns
        Calculates the frequency of each letter in the columns
        Uses that E is the most frequent letter to find the the key by simple
        Caeser decryption.
*******************************************************************************
*******************************************************************************/
char *break_vigenere(FILE *F_IN, int keylen);

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************DOUBLE PERMUTATION*********************************
*******************************************************************************
*******************************************************************************/

/******************************************************************************
*******************************************************************************
Function
Name:   pad_txt
IN:     char *txt   - text to pad
        int bloc    - size of blocs
        long *len   - length of text
        int mode    - PUNCTUATION included or not
Desc:   Calculates the extra chars it has to add to the text
        Creates a string of the new size and reserves memory for it
        Copies the old string and completes with padding Char
        EG:
        bloc size = 15
        if the text is  AAA       The end result is BBB
                        BBB                         DDD
                        CCC                         CCC
                        D                           DXX
                                                    XXX

*******************************************************************************
*******************************************************************************/
char *pad_txt(char *txt, int bloc, long *len, int mode);
/******************************************************************************
*******************************************************************************
Function
Name:   perm_rows
IN:     char **txt  - pointer to a variable containing the padded text
        long len    - length of the text
        int m       - length of K1
        int n       - length of K2 (to calculate bloc size)
        int *k1     - permutation vector
Desc:   Calculates the bloc size (m*n)
        Divides the text into blocs of M*N
        For each bloc it permutates the rows according to the vector K1
        EG:
        K1 = [1 3 2 4 0]
        bloc size = 15
        if the text is  AAA       The end result is BBB
                        BBB                         DDD
                        CCC                         CCC
                        DDD                         EEE
                        EEE                         AAA

*******************************************************************************
*******************************************************************************/
void perm_rows(char **txt, long len, int m, int n, int *k1);


/******************************************************************************
*******************************************************************************
Function
Name:   perm_cols
IN:     char **txt  - pointer to a variable containing the padded text
        long len    - length of the text
        int m       - length of K1 (to calculate bloc size)
        int n       - length of K2
        int *k2     - permutation vector
Desc:   Calculates the bloc size (m*n)
        Divides the text into blocs of M*N
        For each bloc it permutates the cols according to the vector K2
        EG:
        K1 = [1 2 0]
        bloc size = 15
        if the text is  ABC       The end result is BCA
                        ABC                         BCA
                        ABC                         BCA
                        ABC                         BCA
                        ABC                         BCA

*******************************************************************************
*******************************************************************************/
void perm_cols(char **txt, long len, int m, int n, int *k2);

/******************************************************************************
*******************************************************************************
Function
Name:   cipher_dp
IN:     FILE *F_IN    - Open Filestream in CAPS to cipher
        FILE *F_OUT   - OPEN Filestream to write cipher to
        char *fname   - Filename of open F_IN (to save CAPS version)
        int m         - Number of rows in a bloc (len K1)
        int n         - Number of cols in a bloc (len K2)
        int *k1       - Row Permutation Vector
        int *k2       - Col permutation Vector
Desc:   Takes F_IN (text in CAPS)and transfers it to a variable for simpler
        manipulation
        Pads the text (to make up for block size)
        Copies the padded text to another file for later comparison
        Permutates the rows using K1
        Permutates the cols using K2
        Saves the permutated text to F_OUT
*******************************************************************************
*******************************************************************************/
void cipher_dp(FILE *F_IN, FILE *F_OUT, char *fname, int m, int n, int *k1, int *k2);

/******************************************************************************
*******************************************************************************
Function
Name:   invert_perm
IN:     int **perm  - pointer to a permutation vector
        int len     - length of permutation vector
Desc:   Takes the permutation vector
        Looks for each coordinate, where its value is in the permutation
        vector and assigns that value to the new vector
        EG:
        Vector = [1 3 2 4 0]
          --> Inverted = [ 4 0 2 1 3]
*******************************************************************************
*******************************************************************************/
void invert_perm(int **perm, int len);

/******************************************************************************
*******************************************************************************
Function
Name:   decipher_dp
IN:     FILE *F_IN    - Open Filestream in CAPS to cipher
        FILE *F_OUT   - OPEN Filestream to write cipher to
        char *fname   - Filename of open F_IN (to save CAPS version)
        int m         - Number of rows in a bloc (len K1)
        int n         - Number of cols in a bloc (len K2)
        int *k1       - Row Permutation Vector
        int *k2       - Col permutation Vector
Desc:   Takes F_IN (cipher text) and transfers it to a variable for simpler
        manipulation
        Inverts the permutation vectors K1, K2
        Permutates the rows using K1*
        Permutates the cols using K2*
        Saves the deciphered text to F_OUT
*******************************************************************************
*******************************************************************************/
void decipher_dp(FILE *F_IN, FILE *F_OUT, int m, int n, int *k1, int *k2);


/******************************************************************************
*******************************************************************************
*********************************DECRYPT***************************************
*******************************************************************************
*******************************************************************************/
void print_all_words(char all_words[static MAX_WORDS][MAX_REP_LEN+1], int num_w);

void print_list(int *list, int len);

void print_mcds(int all_mcds[MAX_MCDS], int y);

void print_ab(double alfabet[ALFABET_LEN]);





#endif
