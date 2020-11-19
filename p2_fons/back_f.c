#include "funciones.h"

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************Apartado 1*****************************************
*******************************************************************************
*******************************************************************************/
char *gen_key(long len, int mode){
  char *key;
  long i;
  time_t t;

  key = (char *)malloc(len * sizeof(char) + 1);
  if(key == NULL)
    return NULL;

  /*Initialise random seed*/
  srand((unsigned) time(&t));

  if(mode == MODE_EQ)
    for(i=0; i<len; i++)
      key[i] = rand()%(ALFABET_LEN) + 'A';
  else
    for(i=0; i<len; i++)
      key[i] = (rand()%(ALFABET_LEN+ADDITION))%ALFABET_LEN + 'A';

  return key;
}

char *cypher_desp(char *orig, char *key, long len){
  long i;
  char c, *cypher;

  cypher = (char *)malloc(len * sizeof(char) + 1);
  if(cypher == NULL)
    return NULL;

  for(i=0; i<len; i++){
    c = orig[i];
    if(c >= 'A' && c <= 'Z')
      cypher[i] = (key[i] + c - 2*'A')% ALFABET_LEN + 'A';
    else
      cypher[i] = c;
    }

  return cypher;
}

char *decypher_desp(char *cypher, char *key, long len){
  long i;
  char c, *orig;

  orig = (char *)malloc(len * sizeof(char) + 1);
  if(orig == NULL)
    return NULL;

  for(i=0; i<len; i++){
    c = cypher[i];
    if(c >= 'A' && c <= 'Z')
      orig[i] = (c - key[i] + ALFABET_LEN)% ALFABET_LEN + 'A';
    else
      orig[i] = c;
    }

  return orig;
}

void analyse_prob(FILE *F_OUT, char *original, long len){
  long i;
  int j, freqs[ALFABET_LEN] = {0};
  char c;

  for(i=0; i<len; i++){
    c = original[i];
    if(c >= 'A' && c <= 'Z')
      freqs[c - 'A']++;
  }

  for(j=0; j<ALFABET_LEN; j++)
    fprintf(F_OUT, "Pp(%c) = %lf\n", 'A' + j, ((double)freqs[j])/len);
}

double *freq_cmp(char *original, char *cypher, long len, char c){
  long i, cont;
  double *freqs;

  freqs = (double *)calloc(ALFABET_LEN, sizeof(double));
  cont = 0;
  for(i=0; i<len; i++)
    if(cypher[i] == c){
      freqs[original[i] - 'A']++;
      cont++;
    }
  if(cont != 0)
    for(i=0; i<ALFABET_LEN; i++)
      freqs[i] = freqs[i]/cont;

  return freqs;
}

void analyse_prob_cond(FILE *F_OUT, char *original, char *cypher, long len){
  int i, j;
  double **all_freqs;

  all_freqs = (double **)malloc(ALFABET_LEN * sizeof(double *));
  for(i=0; i<ALFABET_LEN; i++){
    all_freqs[i] = freq_cmp(original, cypher, len, 'A'+i);
  }

  for(i=0; i<ALFABET_LEN; i++){
    for(j=0; j<ALFABET_LEN; j++){
      fprintf(F_OUT, "Pp(%c|%c) = %lf ",'A' + i, 'A' + j, all_freqs[j][i]);
    }
    fprintf(F_OUT, "\n");
  }
  for(i=0; i<ALFABET_LEN; i++)
    free(all_freqs[i]);
  free(all_freqs);
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************Apartado 4*****************************************
*******************************************************************************
*******************************************************************************/
unsigned char get_col(unsigned char a){
  unsigned char aux;
  aux = a >> SHIFT;
  return aux;
}

unsigned char get_row(unsigned char a){
  unsigned char aux;
  aux = a << SHIFT;
  aux = aux >> SHIFT;
  return aux;
}


int align_shift(unsigned char r0, unsigned char r1){
  int pos_r0, pos_r1, shift;
  unsigned char aux;
  if(r0 < r1)
    return -1;
  aux = BASE_INT;
  pos_r0 = sizeof(r0)*BITS_IN_BYTE - 1;
  pos_r1 = sizeof(r1)*BITS_IN_BYTE - 1;
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
  int shift, cont, extra;
  unsigned char q, t;
  cont = 0;

  if(n < d){
    *res = 0;
    *rem = n;
    return;
  }
  extra = 0;
  while((n&BASE_INT) != BASE_INT){
    n = n << 1;
    d = d << 1;
    extra++;
  }
  shift = align_shift(n,d);


  d = d << shift;
  q = 0;
  while(cont <= shift && n > 0){
    if( (n&BASE_INT) == BASE_INT){
      t = n^d;
      n = t;
      q = q << 1;
      q++;
    }
    else
      q = q << 1;

    n = n << 1;
    cont++;
  }
  q = q << (shift - cont + 1);
  n = n >> (extra + shift + 1);

  *res = q;
  *rem = n;
}










/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************GENERIC********************************************
*******************************************************************************
*******************************************************************************/
char *capitalize(FILE *F_IN, char *fname){
  char *cap_fname, c;
  FILE *F_CAP;
  cap_fname = (char *)malloc(sizeof(char)*strlen(fname)+5);
  strcpy(cap_fname, "cap_");
  strcat(cap_fname, fname);
  F_CAP = fopen(cap_fname, "w");

  while(EOF != (c = fgetc(F_IN)))
    fputc(toupper(c),F_CAP);

  fclose(F_CAP);
  return cap_fname;
}

char *file_to_var(FILE *F_IN, int punct, long *len){
  char *var = NULL, *no_punct = NULL, c;
  long file_len, extra_chars, i, j;

  /*Get length of file*/
  fseek(F_IN, 0, SEEK_END);
  file_len = ftell(F_IN);
  rewind(F_IN);

  var = (char *)malloc(file_len * sizeof(char) + 1);
  if(var == NULL)
    return NULL;
  i=0;
  extra_chars = 0;
  while(EOF != (c = fgetc(F_IN))){
    var[i] = c;
    if(c < 'A' || c > 'Z')
      extra_chars++;
    i++;
    }
    *len = file_len;

  if(punct == 0){
    no_punct = (char *)calloc((file_len - extra_chars)+1,  sizeof(char));
    j=0;
    for(i=0; i<file_len; i++){
      if(var[i] >= 'A' && var[i] <= 'Z'){
        no_punct[j++] = var[i];
      }
    }
    free(var);
    *len = j;
    return no_punct;
  }
  else
    return var;
}
