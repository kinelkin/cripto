/******************************************************************************
*******************************************************************************
File:   break_vigenere.c
Desc:   finds the keylength of the encrypted text and then through frequency
        analysis proceeds to decrypt the text.
*******************************************************************************
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "funciones_alt.h"

#define MIN_ARGS 1
#define MAX_ARGS 3


int main(int argc, char *argv[]){
  int arg = 0, keylen_k, keylen_ic, keylen;
  char *fname_in = NULL, *fname_out = NULL, *fname_cap = NULL;
  FILE *F_IN = NULL, *F_OUT = NULL;


  if(argc < MIN_ARGS || argc > MAX_ARGS){
    printf("\nProgram with incorrect args\n");
    printf("\nExpected: name [-i file_in ]\n");
    return ERR;
  }
  else{
  /************************ input/output files ************************/
    switch(argc){
      /*ONE FILE*/
      case (MAX_ARGS):
        if( argv[++arg][1] != 'i' ){      /*arg= 5*/
            printf("\nExpected -i but recieved %s\n", argv[arg]);
            return ERR;
          }
        else fname_in = argv[++arg];              /*arg= 3*/
        break;
      /*NO FILES*/
      case (MIN_ARGS):
        break;

      default:
          printf("\nProgram with incorrect input/output args\n");
          printf("\nExpected: name [-i file_in ] [-o file_out ]\n");
          return ERR;
          break;
    }
  }
  if(fname_in){
    F_IN = fopen(fname_in, "r");
    if(F_IN == NULL){
      printf("\n%s failed to open, setting F_IN to stdin\n", fname_in);
      F_IN = stdin;
    }
  }
  else{
    F_IN = stdin;
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

  if(F_IN != stdin){
    fname_cap = capitalize(F_IN, fname_in);
    fclose(F_IN);
    F_IN = fopen(fname_cap, "r");
    free(fname_cap);
  }

  /*YA PODEMOS PROGRAMAR LO Q QUERAMOS*/
  keylen_ic = find_key_len_ic(F_IN);
  keylen_k = find_key_len_kasiski(F_IN);
  printf("\nKASISKI: %d\nIC: %d",keylen_k, keylen_ic);
  if(keylen_k != keylen_ic){
    printf("\nDifferent Key Sizes detected");
    if(keylen_k%keylen_ic == 0)
      keylen = keylen_k;
    else if(keylen_ic%keylen_k == 0)
      keylen = keylen_ic;
    else{
      printf("\nERROR NO KEY DETERMINED");
      if(F_IN != stdin)
        fclose(F_IN);
      if(F_OUT != stdout)
        fclose(F_OUT);
      return ERR;
    }

  }
  else keylen = keylen_ic;

  printf("\nKEYLEN == %d", keylen);
  printf("\nPWD: %s\n", break_vigenere(F_IN, keylen));

  if(F_IN != stdin)
    fclose(F_IN);
  if(F_OUT != stdout)
    fclose(F_OUT);

  return OK;

}
