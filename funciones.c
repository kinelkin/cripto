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

void cifrarAfin(mpz_t a, mpz_t b, mpz_t m, char* filein, char* fileout){
  mpz_t a1,total,resultado;
  int i, mcd;
  FILE* entrada;
  FILE* salida;
  char* textoCifrado=NULL, *textoPlano=NULL;
  char x;

  entrada = fopen(filein, "r");
  if (entrada==NULL){
    printf("Error al abrir el fichero de lectura");
    return;
  }

  salida = fopen(fileout,"w");
  if (salida==NULL){
    fclose(entrada);
    printf("Error al abrir el fichero de salida");
    return;
  }

  textoPlano = (char*)malloc(sizeof(char)*10000);
  fscanf(entrada,"%s", textoPlano);
  textoCifrado = (char*)malloc(sizeof(char)*(strlen(textoPlano)+1));

  if(textoCifrado == NULL){
    printf("Error reservando memoria para la cadena");
    fclose(salida);
    fclose(entrada);
    return;
  }

  mpz_init(a1);
  mpz_init(resultado);
  mpz_init(total);

  euclidean(resultado,a,m);
  mcd = mpz_get_ui(resultado);

  if(mcd!=1){
    printf("No existe inverso multiplicativo de a");
    free(textoPlano);
    free(textoCifrado);
    fclose(salida);
    fclose(entrada);
    return;
  }


  for (i=0; i<strlen(textoPlano); i++){
    x = textoPlano[i];
    mpz_mul_ui(a1,a,x);
    mpz_add(a1,a1,b);
    mpz_mod(total,a1,m);
    mpz_add_ui(total,total,65);
    textoCifrado[i] = mpz_get_ui(total);
    fprintf(salida,"%c", textoCifrado[i]);
  }

  mpz_clear(a1);
  mpz_clear(resultado);
  mpz_clear(total);
  free(textoCifrado);
  free(textoPlano);
  fclose(salida);
  fclose(entrada);

  return;

}

void descifrarAfin(mpz_t a, mpz_t b, mpz_t m, char* filein, char* fileout){
  mpz_t inverso,b1,mul,total;
  int i,sumando,modulo,negativo;
  char x;
  FILE* entrada;
  FILE* salida;
  char* textoDescifrado=NULL;

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

  textoDescifrado = (char*)malloc(sizeof(char)*10000);
  fscanf(entrada,"%s",textoDescifrado);

  mpz_init(inverso);
  mpz_init(b1);
  mpz_init(mul);
  mpz_init(total);
  mpz_invert(inverso,a,m);

  modulo = mpz_get_ui(m);
  for (i=0; i<strlen(textoDescifrado); i++){
    x = textoDescifrado[i]-65;
    mpz_ui_sub(b1,x,b);
    negativo = mpz_get_ui(b1);
    while(negativo<0){
      mpz_add(b1,b1,m);
      negativo += modulo;
    }
    mpz_mul(mul,inverso,b1);
    mpz_mod(total,mul,m);
    sumando = mpz_get_ui(total);
    while(sumando<65){
      sumando += modulo;
    }
    textoDescifrado[i] = sumando;
    fprintf(salida,"%c", textoDescifrado[i]);
  }

  mpz_clear(inverso);
  mpz_clear(b1);
  mpz_clear(mul);
  mpz_clear(total);
  free(textoDescifrado);
  fclose(salida);
  fclose(entrada);

}
