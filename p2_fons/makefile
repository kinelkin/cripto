CC=gcc
CFLAGS=-g -Wall -pedantic
EXS= seg-perf

all: $(EXS)

funciones.o: funciones.c funciones.h
	$(CC) $(CFLAGS) -c funciones.c

seg-perf: p2_e1.o
	$(CC) $(CFLAGS) -o seg-perf p2_e1.o funciones.o

p2_e1.o: p2_e1.c funciones.o
	$(CC) $(CFLAGS) -c p2_e1.c

clean:
	rm -rf *.o $(EXS) c_* stats* k_* r_* cap_*
