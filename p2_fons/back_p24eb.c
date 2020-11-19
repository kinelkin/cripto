/******************************************************************************
*******************************************************************************
File:   p2_e4a.c
Desc:   prints the Pp(x) and Pp(x|y) of text and its cypher
*******************************************************************************
*******************************************************************************/
#include "funciones.h"

#define EXP_ARGS 4



int main(int argc, char *argv[]){
  int mode;
  int arg = 1;
  char *fname_in = NULL, *fname_out = NULL, *fname_cap = NULL, *fname_c = NULL/*, *cipher = NULL*/;
  char *original, *cypher, *key/*, *extra*/;
  long len;
  FILE *F_IN = NULL, *F_OUT = NULL, *F_C = NULL;
  unsigned char res, rem, r0, r1;
  char a[3] = "9c", b[3]="03";

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

  r0 = (int)strtol(a, NULL, 16);
  r1 = (int)strtol(b, NULL, 16);
  printf("\nc = %x or %d, d = %x or %d\n", r0,r0,r1,r1);

  bin_div(r0, r1, &res, &rem);
  printf("\nRES == %x or %d\nrem == %x or %d\n", res,res,rem, rem);







  if(F_OUT != stdout)
    fclose(F_OUT);
  return OK;

}
