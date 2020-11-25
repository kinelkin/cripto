/******************************************************************************
*******************************************************************************
File:   p2_e4a.c
Desc:   prints the Pp(x) and Pp(x|y) of text and its cypher
*******************************************************************************
*******************************************************************************/
#include "funciones.h"

#define EXP_ARGS 4
/*128 = 0x80*/
#define BASE_CHAR 128
/*99 = 0x63 */
#define DEF_00 99
#define AES_N 16

static const char MATRIX_X[BYTESIZE][BITS_IN_BYTE] = {"8f", "c7", "e3", "f1", "f8", "7c", "3e", "1f"};
static const char INV_MATRIX_X[BYTESIZE][BITS_IN_BYTE] = {"25", "92", "49", "a4", "52", "29", "94", "4a"};
static const char VECTOR_C[BITS_IN_BYTE] = "63";
static const char INV_VECTOR_C[BITS_IN_BYTE] = "5";

int main(int argc, char *argv[]){
  int mode;
  int arg = 1;
  char *fname_out = NULL;
  FILE *F_OUT = NULL;
  int c, i, mcd, b, b_aux, j, odd, d[BYTESIZE], b1[BYTESIZE], e, m_x, d_aux, vect_c, s;
  int matrix_x[BYTESIZE];

  if(argc != EXP_ARGS){
    printf("\nProgram with incorrect args\n");
    printf("\nExpected: sbox_aes {-%c|-%c} [-o file_out ]\n", MODE_C, MODE_D);
    return ERR;
  }
  else{
    /************************ MODE ************************/
    if( argv[arg][1] != MODE_C && argv[arg][1] != MODE_D ){
      printf("\nExpected {-%c|-%c} but recieved %s\n",MODE_C, MODE_D, argv[arg]);
      return ERR;
    }
    else mode = argv[arg++][1];     /*arg= 1*/

  /************************ input/output files ************************/
      /*TWO FILES*/
  if( argv[arg][1] != 'o' ){      /*arg=2 */
    printf("\nExpected -o but recieved %s\n", argv[arg]);
    return ERR;
  }
    else fname_out = argv[++arg];              /*arg=3 */
  }

  if(fname_out){
    F_OUT = fopen(fname_out, "w");
    if(F_OUT == NULL){
      printf("\n%s failed to open, setting F_OUT to stdout\n", fname_out);
      F_OUT = stdout;
    }
  }
  else{
    F_OUT = stdout;
  }

  m_x = (int)strtol(M_X, NULL, 16);

  if(mode == MODE_C){
    vect_c = (int)strtol(VECTOR_C, NULL, 16);
    for(i = 0; i < BYTESIZE; i++){
      matrix_x[i] = (int)strtol(MATRIX_X[i], NULL, 16);
    }
    /*For each entry in the sbox*/
    for(c = 0; c <= MAX_BYTE; c++){
      for(i = 0; i < BYTESIZE; i++)
        d[i] = 0;
      euclides_ext_aes(m_x, c, &mcd, &b); /*Only intrested in b (b = inv(c) mod (mx))*/
      /*d = MATRIX_X x b */
      e = 0;
      b = invert_byte(b);
      for(i = 0; i < BYTESIZE; i++){
        d_aux = matrix_x[i] & b;
        odd = 0;
        for(j = 0; j < BYTESIZE; j++){    /*Count number of 1s*/
            if((BASE_CHAR & d_aux) == BASE_CHAR)
              odd++;
            d_aux = d_aux << 1;
        }
        if(odd%2 == 0)
          d[i] = 0;
        else d[i] = 1;

        /*e is the bits of d in a single variable*/
        e = e << 1;
        e = e + d[i];
      }
      e = invert_byte(e);

      /*Put the numbers in hex form in the output file*/
      fprintf(F_OUT, "%x ", e^vect_c);
      if((c + 1) % AES_N == 0)
        fprintf(F_OUT, "\n");
    }
  }
  else{
    vect_c = (int)strtol(INV_VECTOR_C, NULL, 16);
    for(i = 0; i < BYTESIZE; i++){
      matrix_x[i] = (int)strtol(INV_MATRIX_X[i], NULL, 16);
    }
    /*For each entry in the sbox*/
    for(s = 0; s <= MAX_BYTE; s++){

      e = invert_byte(s);

      b = 0;
      for(i = 0; i < BYTESIZE; i++)
        b1[i] = 0;

      for(i = 0; i < BYTESIZE; i++){
        b_aux = matrix_x[i] & e;
        odd = 0;
        for(j = 0; j < BYTESIZE; j++){    /*Count number of 1s*/
            if((BASE_CHAR & b_aux) == BASE_CHAR)
              odd++;
            b_aux = b_aux << 1;
        }
        if(odd%2 == 0)
          b1[i] = 0;
        else b1[i] = 1;

        b = b << 1;
        b = b + b1[i];
      }

      b = invert_byte(b);
      b = b^vect_c;

      euclides_ext_aes(m_x, b, &mcd, &c); /*Only intrested in b (b = inv(c) mod (mx))*/

      /*Put the numbers in hex form in the output file*/
      fprintf(F_OUT, "%x ", c);
      if((s + 1) % AES_N == 0)
        fprintf(F_OUT, "\n");
    }
  }





  if(F_OUT != stdout)
    fclose(F_OUT);
  return OK;

}
