CC=gcc
CFLAGS=-g -Wall -ansi
EXS= v d p

all: $(EXS)

v: vigenere.o
	$(CC) $(CFLAGS) -o v vigenere.o funciones.o

vigenere.o: vigenere.c funciones.o
	$(CC) $(CFLAGS) -c vigenere.c

p: permutation.o
	$(CC) $(CFLAGS) -o p permutation.o funciones.o

permutation.o: permutation.c funciones.o
	$(CC) $(CFLAGS) -c permutation.c

d: decypher.o
	$(CC) $(CFLAGS) -o d decypher.o funciones.o

decypher.o: decypher.c funciones.o
	$(CC) $(CFLAGS) -c decypher.c

funciones.o: funciones.c funciones.h
	$(CC) $(CFLAGS) -c funciones.c


clean:
	rm -rf *.o $(EXS) c_* k_* r_* cap_*
