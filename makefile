CC=gcc
CFLAGS=-g 
EXS= v d p a ar stream_cipher

all: $(EXS)

funciones.o: funciones.c funciones.h
	$(CC) $(CFLAGS) $(GMPLIB) -c funciones.c

a: afin.o
	$(CC) $(CFLAGS) -o a afin.o funciones.o -lgmp

afin.o: afin.c funciones.o
	$(CC) $(CFLAGS) -c afin.c

ar: afinRobusto.o
	$(CC) $(CFLAGS) -o ar afinRobusto.o funciones.o -lgmp

afinRobusto.o: afinRobusto.c funciones.o
	$(CC) $(CFLAGS) -c afinRobusto.c

stream_cipher: stream_cipher.o
	$(CC) $(CFLAGS) -o stream_cipher stream_cipher.o funciones.o -lgmp

stream_cipher.o: stream_cipher.c funciones.o
	$(CC) $(CFLAGS) -c stream_cipher.c

v: vigenere.o
	$(CC) $(CFLAGS) -o v vigenere.o funciones.o -lgmp

vigenere.o: vigenere.c funciones.o
	$(CC) $(CFLAGS) -c vigenere.c

p: permutation.o
	$(CC) $(CFLAGS) -o p permutation.o funciones.o -lgmp

permutation.o: permutation.c funciones.o
	$(CC) $(CFLAGS) -c permutation.c

d: decypher.o
	$(CC) $(CFLAGS) -o d decypher.o funciones.o -lgmp

decypher.o: decypher.c funciones.o
	$(CC) $(CFLAGS) -c decypher.c





clean:
	rm -rf *.o $(EXS) c_* k_* r_* cap_*
