/******************************************************************************
*******************************************************************************
File:   vigenere.c
Desc:   ensures that the correct parameters are inputed into the program
        calls the vigenere methods for coding and decoding
*******************************************************************************
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

#define MIN_ARGS 4
#define MAX_ARGS 8



int main(int argc, char *argv[]){
  int mode;
  int arg = 1;
  char *fname_in = NULL, *fname_out = NULL, *fname_cap;
  char *k = NULL;
  FILE *F_IN = NULL, *F_OUT = NULL;


  if(argc < MIN_ARGS || argc > MAX_ARGS){
    printf("\nProgram with incorrect args\n");
    printf("\nExpected: name {-C|-D} {-k clave}[-i file_in ] [-o file_out ]\n");
    return ERR;
  }
  else{
    /************************ MODE ************************/
    if( argv[arg][1] != 'C' && argv[arg][1] != 'D' ){
      printf("\nExpected {-C|-D} but recieved %s\n", argv[arg]);
      return ERR;
    }
    else mode = argv[arg++][1];     /*arg = 1*/

/************************ -k ************************/
    if( argv[arg][1] != 'k' ){    /*arg = 2*/
      printf("\nExpected -k but recieved %s\n", argv[arg]);
      return ERR;
    }
    else k = argv[++arg];    /*arg = 3*/
    if (strlen(k) > MAX_KEY){
      printf("\nMAX Key Length is %d\n", MAX_KEY);
      return ERR;
    }

  /************************ input/output files ************************/
    switch(argc){
      /*BOTH FILES*/
      case (MAX_ARGS):
        if( argv[++arg][1] != 'i' ){      /*arg = 4*/
          printf("\nExpected -i but recieved %s\n", argv[arg]);
          return ERR;
        }
        else fname_in = argv[++arg];              /*arg = 5*/

        if( argv[++arg][1] != 'o' ){      /*arg = 6*/
          printf("\nExpected -o but recieved %s\n", argv[arg]);
          return ERR;
        }
        else fname_out = argv[++arg];              /*arg = 7*/
        break;
      /*ONE FILE*/
      case (MAX_ARGS - 2):
        if( argv[++arg][1] != 'i' ){      /*arg = 4*/
          if( argv[arg][1] == 'o' ){
            fname_out = argv[++arg];           /*arg = 5*/
          }
          else{
            printf("\nExpected -i or -o but recieved %s\n", argv[arg]);
            return ERR;
          }
        }
        else fname_in = argv[++arg];              /*arg = 5*/
        break;
      /*NO FILES*/
      case (MIN_ARGS):
        break;

      default:
          printf("\nProgram with incorrect input/output args\n");
          printf("\nExpected: name {-C|-D} {-k clave}[-i file_in ] [-o file_out ]\n");
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

  /*YA PODEMOS PROGRAMAR LO Q QUERAMOS*/
  if(F_IN != stdin && mode == 'C'){
    fname_cap = capitalize(F_IN, fname_in);
    fclose(F_IN);
    F_IN = fopen(fname_cap, "r");
    free(fname_cap);
  }
  vigenere(mode, k, F_IN, F_OUT);
  if(F_IN != stdin)
    fclose(F_IN);
  if(F_OUT != stdout)
    fclose(F_OUT);

  return OK;

}
