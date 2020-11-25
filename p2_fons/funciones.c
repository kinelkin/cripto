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
****************************Apartado 3*****************************************
*******************************************************************************
*******************************************************************************/
int get_col_des(int a){
  int aux;
  aux = a << DES_COL_SHIFT;
  aux = aux >> 2;
  return aux;
}

int get_row_des(int a){
  int aux1, aux2;
  aux1 = a >> DES_ROW_SHIFT;
  aux1 = aux1 << 1;
  aux2 = (a << DES_ROW_SHIFT) >> DES_ROW_SHIFT;
  return (aux1^aux2);
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************Apartado 4*****************************************
*******************************************************************************
*******************************************************************************/
int get_col(int a){
  unsigned char aux;
  aux = a >> SHIFT;
  return aux;
}

int get_row(int a){
  unsigned char aux;
  aux = a << SHIFT;
  aux = aux >> SHIFT;
  return aux;
}


int align_shift(int r0, int r1){
  int pos_r0, pos_r1, shift;
  int aux;
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
  // printf("\nAUX == %x or %d", aux, aux);
  while( (aux&r1) == 0 && 0 <= pos_r1){
    pos_r1--;
    aux = aux >> 1;
  }
  shift = (pos_r0 - pos_r1);

  return shift;
}

void bin_div(int n, int d, int *res, int *rem){
  int shift, cont, extra;
  int q, t;
  cont = 0;
  if(n < d){
    *res = 0;
    *rem = n;
    return;
  }
  extra = 0;
  q = 0;
  while((n&BASE_INT) != BASE_INT){
    n = n << 1;
    d = d << 1;
    extra++;
  }
  shift = align_shift(n,d);


  d = d << shift;
  while(cont <= shift && n > 0){
    if( (n&BASE_INT) == BASE_INT){
      t = n^d;
      n = t;
      q = q << 1;
      q++;
    }
    else            /*Shift n and q without dividing*/
      q = q << 1;

    n = n << 1;
    cont++;
  }

  q = q << (shift - cont + 1);
  n = n >> (extra + shift + 1);

  *res = q;
  *rem = n;
}


int euclides_aes(int r0, int r1){
  int q, rem;

  while(rem != 0){
    bin_div(r0, r1, &q, &rem);
    r0 = r1;
    r1 = rem;
  }
  return r0;
}

unsigned char xtime(unsigned char a){
  if((a & AES_80) != AES_80)
    return a << 1;
  else
    return (a << 1)^XTIME_CTE;
}

int aes_mult(int a, int b){
  unsigned char bit, res, i, j, aux;
  bit = 1;
  res = 0;
  aux = 0;
  for(i=0; i<BYTESIZE; i++){
    if( (bit & b) == bit){
      aux = (unsigned char)a;
      for(j = 0; j<i; j++){
        aux = xtime(aux);
      }

      res = res^aux;
      aux = 0;
    }
    bit = bit << 1;
  }
  return res;
}

void euclides_ext_aes(int a, int b, int *mcd, int *inv){
  int r0, r1, t0, t1, q, aux;
  if(b == 0){
    *mcd = a;
    *inv = 0;
    return;
  }

  r0 = a;
  r1 = b;
  t0 = 0;
  t1 = 1;
  // s0 = 1;
  // s1 = 0;
  q = 0;
  while(r1 != 0){
    // printf("\nBEFORE DIV R1 == %x\nR0 = %x\nq = %x\nt0 = %x", r1, r0, q, t0);
    // printf("\nBefore Div: T0 = %x, T1 = %x, q = %x, q*t1 = %x", t0, t1, q, q*t1);
    aux = r1;
    bin_div(r0, r1, &q, &r1);
    // printf("\nAFTER DIV q == %x", q);
    // q = r0/r1;
    // aux = r1;
    // r1 = r0 - q*r1;
    r0 = aux;
    // aux = s1;
    // s1 = s0 - (q*s1);
    // s1 = s0^(q*s1);
    // s0 = aux;
    aux = t1;
    // t1 = t0 - q*t1;
    t1 = t0^(aes_mult(q,t1));
    t0 = aux;
    // printf("\nAfter Div: T0 = %x, T1 = %x, q = %x, q*t1 = %x", t0, t1, q, q*t1);
    // printf("\nAFTER DIV R1 == %x\nR0 = %x\nq = %x\nt0 = %x\n", r1, r0, q, t0);

  }
  /*In case the inv >= 11b we need the inverse mod 11b*/
  if(a <= t0)
    bin_div(t0, a, &aux, &t0);
  *mcd = r0;
  *inv = t0;
  // printf("\nS == %x", s0);
  // bin_div((int)strtol("11b", NULL, 16), s0, &t0, &t1);
  // printf("\nS == %x", t1);
}

unsigned char invert_byte(unsigned char b){
  int i, bit, i_bit;
  unsigned char inv;
  bit = 1;
  i_bit = 128;
  inv = 0;
  for(i = 0; i < BYTESIZE; i++){
    if((bit & b) == bit)
      inv  += i_bit;
    bit = bit << 1;
    i_bit = i_bit >> 1;
  }
  return inv;
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
