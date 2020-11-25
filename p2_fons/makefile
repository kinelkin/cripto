CC=gcc
CFLAGS=-g -Wall -pedantic
EXS= seg-perf des_lin aes_lin aes_box

all: $(EXS)

funciones.o: funciones.c funciones.h
	$(CC) $(CFLAGS) -c funciones.c

seg-perf: p2_e1.o
	$(CC) $(CFLAGS) -o seg-perf p2_e1.o funciones.o

p2_e1.o: p2_e1.c funciones.o
	$(CC) $(CFLAGS) -c p2_e1.c

des_lin: p2_e3a.o
	$(CC) $(CFLAGS) -o des_lin p2_e3a.o funciones.o

p2_e3a.o: p2_e3a.c funciones.o
	$(CC) $(CFLAGS) -c p2_e3a.c

aes_lin: p2_e4a.o
	$(CC) $(CFLAGS) -o aes_lin p2_e4a.o funciones.o

p2_e4a.o: p2_e4a.c funciones.o
	$(CC) $(CFLAGS) -c p2_e4a.c

aes_box: p2_e4b.o
	$(CC) $(CFLAGS) -o aes_box p2_e4b.o funciones.o

p2_e4b.o: p2_e4b.c funciones.o
	$(CC) $(CFLAGS) -c p2_e4b.c


clean:
	rm -rf *.o $(EXS) c_* stats* k_* r_* cap_* aes*.txt
