CC=gcc
CFLAGS=-Wall -g -std=c89 -pedantic

all: inversion robson thread

clean:
	@rm inv.x rob.x thread.x

inversion:
	$(CC) $(CFLAGS) link_inversion.c -o inv.x

robson:
	$(CC) $(CFLAGS) rob.c -o rob.x

thread:
	$(CC) $(CFLAGS) threaded.c -o thread.x
