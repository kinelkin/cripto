#include "funciones.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


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
