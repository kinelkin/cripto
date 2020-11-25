#Variables
APP=desCBC
APP2=tripleDES

CFLAGS=-std=c99 -Wall -Wextra -g -O2
CPPFLAGS=-I -DDEBUG
LDFLAGS=-lm


.PHONY: all clean help generaClave generaClaveTRIPLE


all: $(APP) $(APP2)

$(APP2): DES.o p2_e2b.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(APP): DES.o p2_e2a.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

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

clean:
	@rm -f *.o $(APP) generaClave

help :
	@echo -e "Usage :"
	@echo -e "  make all
	@echo -e "  make generaClave
	@echo -e "  make generaClaveTRIPLE				
	@echo -e "  make clean		
	@echo -e "  make help		
