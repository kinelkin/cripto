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
#include "funciones.h"

#define MIN_ARGS 8






int main(int argc, char *argv[]){
  int mode, num;
  int arg = 1, i;
  char *fname_in = NULL, *fname_out = NULL, *fname_cap = NULL/*, *cipher = NULL*/;
  FILE *F_IN = NULL, *F_OUT = NULL;
  int k1[MAX_PERM], k2[MAX_PERM], m, n;

  if(argc < MIN_ARGS){
    printf("\nProgram with incorrect args\n");
    printf("\nExpected: name {-C|-D} {-k1 K1 -k2 K2}[-i file_in ] [-o file_out ]"
            "with K1 and K2 [ 3 5 6 7 0 1 4 ]\n");
    return ERR;
  }
  else{
    /************************ MODE ************************/
    if( argv[arg][1] != 'C' && argv[arg][1] != 'D' ){
      printf("\nExpected {-C|-D} but recieved %s\n", argv[arg]);
      return ERR;
    }
    else mode = argv[arg++][1];     /*arg= 1*/

/************************ -k1 ************************/
    if( strcmp(argv[arg], "-k1") != 0){    /*arg= 2*/
      printf("\nExpected -k1 [] but recieved %s\n", argv[arg]);
      return ERR;
    }
    if(argv[++arg][0] != '['){    /*arg= 3*/
      printf("\nExpected [ but recieved %s\n", argv[arg]);
      return ERR;
    }

    arg++;
    m = 0;
    while(argv[arg][0] != ']' && m < MAX_PERM){
      num = atoi(argv[arg++]);
      if(get_pos(k1, m, num) != ERR){
        printf("\nNumbers in vector K1 cannot be repeated\n");
        return ERR;
      }
      k1[m++] = num;
    }

    arg++;
/*arg = 4 + n */
/************************ -k1 ************************/
    if( strcmp(argv[arg], "-k2") != 0){    /*arg= 2*/
      printf("\nExpected -k2 [] but recieved %s\n", argv[arg]);
      return ERR;
    }
    if(argv[++arg][0] != '['){    /*arg=3 */
      printf("\nExpected [ but recieved %s\n", argv[arg]);
      return ERR;
    }

    argv++;
    n = 0;
    while(argv[arg][0] != ']' && n < MAX_PERM){
      num = atoi(argv[arg++]);
      if(get_pos(k2, n, num) != ERR){
        printf("\nNumbers in vector K2 cannot be repeated\n");
        return ERR;
      }
      k2[n++] = num;
    }


  /************************ input/output files ************************/
      /*TWO FILES*/
      if(argc == arg + 6){
        if( argv[++arg][1] != 'i' ){      /*arg=4 */
          printf("\nExpected -i but recieved %s\n", argv[arg]);
          return ERR;
        }
        else fname_in = argv[++arg];              /*arg= 5*/

        if( argv[++arg][1] != 'o' ){      /*arg=7 */
          printf("\nExpected -o but recieved %s\n", argv[arg]);
          return ERR;
        }
        else fname_out = argv[++arg];              /*arg=8 */
      }
      /*ONE FILE*/
      else if(argc == arg + 4){
        if( argv[++arg][1] != 'i' ){      /*arg= 4*/
          if( argv[arg][1] == 'o' ){
            fname_out = argv[++arg];           /*arg=4 */
          }
          else{
            printf("\nExpected -i or -o but recieved %s\n", argv[arg]);
            return ERR;
          }
        }
        else fname_in = argv[++arg];              /*arg=5*/
      }
      /*NO FILES*/
      else if (argc != arg + 2){
        printf("\nProgram with incorrect input/output args\n");
        printf("\nExpected: name {-C|-D} {-k1 K1 -k2 K2}[-i file_in ] [-o file_out ]"
                "with K1 and K2 [ 3 5 6 7 0 1 4 ]\n");
      return ERR;
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


  for(i=0; i<m; i++)
    if(k1[i] >= m){
      printf("\nError, value %d >= length K1 %d",k1[i], m);
      return ERR;
    }

  for(i=0; i<n; i++)
    if(k2[i] >= n){
      printf("\nError, value %d >= length K2 %d",k2[i], n);
      return ERR;
    }

  /*YA PODEMOS PROGRAMAR LO Q QUERAMOS*/
  if(F_IN != stdin && mode == 'C'){
    fname_cap = capitalize(F_IN, fname_in);
    fclose(F_IN);
    F_IN = fopen(fname_cap, "r");
    free(fname_cap);
  }
  if(mode == 'C')
    cipher_dp(F_IN, F_OUT, fname_in, m, n, k1, k2);
  else
    decipher_dp(F_IN, F_OUT, m, n, k1, k2);

  if(F_IN != stdin)
    fclose(F_IN);
  if(F_OUT != stdout)
    fclose(F_OUT);
  return OK;

}
