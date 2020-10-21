#include "funciones.h"

void Euclidean(mpz_t resultado, mpz_t a, mpz_t b){
  mpz_t modulo;
  mpz_init(modulo);

  if(mpz_sgn(a)==0){
    mpz_set(resultado,b);
    mpz_clear(modulo);
    return;
  }
  mpz_mod(modulo,b,a);
  Euclidean(resultado,modulo,a);
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

void cifrarAfin(mpz_t a, mpz_t b, mpz_t m, char* mensaje, char* fichero){
  mpz_t a1,total,resultado;
  int i, mcd;
  FILE* f;
  char* textoCifrado;
  char x;

  f = fopen(fichero,"w");
  if (f==NULL){
    printf("Error al abrir el fichero");
    return;
  }

  textoCifrado = (char*)malloc(sizeof(char)*(strlen(mensaje)+1));

  if(textoCifrado == NULL){
    printf("Error reservando memoria para la cadena");
    fclose(f);
    return;
  }

  mpz_init(a1);
  mpz_init(resultado);
  mpz_init(total);

  Euclidean(resultado,a,m);
  mcd = mpz_get_ui(resultado);

  if(mcd!=1){
    printf("No existe inverso multiplicativo de a");
    free(textoCifrado);
    fclose(f);
    return;
  }

  for (i=0; i<strlen(mensaje); i++){
    x = mensaje[i];
    mpz_mul_ui(a1,a,x);
    mpz_add(a1,a1,b);
    mpz_mod(total,a1,m);
    textoCifrado[i] = mpz_get_ui(total);
    fprintf(f,"%c", textoCifrado[i]);
  }

  mpz_clear(a1);
  mpz_clear(resultado);
  mpz_clear(total);
  fclose(f);

  return;

}

void inversoMultiplicativo(mpz_t resultado, mpz_t a, mpz_t m){
  mpz_t b;
  mpz_init(b);
  
  for()
}

void descifrarAfin(mpz_t a, mpz_t b, mpz_t m, char* mensaje, char* fichero2){
  mpz_t a1,total,resultado;
  int i, mcd;
  FILE* f;
  char* textoPlano;
  char x;

  f = fopen(fichero,"w");
  if (f==NULL){
    printf("Error al abrir el fichero");
    return;
  }

  textoPlano = (char*)malloc(sizeof(char)*(strlen(mensaje)+1));

  if(textoPlano == NULL){
    printf("Error reservando memoria para la cadena");
    fclose(f);
    return;
  }



}


int main(){
    mpz_t a,b,m;
    char filename[100] = "cifrado.txt";
    char filename2[100] = "plano.txt"

    char mensaje[100] = "Probando que funcione el cifrado afín";

    mpz_init(a);
    mpz_init(b);
    mpz_init(m);

    mpz_set_str (a,"4",10);
    mpz_set_str (b,"15",10);
    mpz_set_str (m,"3",10);

    cifrarAfin(a,b,m,mensaje,filename);
    descifrarAfin(a,b,m,mensaje,filename);

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(m);

}
