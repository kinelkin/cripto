#include "funciones.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char *read_from_file(const char *filename){
    long int size = 0;
    FILE *file = fopen(filename, "r");

    if(!file) {
        fputs("File error.\n", stderr);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);

    char *result = (char *) malloc(size);
    if(!result) {
        fputs("Memory error.\n", stderr);
        fclose(file);
        return NULL;
    }

    if(fread(result, 1, size, file) != size) {
        fputs("Read error.\n", stderr);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return result;
}

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

  euclidean(resultado,a,m);
  mcd = mpz_get_ui(resultado);

  if(mcd!=1){
    printf("No existe inverso multiplicativo de a");
    free(textoCifrado);
    fclose(f);
    return;
  }


  for (i=0; i<strlen(mensaje); i++){
    x = mensaje[i];
    printf("%c %d\n", mensaje[i], mensaje[i]);
    mpz_mul_ui(a1,a,x);
    gmp_printf("%Zd\n", a1);
    mpz_add(a1,a1,b);
    gmp_printf("%Zd\n", a1);
    mpz_mod(total,a1,m);
    gmp_printf("%Zd\n", total);
    mpz_add_ui(total,total,65);
    gmp_printf("%Zd\n", total);
    textoCifrado[i] = mpz_get_ui(total);
    fprintf(f,"%c", textoCifrado[i]);
  }

  mpz_clear(a1);
  mpz_clear(resultado);
  mpz_clear(total);
  fclose(f);

  return;

}

void descifrarAfin(mpz_t a, mpz_t b, mpz_t m, char* ciphertext){
  mpz_t inverso,b1,mul,total;
  int i,sumando,modulo,negativo;
  FILE* plano;
  FILE* cipher;
  char x;
  char* cadena=NULL;

  cipher = fopen(ciphertext, "r");
  if(cipher==NULL){
    printf("Error abriendo cypher");
    return;
  }

  plano = fopen("plano.txt","w");
  if (plano==NULL){
    printf("Error al abrir el fichero");
    fclose(cipher);
    return;
  }

  cadena = read_from_file(ciphertext);

  mpz_init(inverso);
  mpz_init(b1);
  mpz_init(mul);
  mpz_init(total);
  mpz_invert(inverso,a,m);

  modulo = mpz_get_ui(m);
  for (i=0; i<strlen(cadena); i++){
    x = cadena[i]-65;
    printf("%c %d \n", cadena[i],cadena[i]);
    mpz_ui_sub(b1,x,b);

    negativo = mpz_get_ui(b1);
    while(negativo<0){
      mpz_add(b1,b1,m);
      negativo += modulo;
    }
    mpz_mul(mul,inverso,b1);
    gmp_printf("%Zd\n", mul);
    mpz_mod(total,mul,m);
    gmp_printf("%Zd\n", total);
    sumando = mpz_get_ui(total);
    while(sumando<65){
      sumando += modulo;
    }
    cadena[i] = sumando;
    fprintf(plano,"%c", cadena[i]);
  }

  mpz_clear(inverso);
  mpz_clear(b1);
  mpz_clear(mul);
  mpz_clear(total);
  fclose(plano);
  fclose(cipher);

}

int main(){
    mpz_t a,b,m;
    char ciphertext[100] = "cifrado.txt";
    char mensaje[100] = "hola";

    mpz_init(a);
    mpz_init(b);
    mpz_init(m);

    mpz_set_str (a,"5",10);
    mpz_set_str (b,"15",10);
    mpz_set_str (m,"27",10);

    descifrarAfin(a,b,m,ciphertext);
    /*cifrarAfin(a,b,m,mensaje,filename);*/

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(m);
    return 0;
}
