all:
	gcc -c funciones.c
	gcc -o funciones funciones.c -lgmp -L.
	gcc -c main.c