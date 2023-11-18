CC=gcc
CFLAGS=-I.
DEPS =
OBJ = rendezvous.o signalling.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: rendezvous signalling mutex

rendezvous: rendezvous.o
	$(CC) -o rendezvous rendezvous.o -lpthread

signalling: signalling.o
	$(CC) -o signalling signalling.o -lpthread

mutex: mutex.o
	$(CC) -o mutex mutex.o -lpthread

.PHONY: clean

clean:
	rm -f *.o rendezvous signalling mutex
