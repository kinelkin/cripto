APP=desCBC
APP2=tripleDES

CC = gcc
CFLAGS=-std=c99 -Wall -Wextra -g -O2 -pedantic
CPPFLAGS=-I -DDEBUG
LDFLAGS=-lm
EXS= seg-perf des_lin aes_lin aes_box

.PHONY: all clean help generaClave generaClaveTRIPLE

all: $(APP) $(APP2) $(EXS)

$(APP): DES.o p2_e2a.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(APP2): DES.o p2_e2b.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

funciones.o: funciones.c funciones.h
    $(CC) $(CFLAGS) -c funciones.c

seg-perf: p2_e1.o
    $(CC) $(CFLAGS) -o seg-perf p2_e1.o funciones.o

p2_e1.o: p2_e1.c funciones.o
    $(CC) $(CFLAGS) -c p2_e1.c

p2_e2a.o: p2_e2a.c DES.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

p2_e2b.o: p2_e2b.c DES.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

generaClave: generaClave.o DES.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

generaClave.o: generaClave.c DES.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

generaClaveTRIPLE: generaClaveTRIPLE.o DES.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

generaClaveTRIPLE.o: generaClaveTRIPLE.c DES.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

DES.o: DES.c DES.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

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
    $(CC) $(CFLAGS) -c p2e4b.c

clean:
	@rm -f *.o $(APP) $(EXS) c* stats* k* r* cap_* aes*.txt generaClave

help :
	@echo -e "Usage :"
	@echo -e "  make all
	@echo -e "  make generaClave
	@echo -e "  make generaClaveTRIPLE				
	@echo -e "  make clean		
	@echo -e "  make help		
