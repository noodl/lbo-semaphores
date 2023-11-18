CC=gcc
CFLAGS=-I.
DEPS =
OBJ = rendezvous.o signalling.o mutex.o multiplex.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: rendezvous signalling mutex multiplex

rendezvous: rendezvous.o
	$(CC) -o rendezvous rendezvous.o -lpthread

signalling: signalling.o
	$(CC) -o signalling signalling.o -lpthread

mutex: mutex.o
	$(CC) -o mutex mutex.o -lpthread

multiplex: multiplex.o
	$(CC) -o multiplex multiplex.o -lpthread

.PHONY: clean

clean:
	rm -f *.o rendezvous signalling mutex multiplex
