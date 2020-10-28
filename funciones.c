#include "funciones.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <gmp.h>

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************EUCLIDES********************************************
*******************************************************************************
*******************************************************************************/
void euclidean(mpz_t resultado, mpz_t a, mpz_t b){
  mpz_t modulo;
  mpz_init(modulo);

  if(mpz_sgn(a)==0){
    mpz_set(resultado,b);
    mpz_clear(modulo);
    return;
  }
  mpz_mod(modulo,b,a);
  euclidean(resultado,modulo,a);
  mpz_clear(modulo);
}

void euclideanExtended(mpz_t resultado, mpz_t a, mpz_t b){

  mpz_t x,y,d;
  mpz_t x2,x1,y2,y1,q,r,mul;
  mpz_init(x);
  mpz_init(y);
  mpz_init(d);

  mpz_init(x2);
  mpz_init(x1);
  mpz_init(y2);
  mpz_init(y1);
  mpz_init(q);
  mpz_init(r);
  mpz_init(mul);


  while(mpz_sgn(b)){
    mpz_divexact(q,a,b);
    mpz_mod(r,a,b);
    mpz_mul(mul,q,x1);
    mpz_sub(x,x2,mul);
    mpz_mul(mul,q,y1);
    mpz_sub(y,y2,mul);
    mpz_set(a,b);
    mpz_set(b,r);
    mpz_set(x2,x1);
    mpz_set(y2,y1);
    mpz_set(y1,y);
    mpz_set(d,a);
  }

  mpz_set(x,x2);
  mpz_set(y,y2);
  mpz_set(resultado,d);

  mpz_clear(x);
  mpz_clear(y);
  mpz_clear(d);
  mpz_clear(x2);
  mpz_clear(x1);
  mpz_clear(y2);
  mpz_clear(y1);
  mpz_clear(q);
  mpz_clear(r);
  mpz_clear(mul);

}
/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************AFIN********************************************
*******************************************************************************
*******************************************************************************/
long int findSize(const char* file_name){
    struct stat st;

    if(stat(file_name,&st)==0)
        return (st.st_size);
    else
        return -1;
}

int comprobarInyectividad(mpz_t a, mpz_t b, mpz_t m){
  char alfabeto[25]="ABCDEFGHIJKLMNOPQRSTUVWYZ";
  char cifrado[25], c;
  mpz_t a1,total;
  FILE* entrada;
  FILE* salida;
  int i,j;

  salida = fopen("comprobacion_inyectiva.txt","w");
  if (salida==NULL){
    printf("Error al abrir el fichero de salida");
    return-1;
  }

  mpz_init(a1);
  mpz_init(total);

  for (i=0; i<25; i++){
    c = alfabeto[i];
    mpz_mul_ui(a1,a,c);
    mpz_add(a1,a1,b);
    mpz_mod(total,a1,m);
    mpz_add_ui(total,total,65);
    cifrado[i] = mpz_get_ui(total);
    fprintf(salida,"%c", cifrado[i]);
  }
  fclose(salida);

  salida = fopen("comprobacion_inyectiva.txt","r");
    if (salida==NULL){
      printf("Error al abrir el fichero de salida");
      return-1;
    }
  fscanf(salida,"%s",cifrado);


  for(i=0;i<25;i++){
    for(j=0;j<i;j++){
      if(cifrado[i]==cifrado[j]){
        printf("%c %c \n", cifrado[i], cifrado[j]);
        return 0;
      }
    }
  }

  mpz_clear(a1);
  mpz_clear(total);
  fclose(salida);
  return 1;

}

void cifrarAfin(int m, int a, int b, char* filein, char* fileout){
  mpz_t m1,a1,b1,a_aux,total,resultado;
  int i, mcd, inyectiva;
  long int longitud;
  FILE* entrada;
  FILE* salida;
  char* textoCifrado=NULL, *textoPlano=NULL;
  char x, c;
  struct stat fileStat;

  mpz_init(a1);
  mpz_init(m1);
  mpz_init(b1);
  mpz_set_ui(a1,a);
  mpz_set_ui(b1,b);
  mpz_set_ui(m1,m);
  inyectiva = comprobarInyectividad(a1,b1,m1);

  if(inyectiva!=1){
    printf("NO ES INYECTIVA");
    mpz_clear(a1);
    mpz_clear(b1);
    mpz_clear(m1);
    return;
  }

  entrada = fopen(filein, "r");
  if (entrada==NULL){
    printf("Error al abrir el fichero de lectura");
    mpz_clear(a1);
    mpz_clear(b1);
    mpz_clear(m1);
    return;
  }

  longitud = findSize(filein);

  salida = fopen(fileout,"w");
  if (salida==NULL){
    fclose(entrada);
    mpz_clear(a1);
    mpz_clear(b1);
    mpz_clear(m1);
    printf("Error al abrir el fichero de salida");
    return;
  }

  textoPlano = (char*)malloc(sizeof(char)*longitud);
  fscanf(entrada,"%s", textoPlano);
  textoCifrado = (char*)malloc(sizeof(char)*(strlen(textoPlano)+1));

  if(textoCifrado == NULL){
    printf("Error reservando memoria para la cadena");
    mpz_clear(a1);
    mpz_clear(b1);
    mpz_clear(m1);
    fclose(salida);
    fclose(entrada);
    return;
  }

  mpz_init(a_aux);
  mpz_init(resultado);
  mpz_init(total);

  euclidean(resultado,a1,m1);
  mcd = mpz_get_ui(resultado);

  if(mcd!=1){
    printf("No existe inverso multiplicativo de a");
    mpz_clear(a1);
    mpz_clear(b1);
    mpz_clear(m1);
    free(textoPlano);
    free(textoCifrado);
    fclose(salida);
    fclose(entrada);
    return;
  }


  for (i=0; i<strlen(textoPlano); i++){
    x = textoPlano[i];
    mpz_mul_ui(a_aux,a1,x);
    mpz_add(a_aux,a_aux,b1);
    mpz_mod(total,a_aux,m1);
    mpz_add_ui(total,total,65);
    textoCifrado[i] = mpz_get_ui(total);
    fprintf(salida,"%c", textoCifrado[i]);
  }

  mpz_clear(a_aux);
  mpz_clear(resultado);
  mpz_clear(total);
  mpz_clear(a1);
  mpz_clear(b1);
  mpz_clear(m1);
  free(textoCifrado);
  free(textoPlano);
  fclose(salida);
  fclose(entrada);

  return;

}

void descifrarAfin(int m, int a, int b, char* filein, char* fileout){
  mpz_t m1,a1,b1,inverso,b_aux,mul,total;
  int i,sumando,modulo,negativo;
  long int longitud;
  char x;
  FILE* entrada;
  FILE* salida;
  char* textoDescifrado;

  entrada = fopen(filein, "r");
  if(entrada==NULL){
    printf("Error abriendo el fichero a descifrar");
    return;
  }

  salida = fopen(fileout,"w");
  if (salida==NULL){
    printf("Error al abrir el fichero de salida para el descifrado");
    fclose(entrada);
    return;
  }

  longitud = findSize(filein);
  textoDescifrado = (char*)malloc(sizeof(char)*longitud);
  if (textoDescifrado==NULL){
    printf("Error reservando memoria para la cadena de descifrado");
    fclose(entrada);
    fclose(salida);
    return;
  }

  fscanf(entrada,"%s",textoDescifrado);

  mpz_init(a1);
  mpz_init(m1);
  mpz_init(b1);
  mpz_set_ui(a1,a);
  mpz_set_ui(b1,b);
  mpz_set_ui(m1,m);
  mpz_init(inverso);
  mpz_init(b_aux);
  mpz_init(mul);
  mpz_init(total);
  mpz_invert(inverso,a1,m1);


  for (i=0; i<strlen(textoDescifrado); i++){
    x = textoDescifrado[i]-65;
    mpz_ui_sub(b_aux,x,b1);
    negativo = mpz_get_ui(b_aux);
    while(negativo<0){
      mpz_add(b_aux,b_aux,m1);
      negativo += modulo;
    }
    mpz_mul(mul,inverso,b_aux);
    mpz_mod(total,mul,m1);
    sumando = mpz_get_ui(total);
    while(sumando<65){
      sumando += m;
    }
    textoDescifrado[i] = sumando;
    fprintf(salida,"%c", textoDescifrado[i]);
  }

  mpz_clear(inverso);
  mpz_clear(b1);
  mpz_clear(mul);
  mpz_clear(total);
  mpz_clear(a1);
  mpz_clear(b1);
  mpz_clear(m1);
  free(textoDescifrado);
  fclose(salida);
  fclose(entrada);

}

void cifrarAfinRobusto(int m, int a, int b, char* filein, char* fileout){
  mpz_t m1,a1,b1,a_aux,total,resultado;
  int i, mcd;
  long int longitud;
  FILE* entrada;
  FILE* salida;
  char* textoCifrado=NULL, *textoPlano=NULL;
  char x, c;
  struct stat fileStat;

  mpz_init(a1);
  mpz_init(m1);
  mpz_init(b1);
  mpz_set_ui(a1,a);
  mpz_set_ui(b1,b);
  mpz_set_ui(m1,m);

  entrada = fopen(filein, "r");
  if (entrada==NULL){
    printf("Error al abrir el fichero de lectura");
    mpz_clear(a1);
    mpz_clear(b1);
    mpz_clear(m1);
    return;
  }

  longitud = findSize(filein);

  salida = fopen(fileout,"w");
  if (salida==NULL){
    fclose(entrada);
    mpz_clear(a1);
    mpz_clear(b1);
    mpz_clear(m1);
    printf("Error al abrir el fichero de salida");
    return;
  }

  textoPlano = (char*)malloc(sizeof(char)*longitud);
  fscanf(entrada,"%s", textoPlano);
  textoCifrado = (char*)malloc(sizeof(char)*(strlen(textoPlano)+1));

  if(textoCifrado == NULL){
    printf("Error reservando memoria para la cadena");
    mpz_clear(a1);
    mpz_clear(b1);
    mpz_clear(m1);
    fclose(salida);
    fclose(entrada);
    return;
  }

  mpz_init(a_aux);
  mpz_init(resultado);
  mpz_init(total);

  euclidean(resultado,a1,m1);
  mcd = mpz_get_ui(resultado);

  if(mcd!=1){
    printf("No existe inverso multiplicativo de a");
    mpz_clear(a1);
    mpz_clear(b1);
    mpz_clear(m1);
    free(textoPlano);
    free(textoCifrado);
    fclose(salida);
    fclose(entrada);
    return;
  }


  for (i=0; i<strlen(textoPlano); i++){
    x = textoPlano[i];
    mpz_mul_ui(a_aux,a1,x);
    mpz_add(a_aux,a_aux,b1);
    mpz_mod(total,a_aux,m1);
    mpz_add_ui(total,total,32);
    textoCifrado[i] = mpz_get_ui(total);
    fprintf(salida,"%c", textoCifrado[i]);
  }

  mpz_clear(a_aux);
  mpz_clear(resultado);
  mpz_clear(total);
  mpz_clear(a1);
  mpz_clear(b1);
  mpz_clear(m1);
  free(textoCifrado);
  free(textoPlano);
  fclose(salida);
  fclose(entrada);

  return;

}

void descifrarAfinRobusto(int m, int a, int b, char* filein, char* fileout){
  mpz_t m1,a1,b1,inverso,b_aux,mul,total;
  int i,sumando,modulo,negativo;
  long int longitud;
  char x;
  FILE* entrada;
  FILE* salida;
  char* textoDescifrado;

  entrada = fopen(filein, "r");
  if(entrada==NULL){
    printf("Error abriendo el fichero a descifrar");
    return;
  }

  salida = fopen(fileout,"w");
  if (salida==NULL){
    printf("Error al abrir el fichero de salida para el descifrado");
    fclose(entrada);
    return;
  }

  longitud = findSize(filein);
  textoDescifrado = (char*)malloc(sizeof(char)*longitud);
  if (textoDescifrado==NULL){
    printf("Error reservando memoria para la cadena de descifrado");
    fclose(entrada);
    fclose(salida);
    return;
  }

  fscanf(entrada,"%s",textoDescifrado);

  mpz_init(a1);
  mpz_init(m1);
  mpz_init(b1);
  mpz_set_ui(a1,a);
  mpz_set_ui(b1,b);
  mpz_set_ui(m1,m);
  mpz_init(inverso);
  mpz_init(b_aux);
  mpz_init(mul);
  mpz_init(total);
  mpz_invert(inverso,a1,m1);


  for (i=0; i<strlen(textoDescifrado); i++){
    x = textoDescifrado[i]-32;
    mpz_ui_sub(b_aux,x,b1);
    negativo = mpz_get_ui(b_aux);
    while(negativo<0){
      mpz_add(b_aux,b_aux,m1);
      negativo += modulo;
    }
    mpz_mul(mul,inverso,b_aux);
    mpz_mod(total,mul,m1);
    sumando = mpz_get_ui(total);
    while(sumando<32){
      sumando += m;
    }
    textoDescifrado[i] = sumando;
    fprintf(salida,"%c", textoDescifrado[i]);
  }

  mpz_clear(inverso);
  mpz_clear(b1);
  mpz_clear(mul);
  mpz_clear(total);
  mpz_clear(a1);
  mpz_clear(b1);
  mpz_clear(m1);
  free(textoDescifrado);
  fclose(salida);
  fclose(entrada);

}
/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************FLUJO********************************************
*******************************************************************************
*******************************************************************************/
void swap(unsigned char *x, unsigned char *y){
	char aux;
  aux=*x;
	*x=*y;
	*y=aux;
}

int cifradoFlujo(void){
	unsigned char s[N];
	int i, cifrado_i, cifrado_j;

	for(i=0 ; i<N; i++){
		s[i] = i;
  }
  /*Reseteamos el valor*/
	cifrado_i=0;
  cifrado_j=0;

	return 1;
}

int generateKey(unsigned char *key, int longitud){
	unsigned char s[N];
	int cifrado_i, cifrado_j;

	for(cifrado_i=0; cifrado_i<N; cifrado_i++){
		cifrado_j = (cifrado_j + s[cifrado_i] + key[cifrado_i % longitud])% N;
		swap(&s[cifrado_i], &s[cifrado_j]);
	}

	cifrado_i = 0;
  cifrado_j = 0;
}

char permutacion(void){
	unsigned char s[N];
	int cifrado_i, cifrado_j;
	cifrado_i = (cifrado_i +1 ) % N;
	cifrado_j = (cifrado_j + s[cifrado_i]) % N;
	swap(&s[cifrado_i], &s[cifrado_j]);

	return s[(s[cifrado_i] + s[cifrado_j]) % N];
}


/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************GENERAL********************************************
*******************************************************************************
*******************************************************************************/

int get_pos(int *array, int len, int num){
  int i;
  for(i=0; i<len; i++)
    if(array[i] == num)
      return i;

  return ERR;
}

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


long mcd(long a, long b){
  long i, mcd;
  mcd = 1;
  for(i=2; i <= a && i <= b; i++)
    if(a%i==0 && b%i==0)
      mcd = i;

  return mcd;

}


int most_probable_mcd(int *mcd_list, int total){
  int i,j, max, candidate, factor;
  candidate = 1;
  max = 0;
  factor = 0;
  for(i=3; i<MAX_KEY; i++){
    for(j=0; j<total; j++){
      if(mcd_list[j]%i == 0)
        factor++;
    }
    if(factor >= max){
      candidate = i;
      max = factor;
    }
    factor = 0;
  }
  return candidate;
}

int check_word(char all_words[MAX_WORDS][MAX_REP_LEN+1], char word[MAX_REP_LEN], int num_w, int len_word){
  int i, j;
  if(num_w < 1)
    return FALSE;
  for(i=0; i<num_w; i++){
    if(all_words[i][0] == len_word)
      for(j=0; j<len_word; j++){
        if(all_words[i][j+1] != word[j]){
          break;
        }
        return TRUE;
      }
  }
  return FALSE;
}

double absol(double a){
  if(a<0)
    return -a;

  return a;
}

double avg(double *list, int len){
  int i;
  double sum;
  sum=0;
  for(i = 0; i<len; i++)
    sum += list[i];
  return sum/len;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************VIGENERE********************************************
*******************************************************************************
*******************************************************************************/
void vigenere(int mode, char *k, FILE *F_IN, FILE *F_OUT){
  int key_len, total_letters, i;
  char c;
  total_letters = 'Z' - 'A' + 1;
  key_len = strlen(k);
  if (mode == 'C'){
    i = 0;
    while(EOF != (c = fgetc(F_IN)))
      if(c >= 'A' && c <= 'Z')
        fprintf(F_OUT, "%c", (k[i++%key_len] + c - 2*'A') % total_letters + 'A');
      else
        fprintf(F_OUT, "%c", c);
      }
  else{
    i = 0;
    while(EOF != (c = fgetc(F_IN)))
        if(c >= 'A' && c <= 'Z')
          fprintf(F_OUT, "%c", (c - k[i++%key_len] + total_letters) % total_letters + 'A');
        else
          fprintf(F_OUT, "%c", c);
  }
}

/****************************KASISKI*******************************************/
int all_instances(FILE *F_analysis, int len_word, long i_0, long i_1, char *string, long len_str){
  int flag;
  long j, max, k, mcd_n, mcd_temp;

  max = len_str - len_word;
  mcd_n = i_1 - i_0;
  for(j=i_1+len_word; j<max; j++){
    if(string[i_0] == string[j]){
      for(k=1; k<len_word && k<len_word; k++){
        flag = 0;
        if(string[i_0+k] != string[j+k]){
          flag = 1;
          break;
        }
      }
      if(flag == 0){
        fprintf(F_analysis, "\t%ld\t%ld\t%ld\n", i_0, j, j-i_0);
        mcd_temp = mcd(mcd_n, j-i_0);
        if(mcd_temp != 1 && mcd_temp != 2)
          mcd_n = mcd_temp;
        j+=len_word;
      }
    }
  }
  return mcd_n;
}

int find_key_len_kasiski(FILE *F_IN){
  char *cipher = NULL;
  char word[MAX_REP_LEN];
  char all_words[MAX_WORDS][MAX_REP_LEN+1];
  int all_mcds[MAX_MCDS] = {0};
  FILE *F_analysis;
  int r,rep_len, flag, len_word, n, y, b, key_len;
  long cipher_len, i, j;

  /*Allocate memory and copy file to char* */
  cipher = file_to_var(F_IN, NO_PUNCT, &cipher_len);
  if(cipher == NULL)
    return ERR;

  F_analysis = fopen(K_ANALYSIS,"w");
  flag = 0;
  y = 0;
  rep_len = 0;
  for(len_word=MIN_REP_LEN; len_word<MAX_REP_LEN && y < MAX_WORDS; len_word++){
    printf("\nKEYLEN == %d", len_word);
    for(i=0; i<cipher_len && y < MAX_WORDS; i++){
      for(j=i+1; j<cipher_len; j++){
        if(cipher[i] == cipher[j]){       /*We can start looking for reps*/
          rep_len = 1;
          word[0] = cipher[i];
          while(cipher[i+rep_len] == cipher[j+rep_len] && rep_len < len_word){   /*Get length of rep*/
            word[rep_len] = cipher[i+rep_len];
            rep_len++;
          }
          if(rep_len == len_word && check_word(all_words, word, y, len_word) == FALSE){
            for(r=0; r<len_word; r++)
              fputc(word[r], F_analysis);
            n = all_instances(F_analysis, len_word, i, j, cipher, cipher_len);
            /*printf("\nN===%d", n);*/
            all_mcds[y] = n;
            all_words[y][0] = len_word;
            for(b=0; b<len_word; b++)
              all_words[y][b+1] = word[b];
            y++;
            flag = 1;
          }
        }
        if(flag){
          flag = 0;
          break;
        }
      }
    }
  }
  print_mcds(all_mcds, y);
  key_len = most_probable_mcd(all_mcds, y);
  printf("\nMost Probable KEYLEN: %d\n", key_len);
  fclose(F_analysis);
  free(cipher);

  return key_len;
}


/****************************COINCIDENCE INDEX*********************************/
double ic_sum(double *alfabet, int len){
  int i;
  double sum;
  sum = 0;
  for(i=0; i< len; i++)
    sum += alfabet[i]*alfabet[i];

  return sum;
}

double calculate_ic(char *t1, long len_str, int m){
  long i, max;
  int j,k,letter;
  double ic_col[m];
  double alfabet[ALFABET_LEN];


  for(j=1; j<=m; j++){
    for(k=0; k<ALFABET_LEN;k++)
      alfabet[k]=0.0;
    max = len_str - j;
    for(i=0; i<max; i+=m){
      letter = t1[i+j-1] - 'A';
      alfabet[letter] += 1;
    }
    for(i=0; i<ALFABET_LEN; i++){
      alfabet[i] = (alfabet[i]*m)/max;
    }
    /*print_ab(alfabet);*/

    ic_col[j-1] = ic_sum(alfabet, ALFABET_LEN);
  }
  for(j=0; j<m; j++){
    printf("\nCOL %d --> ic = %lf", j, ic_col[j]);
  }

  return avg(ic_col, m);
}

int find_key_len_ic(FILE *F_IN){
    char *cipher = NULL;
    int i, candidate, extra_len;
    long cipher_len;
    double ic_m;
    double min, tmp;
    int extras[MAX_KEY] = {0};

    /*Transfer the input file to a variable and strip all punctuation*/
    cipher = file_to_var(F_IN, NO_PUNCT, &cipher_len);
    if(cipher == NULL)
      return ERR;

    candidate = 0;
    min = 1.0;
    candidate = 0;
    extra_len = 0;
    for(i = 1; i<=MAX_KEY; i++){
      printf("\nM === %d", i);
      ic_m = calculate_ic(cipher, cipher_len, i) - ENGLIS_IC;
      printf("\nAVG == %lf\n",ic_m+ENGLIS_IC);
      if((tmp = absol(ic_m)) < min){
        if(tmp < TOO_SMALL && absol(min - tmp) < TOO_SMALL){
            if(extra_len == 0)
              extras[extra_len++] = candidate;
            extras[extra_len++] = i;
        }
        min = tmp;
        candidate = i;
      }
    }
    if(extra_len > 0){
      candidate = most_probable_mcd(extras, extra_len);
      printf("\nWarning: many probable lengths --> choosing MCD");
      print_list(extras, extra_len);
    }

    printf("\nCandidate is %d", candidate);
    free(cipher);

    return candidate;

}


char *break_vigenere(FILE *F_IN, int keylen){
  int i,j,k,l, letter, m_letter;
  char *cipher = NULL;
  static char pwd[MAX_KEY];
  long cipher_len, max, alfabet[ALFABET_LEN];
  int dist = 'E' - 'A';

  cipher = file_to_var(F_IN, NO_PUNCT, &cipher_len);

  pwd[keylen] = '\0';
  for(i=1; i<=keylen; i++){
    for(k=0; k<ALFABET_LEN; k++)
      alfabet[k]=0;
    max = cipher_len - i;
    /*Get all freqs from column i*/
    for(j=0; j<max; j+=keylen){
      letter = cipher[j+i-1] - 'A';
      alfabet[letter] += 1;
    }
    /*USING THAT E is the most used letter*/
    max = 0;
    for(l=0; l<ALFABET_LEN; l++){
      if(alfabet[l] > max){
        m_letter = l;
        max = alfabet[l];
      }
    }

    pwd[i-1] = (m_letter - dist + ALFABET_LEN) % ALFABET_LEN + 'A';
  }
  free(cipher);
  return pwd;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
****************************DOUBLE PERMUTATION*********************************
*******************************************************************************
*******************************************************************************/

char *pad_txt(char *txt, int bloc, long *len, int mode){
  int i;
  long extra;
  char *padded;

  extra = (bloc - *len%bloc)%bloc;
  *len = *len+extra;
  padded = (char *)calloc((*len)+1,  sizeof(char));
  strcpy(padded, txt);

  for(i=0; i<extra; i++)
    padded[*len - extra + i] = PAD_LETTER;
  padded[*len] = '\0';
  return padded;
}

void perm_rows(char **txt, long len, int m, int n, int *k1){
  char *text, tmp_row[n];
  int bloc_size, len_done, row_read, row_write;
  int i, j, start, try, tmp_row_num, aux, tmp_flag;
  int done[m];

  text = *txt;
  bloc_size = m*n;
  for(i=0; i<len; i+=bloc_size){
    len_done = 0;
    tmp_row_num = k1[0];
    tmp_flag = 0;
    while(len_done < m){
      try = 0;
      while(get_pos(done, len_done, tmp_row_num) != ERR){
        tmp_row_num = k1[try++];  /*Find another tmp_row_num*/
        tmp_flag = 0;
      }

      row_write = get_pos(k1, m, tmp_row_num);
      row_read = tmp_row_num;
      if(row_write != row_read){
        /*Copy to tmp_row and write new row*/
        start = row_write*n;
        if(tmp_flag == 0){  /*NO text in tmp*/
          for(j=0; j<n; j++){
            tmp_row[j] = text[i + start + j];
            text[i + start + j] = text[i + row_read*n + j];
          }
          tmp_flag = 1;
        }
        else{
          for(j=0; j<n; j++){
            aux = tmp_row[j];
            tmp_row[j] = text[i + start + j];
            text[i + start + j] = aux;
          }
        }
      }
      tmp_row_num = row_write;
      done[len_done++] = row_read;
    }
  }
}

void perm_cols(char **txt, long len, int m, int n, int *k2){
  char *text, tmp_col[m];
  int bloc_size, len_done, col_read, col_write;
  int i, j, try, tmp_col_num, aux, tmp_flag;
  int done[n];

  text = *txt;
  bloc_size = m*n;
  for(i=0; i<len; i+=bloc_size){
    len_done = 0;
    tmp_col_num = k2[0];
    tmp_flag = 0;
    while(len_done < n){
      try = 0;
      while(get_pos(done, len_done, tmp_col_num) != ERR){
        tmp_col_num = k2[try++];  /*Find another tmp_col_num*/
        tmp_flag = 0;
      }

      col_write = get_pos(k2, n, tmp_col_num);
      col_read = tmp_col_num;
      if(col_write != col_read){
        /*Copy to tmp_col and write new col*/
        if(tmp_flag == 0){  /*NO text in tmp*/
          for(j=0; j<m; j++){
            tmp_col[j] = text[i + col_write + j*n];
            text[i + col_write + j*n] = text[i + col_read + j*n];
          }
          tmp_flag = 1;
        }
        else{
          for(j=0; j<m; j++){
            aux = tmp_col[j];
            tmp_col[j] = text[i + col_write + j*n];
            text[i + col_write + j*n] = aux;
          }

        }
      }
      tmp_col_num = col_write;
      done[len_done++] = col_read;
    }
  }
}

void cipher_dp(FILE *F_IN, FILE *F_OUT, char *fname, int m, int n, int *k1, int *k2){
  long len;
  char *txt, *padded, *cap_fname;
  FILE *F_CAP;
  txt = file_to_var(F_IN, NO_PUNCT, &len);
  padded = pad_txt(txt, m*n, &len, NO_PUNCT);
  cap_fname = (char *)malloc(sizeof(char)*strlen(fname)+5);
  strcpy(cap_fname, "cap_");
  strcat(cap_fname, fname);
  F_CAP = fopen(cap_fname, "w");
  free(cap_fname);
  fprintf(F_CAP,"%s", padded);
  free(txt);

  perm_rows(&padded, len, m, n, k1);
  perm_cols(&padded, len, m, n, k2);

  fprintf(F_OUT,"%s",padded);
  fclose(F_CAP);
  free(padded);

}

void invert_perm(int **perm, int len){
  int i, aux[len];
  int *v;
  v = *perm;
  for(i=0; i<len; i++){
    aux[i] = get_pos(v, len, i);
  }
  for(i=0; i<len; i++)
    v[i] = aux[i];

}

void decipher_dp(FILE *F_IN, FILE *F_OUT, int m, int n, int *k1, int *k2){
  long len;
  char *padded;
  padded = file_to_var(F_IN, NO_PUNCT, &len);

  invert_perm(&k1, m);
  invert_perm(&k2, n);
  perm_cols(&padded, len, m, n, k2);

  perm_rows(&padded, len, m, n, k1);

  fprintf(F_OUT,"%s",padded);
  free(padded);

}





void print_all_words(char all_words[static MAX_WORDS][MAX_REP_LEN+1], int num_w){
  int len_word, i, j;
  printf("\nAll words: \n[");
  for(i=0; i<num_w; i++){
    len_word = all_words[i][0];
    for(j=0; j<len_word;j++){
      printf("%c", all_words[i][j+1]);
      if(j== len_word-1 && i != num_w - 1)
        printf(", ");
    }
  }
  printf("]\n");
}

void print_list(int *list, int len){
  int i;
  if(len <= 0)
    return;
  printf("\n[");
  for(i=0; i<len; i++){
    if(i != len-1)
      printf("%d, ", list[i]);
    else printf("%d]\n", list[i]);
  }
}

void print_mcds(int all_mcds[MAX_MCDS], int y){
  int i;
  printf("\n[");
  for(i=0; i<y; i++)
    printf(" %d ", all_mcds[i]);
  printf("]\n");
}

void print_ab(double alfabet[ALFABET_LEN]){
  int i;
  printf("\n[");
  for(i = 0; i< ALFABET_LEN; i++){
    if(i != ALFABET_LEN - 1)
      printf("%lf, ", alfabet[i]);
    else printf("%lf]", alfabet[i]);
  }
  printf("\n");

}
