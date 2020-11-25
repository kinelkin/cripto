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

#define DES_ROW_SHIFT 5
#define DES_COL_SHIFT 1

#define SHIFT 4
#define MODE_C 'C'
#define MODE_D 'D'

/* 1 0000 0000  = '100' for aes division */
#define BASE_INT 256
#define BYTESIZE 8
#define BITS_IN_BYTE 9
#define MAX_BYTE 255
/* 0001 1011 = '1B' for aes multiplication*/
#define XTIME_CTE 27
#define AES_80 128
#define M_X "11b"


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
Name:   get_col_des
IN:     int a -- number to get sbox col from
OUT:    int -- number obtained
DESC:   shifts a 1 bit to the left
        then shifts it 2 bits to the right (obtains a2 a3 a4 a5)
        a = a1 a2 a3 a4 a5 a6 = 101011
        aux = 010110 (a2 a3 a4 a5 a6 0)
        aux = 000101 (0 0 a2 a3 a4 a5)
*******************************************************************************
*******************************************************************************/
int get_col_des(int a);

/******************************************************************************
*******************************************************************************
Function
Name:   get_row_des
IN:     int a -- number to get sbox row from
OUT:    int -- number obtained
DESC:   shifts a 5 bits to the right to obtain the msb
        stores this in aux1 and shifts one to the left
        shifts a 5 bits to the left and then to the right to obtain lsb
        XORs both results (obtains a1 a6)
        a = a1 a2 a3 a4 a5 a6 = 101011
        aux1 = 000001 (00000a1) --> 000010 (0000a10)
        aux2 = 000001 (00000a6)
        aux1 XOR aux2 = 000011 (0000a1a6)
*******************************************************************************
*******************************************************************************/
int get_row_des(int a);












/******************************************************************************
*******************************************************************************
Function
Name:   get_col
IN:     int a -- number to get sbox col from
OUT:    int -- number obtained
DESC:   shifts a 4 bits to the right
        EG: a = '1001 0011' --> 0000 1001
*******************************************************************************
*******************************************************************************/
int get_col(int a);

/******************************************************************************
*******************************************************************************
Function
Name:   get_row
IN:     int a -- number to get sbox row from
OUT:    int -- number obtained
DESC:   shifts a 4 bits to the left and then back to the right (to fill extra)
        bits with 0s
        EG: a = '1001 0011' --> 0011 0000 --> 0000 0011
*******************************************************************************
*******************************************************************************/
int get_row(int a);

/******************************************************************************
*******************************************************************************
Function
Name:   bin_div
IN:     int n -- number to divide
        int d -- divisor
        int *res  --  pointer to store quotient
        int *rem  --  pointer to store remainder
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
void bin_div(int n, int d, int *res, int *rem);


/******************************************************************************
*******************************************************************************
Function
Name:   euclides_aes
IN:     int r0 -- larger number to divide
        int r1 -- smaller number divisor
OUT:    int -- mcd of r0 and r1 in AES (Z2[x]/<m(x)>), m(x) = '11B'
DESC:   calculates the mcd of two polinomials r0 and r1 in Z2[x]/<m(x)>)
        using Euclides' Algorithm
        r0 = q1*r1 + r2
        r1 = q2*r2 + r3
        ...
        r_(n-1) = q_n*r_n + 0
*******************************************************************************
*******************************************************************************/
int euclides_aes(int r0, int r1);

/******************************************************************************
*******************************************************************************
Function
Name:   aes_mult
IN:     int a -- number to mult
        int b -- number to mult
OUT:    aes multiplication of a*b
DESC:   uses xtime function to multiply two numbers in aes
*******************************************************************************
*******************************************************************************/
int aes_mult(int a, int b);

/******************************************************************************
*******************************************************************************
Function
Name:   euclides_ext_aes
IN:     int a -- larger number to divide
        int b -- smaller number divisor
        int *mcd -- int to store mcd
        int *inv -- int to store the inverse
OUT:    void (stores variablesin mcd and inv)
DESC:   calculates the mcd of two polinomials r0 and r1 in Z2[x]/<m(x)>)
        and the inverse of r1
        using Euclides' extended Algorithm
        r0 = q1*r1 + r2 --> r2 = r0 - q1*r1
        r1 = q2*r2 + r3 --> r3 = r1 - q2*r2
        ...
        r_(n-1) = q_n*r_n + 0
        For the division it uses the above function 'bin_div'
*******************************************************************************
*******************************************************************************/
void euclides_ext_aes(int a, int b, int *mcd, int *inv);

/******************************************************************************
*******************************************************************************
Function
Name:   invert_byte
IN:     unsigned char b -- byte to invert
OUT:    inverted byte
DESC:   EG: 0010 1101 --> 1011 0100
*******************************************************************************
*******************************************************************************/
unsigned char invert_byte(unsigned char b);
