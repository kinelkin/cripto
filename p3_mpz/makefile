CC=gcc
CFLAGS=-g -Wall -pedantic
EXS= potencia miller primo primo_b primo_rsa

all: $(EXS)

funciones.o: funciones.c funciones.h
	$(CC) $(CFLAGS) -c funciones.c

# e2a
potencia: p3_ej2a.o
	$(CC) $(CFLAGS) -o potencia p3_ej2a.o funciones.o -lgmp

p3_ej2a.o: p3_ej2a.c funciones.o
	$(CC) $(CFLAGS) -c p3_ej2a.c

# e2b (TEST)
miller: miller_test.o
	$(CC) $(CFLAGS) -o miller miller_test.o funciones.o -lgmp

miller_test.o: miller_test.c funciones.o
	$(CC) $(CFLAGS) -c miller_test.c

# e2b
primo: p3_ej2b.o
	$(CC) $(CFLAGS) -o primo p3_ej2b.o funciones.o -lgmp

p3_ej2b.o: p3_ej2b.c funciones.o
	$(CC) $(CFLAGS) -c p3_ej2b.c

# e2b_b
primo_b: p3_ej2b_b.o
	$(CC) $(CFLAGS) -o primo_b p3_ej2b_b.o funciones.o -lgmp

p3_ej2b_b.o: p3_ej2b_b.c funciones.o
	$(CC) $(CFLAGS) -c p3_ej2b_b.c

# e2c
primo_rsa: p3_ej2c.o
	$(CC) $(CFLAGS) -o primo_rsa p3_ej2c.o funciones.o -lgmp

p3_ej2c.o: p3_ej2c.c funciones.o
	$(CC) $(CFLAGS) -c p3_ej2c.c

clean:
	rm -rf *.o $(EXS)
