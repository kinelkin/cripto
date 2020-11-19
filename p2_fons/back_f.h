#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define ERR -1
#define OK 1
#define NO_PUNCT 0
#define TRUE 1
#define FALSE 0
#define NO_PUNCT 0

#define MODE_EQ 'P'
#define MODE_NOT_EQ 'I'

#define ALFABET_LEN 26
#define ADDITION 10

#define SHIFT 4
#define MODE_C 'C'
#define MODE_D 'D'

/* 1000 0000 = '80' for division */
#define BASE_INT 128
#define BITS_IN_BYTE 8


/******************************************************************************
*******************************************************************************
Function
Name:   gen_key
IN:     long len  - length of key to generate
        int mode  - mode of generating key (P = Random, I = Not Random)
OUT:    char *key   --  char * with all the chars from the key
                    --  in case of error NULL
DESC:   Reserves memory for the key
        If mode = P then gnerates a random number between 0 and ALFABET_LEN - 1
        and appends it to the key
        If mode = I then generates a random number between 0 and
        ALFABET_LEN - REDUCTION (less numbers) and appends it to the key
        Returns the key
*******************************************************************************
*******************************************************************************/
char *gen_key(long len, int mode);

/******************************************************************************
*******************************************************************************
Function
Name:   cypher_desp
IN:     char *orig  - original text in variable
        char *key   - key to cypher with
        long len    - length of both key and cypher
OUT:    char *cypher  - char * with cyphered text
                      - in case of error NULL
DESC:   Takes the original text and the key
        Reserves memory for the cypher
        if the current char is between 'A'-'Z' then it adds the key
        to the char mod ALFABET_LEN
        if it is not (punctuation, space etc) then it leaves it as is.
        Returns the cypher
*******************************************************************************
*******************************************************************************/
char *cypher_desp(char *orig, char *key, long len);

/******************************************************************************
*******************************************************************************
Function
Name:   decypher_desp
IN:     char *cypher  - cypher text in variable
        char *key   - key to cypher with
        long len    - length of both key and cypher
OUT:    char *orig  - char * with orig text
                      - in case of error NULL
DESC:   Takes the cypher text and the key
        Reserves memory for the original text
        if the current char is between 'A'-'Z' then it adds the key
        to the char mod ALFABET_LEN
        if it is not (punctuation, space etc) then it leaves it as is.
        Returns the original text
*******************************************************************************
*******************************************************************************/
char *decypher_desp(char *cypher, char *key, long len);

/******************************************************************************
*******************************************************************************
Function
Name: analyse_prob
IN:   FILE *F_OUT     - Open Filestrean to write stats to
      char *original  - variable with original text in capital letters
      long len        - length of original text
OUT:  void
Desc: reads text char by char
      adds frequency to letter in array corresponding to letter read
      at the end prints out stats for each letter in probability (divided by len)
*******************************************************************************
*******************************************************************************/
void analyse_prob(FILE *F_OUT, char *original, long len);

/******************************************************************************
*******************************************************************************
Function
Name: analyse_prob_cond
IN:   FILE *F_OUT     - Open Filestrean to write stats to
      char *original  - variable with original text in capital letters
      char *cypher    - variable with original text in capital letters
      long len        - length of original text
OUT:  void
Desc: reads text char by char
      adds frequency to letter in array corresponding to letter read
      at the end prints out stats for each letter in probability (divided by len)
*******************************************************************************
*******************************************************************************/
void analyse_prob_cond(FILE *F_OUT, char *original, char *cypher, long len);

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
Name:   get_col
IN:     unsigned char a -- number to get sbox col from
OUT:    unsigned char -- number obtained
DESC:   shifts a 4 bits to the right
        EG: a = '1001 0011' --> 0000 1001
*******************************************************************************
*******************************************************************************/
unsigned char get_col(unsigned char a);

/******************************************************************************
*******************************************************************************
Function
Name:   get_row
IN:     unsigned char a -- number to get sbox row from
OUT:    unsigned char -- number obtained
DESC:   shifts a 4 bits to the left and then back to the right (to fill extra)
        bits with 0s
        EG: a = '1001 0011' --> 0011 0000 --> 0000 0011
*******************************************************************************
*******************************************************************************/
unsigned char get_row(unsigned char a);

/******************************************************************************
*******************************************************************************
Function
Name:   bin_div
IN:     unsigned char n -- number to divide
        unsigned char d -- divisor
        unsigned char *res  --  pointer to store quotient
        unsigned char *rem  --  pointer to store remainder
OUT:    void (stores results in res and rem)
DESC:   does binary AES division using XOR
        begins by aligning the two most signficant 1s
        n XOR d
        shifts q (quotient) to the left
        adds 1 to q
        if n's msb != 1 then shift both n and q one bit to the left
        in the end shift n and q back the necessary amount to account for
        previous shifts
        q = q << (shift - cont + 1);
        n = n >> (extra + shift + 1);

        store q in *res (quotient)
        store n in *rem (remainder)
*******************************************************************************
*******************************************************************************/
void bin_div(unsigned char n, unsigned char d, unsigned char *res, unsigned char *rem);


/******************************************************************************
*******************************************************************************
Function
Name:   euclides
IN:     unsigned char a -- number to get sbox row from
OUT:    unsigned char -- number obtained
DESC:   shifts a 4 bits to the left and then back to the right (to fill extra)
        bits with 0s
        EG: a = '1001 0011' --> 0011 0000 --> 0000 0011
*******************************************************************************
*******************************************************************************/
unsigned char get_row(unsigned char a);
