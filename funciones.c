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

void cifrarAfin(mpz_t a, mpz_t b, mpz_t m, char* filein, char* fileout){
  mpz_t a1,total,resultado;
  int i, mcd, contador=0;
  long int longitud;
  FILE* entrada;
  FILE* salida;
  char* textoCifrado=NULL, *textoPlano=NULL;
  char x, c;
  struct stat fileStat;

  entrada = fopen(filein, "r");
  if (entrada==NULL){
    printf("Error al abrir el fichero de lectura");
    return;
  }

  longitud = findSize(filein);

  salida = fopen(fileout,"w");
  if (salida==NULL){
    fclose(entrada);
    printf("Error al abrir el fichero de salida");
    return;
  }

  textoPlano = (char*)malloc(sizeof(char)*longitud);
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
  long int longitud;
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
  longitud = findSize(filein);
  textoDescifrado = (char*)malloc(sizeof(char)*longitud);
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

int comprobarInyectividad(mpz_t a, mpz_t b, mpz_t m, char* filein){
  char comprobacion2[100]="comprobacion2.txt";
  char alfabeto[27]="ABCDEFGHIJKLMNOPQRSTUVWYZ";
  char cifrado[27];
  FILE* entrada;
  FILE* salida;
  int i=0,j;

  entrada = fopen(filein, "w");
  if (entrada==NULL){
    printf("Error al abrir el fichero de lectura");
    return -1;
  }

  fprintf(entrada, "%s", alfabeto);
  fclose(entrada);

  cifrarAfin(a,b,m,filein,comprobacion2);

  salida = fopen(comprobacion2,"r");
  if (salida==NULL){
    printf("Error al abrir el fichero de salida");
    return-1;
  }

  fscanf(salida,"%s",cifrado);


  for(i=0;i<28;i++){
    for(j=0;j<i;j++){
      if(cifrado[i]==cifrado[j]){
        return 0;
      }
    }
  }


  fclose(salida);
  return 1;

}

int main(){
    mpz_t a,b,m;
    char fichero[100]="fichero.txt";
    char cifrado[100]="cifrado.txt";
    char plano[100]="plano.txt";
    char comprobacion1[100]="comprobacion1.txt";
    int inyectiva;



    mpz_init(a);
    mpz_init(b);
    mpz_init(m);

    mpz_set_str (a,"5",10);
    mpz_set_str (b,"18",10);
    mpz_set_str (m,"27",10);


    inyectiva = comprobarInyectividad(a,b,m,comprobacion1);

    if(inyectiva!=1){
      printf("NO ES INYECTIVA");
      mpz_clear(a);
      mpz_clear(b);
      mpz_clear(m);
      return -1;
    }

    cifrarAfin(a,b,m,fichero,cifrado);
    descifrarAfin(a,b,m,cifrado,plano);



    return 0;
}
