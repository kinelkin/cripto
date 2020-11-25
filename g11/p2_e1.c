/******************************************************************************
*******************************************************************************
File:   p2_e1.c
Desc:   prints the Pp(x) and Pp(x|y) of text and its cypher
*******************************************************************************
*******************************************************************************/
#include "funciones.h"

#define EXP_ARGS 6


int main(int argc, char *argv[]){
  int mode;
  int arg = 1;
  char *fname_in = NULL, *fname_out = NULL, *fname_cap = NULL, *fname_c = NULL/*, *cipher = NULL*/;
  char *original, *cypher, *key/*, *extra*/;
  long len;
  FILE *F_IN = NULL, *F_OUT = NULL, *F_C = NULL;

  if(argc != EXP_ARGS){
    printf("\nProgram with incorrect args\n");
    printf("\nExpected: seg-perf {-%c|-%c} [-i file_in ] [-o file_out ]\n", MODE_EQ, MODE_NOT_EQ);
    return ERR;
  }
  else{
    /************************ MODE ************************/
    if( argv[arg][1] != MODE_EQ && argv[arg][1] != MODE_NOT_EQ ){
      printf("\nExpected {-%c|-%c} but recieved %s\n",MODE_EQ, MODE_NOT_EQ, argv[arg]);
      return ERR;
    }
    else mode = argv[arg++][1];     /*arg= 1*/

  /************************ input/output files ************************/
      /*TWO FILES*/
  if( argv[arg][1] != 'i' ){      /*arg=2 */
    printf("\nExpected -i but recieved %s\n", argv[arg]);
    return ERR;
  }
  else fname_in = argv[++arg];              /*arg= 3*/

  if( argv[++arg][1] != 'o' ){      /*arg=4 */
    printf("\nExpected -o but recieved %s\n", argv[arg]);
    return ERR;
  }
    else fname_out = argv[++arg];              /*arg=5 */
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

  /*Saving the cypher file*/
  fname_c = (char *)malloc(sizeof(char)*strlen(fname_in)+5);
  strcpy(fname_c, "c_");
  strcat(fname_c, fname_in);
  F_C = fopen(fname_c, "w");
  free(fname_c);

  /*First we convert the text to capital letters*/
  fname_cap = capitalize(F_IN, fname_in);
  fclose(F_IN);
  F_IN = fopen(fname_cap, "r");
  free(fname_cap);

  /*Transfer text to a static variable*/
  original = file_to_var(F_IN, FALSE, &len);

  /*Generate key according to mode*/
  key = gen_key(len, mode);

  /*Generate cypher from key*/
  cypher = cypher_desp(original, key, len);

  analyse_prob(F_OUT, original, len);

  analyse_prob_cond(F_OUT, original, cypher, len);

  // extra = decypher_desp(cypher, key, len);
  for(long i=0; i<len; i++)
    fprintf(F_C, "%c", cypher[i]);

  fclose(F_C);


  free(original);
  free(key);
  free(cypher);
  // free(extra);

  if(F_IN != stdin)
    fclose(F_IN);
  if(F_OUT != stdout)
    fclose(F_OUT);
  return OK;

}
