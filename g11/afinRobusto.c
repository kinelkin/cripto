#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include <ctype.h>
#include "funciones.h"

#define MIN_ARGS 8
#define MAX_ARGS 12
#define ERR -1
#define OK 1



int main(int argc, char *argv[]){
  int mode, Zm, Na, Nb;
  int arg = 1;
  char *fIn = NULL, *fOut = NULL;


  if(argc < MIN_ARGS || argc > MAX_ARGS){
    printf("\nProgram with incorrect args\n");
    printf("\nExpected: name {-C|-D} {-m |Z m |} {-a N × } {-b N + } [-i f ile in ] [-o f ile out ]\n");
    return ERR;
  }
  else{
    /************************ MODE ************************/
    if( argv[arg][1] != 'C' && argv[arg][1] != 'D' ){
      printf("\nExpected {-C|-D} but recieved %s\n", argv[arg]);
      return ERR;
    }
    else mode = argv[arg++][1];     //arg = 1

/************************ -m ************************/
    if( argv[arg][1] != 'm' ){    //arg = 2
      printf("\nExpected -m but recieved %s\n", argv[arg]);
      return ERR;
    }
    else Zm = atoi(argv[++arg]);    //arg = 3

/************************ -a ************************/
    if( argv[++arg][1] != 'a' ){    //arg = 4
      printf("\nExpected -a but recieved %s\n", argv[arg]);
      return ERR;
    }
    else Na = atoi(argv[++arg]);    //arg = 5

/************************ -b ************************/
    if( argv[++arg][1] != 'b' ){    //arg = 6
      printf("\nExpected -b but recieved %s\n", argv[arg]);
      return ERR;
    }

    else Nb = atoi(argv[++arg]);    //arg = 7

  /************************ input/output files ************************/
    switch(argc){
      /*BOTH FILES*/
      case (MAX_ARGS):
        if( argv[++arg][1] != 'i' ){      //arg = 8
          printf("\nExpected -i but recieved %s\n", argv[arg]);
          return ERR;
        }
        else fIn = argv[++arg];              //arg = 9

        if( argv[++arg][1] != 'o' ){      //arg = 10
          printf("\nExpected -o but recieved %s\n", argv[arg]);
          return ERR;
        }
        else fOut = argv[++arg];              //arg = 11
        break;
      /*ONE FILE*/
      case (MAX_ARGS - 2):
        if( argv[++arg][1] != 'i' ){      //arg = 8
          if( argv[arg][1] == 'o' ){
            fOut = argv[++arg];           //arg = 9
          }
          else{
            printf("\nExpected -i or -o but recieved %s\n", argv[arg]);
            return ERR;
          }
        }
        else fIn = argv[++arg];              //arg = 9
        break;
      /*NO FILES*/
      case (MIN_ARGS):
        break;

      default:
          printf("\nProgram with incorrect input/output args\n");
          printf("\nExpected: name {-C|-D} {-m |Z m |} {-a N × } {-b N + } [-i f ile in ] [-o f ile out ]\n");
          return ERR;
          break;
    }
  }
  printf("Le sugerimos que escriba un modulo alto para aumentar la robustez de su cifrado\n");
  if(mode=='C'){
    cifrarAfinRobusto(Zm,Na,Nb,fIn,fOut);
  }else if(mode=='D'){
    descifrarAfinRobusto(Zm,Na,Nb,fIn,fOut);
  }

}
