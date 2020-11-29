CC=gcc
CFLAGS=-g -Wall -pedantic
EXS= potencia

all: $(EXS)

funciones.o: funciones.c funciones.h
	$(CC) $(CFLAGS) -c funciones.c

# e2a
potencia: p3_ej2a.o
	$(CC) $(CFLAGS) -o potencia p3_ej2a.o funciones.o

p3_ej2a.o: p3_ej2a.c funciones.o
	$(CC) $(CFLAGS) -c p3_ej2a.c



clean:
	rm -rf *.o $(EXS) 
