#Variables
APP=desCBC


CFLAGS=-std=c99 -Wall -Wextra -g -O2
CPPFLAGS=-I -DDEBUG
LDFLAGS=-lm


.PHONY: all clean help genkey


all: $(APP)

$(APP): DES.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.c DES.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

generaClave: generaClave.o DES.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

generaClave.o: generaClave.c DES.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

DES.o: DES.c DES.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	@rm -f *.o $(APP) generaClave

help :
	@echo -e "Usage :"
	@echo -e "  make all		
	@echo -e "  make generaClave	
	@echo -e "  make clean		
	@echo -e "  make help		
