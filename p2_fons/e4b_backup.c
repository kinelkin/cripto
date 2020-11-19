/******************************************************************************
*******************************************************************************
File:   p2_e4a.c
Desc:   prints the Pp(x) and Pp(x|y) of text and its cypher
*******************************************************************************
*******************************************************************************/
#include "funciones.h"

#define EXP_ARGS 4
/* 1000 0000 = '80' for division */
#define BASE_INT 128
#define BITS_IN_BYTE 8

int align_shift(unsigned char r0, unsigned char r1){
  int pos_r0, pos_r1, shift;
  unsigned char aux;
  aux = BASE_INT;
  printf("\nAUX == %x or %d", aux, aux);
  pos_r0 = sizeof(r0)*BITS_IN_BYTE - 1;
  pos_r1 = sizeof(r1)*BITS_IN_BYTE - 1;
  printf("\nPOSR) = %d\nPOSR1 == %d\n", pos_r0, pos_r1);
  while( (aux&r0) == 0 && 0 <= pos_r0){
    pos_r0--;
    aux = aux >> 1;
  }
  aux = BASE_INT;
  while( (aux&r1) == 0 && 0 <= pos_r1){
    pos_r1--;
    aux = aux >> 1;
  }
  shift = (pos_r0 - pos_r1);

  return shift;
}

void bin_div(unsigned char n, unsigned char d, unsigned char *res, unsigned char *rem){
  int shift, cont;
  unsigned char q, t;
  cont = 0;
  shift = align_shift(n,d);
  printf("\nSHF = %d", shift);
  d = d << shift;
  while(cont < shift && n > 0){
    if( (n&BASE_INT) == BASE_INT){
      t = n^d;
      n = t;
      q = q << 1;
      q++;
    }
    else{
      q = q << 1;
    }
    n = n << 1;
    cont++;
  }
  q = q << (shift - cont);
  *res = q;
  *rem = n >> cont;
}

int main(int argc, char *argv[]){
  int mode;
  int arg = 1;
  char *fname_in = NULL, *fname_out = NULL, *fname_cap = NULL, *fname_c = NULL/*, *cipher = NULL*/;
  char *original, *cypher, *key/*, *extra*/;
  long len;
  FILE *F_IN = NULL, *F_OUT = NULL, *F_C = NULL;
  unsigned char res, rem, r0, r1;
  char a[3] = "c9", b[3]="06";

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

  printf("\na = %s, b = %s", a,b);
  r0 = (int)strtol(a, NULL, 16);
  r1 = (int)strtol(b, NULL, 16);
  printf("\nc = %x or %d, d = %x or %d", r0,r0,r1,r1);

  bin_div(r0, r1, &res, &rem);
  printf("\nRES == %x\nrem == %x\n", res, rem);







  if(F_OUT != stdout)
    fclose(F_OUT);
  return OK;

}
