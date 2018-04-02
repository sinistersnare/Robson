CC=gcc
CFLAGS=-std=c89 -pedantic -Wall -O3

all: inversion robson thread

clean:
	rm -f link_inversion.x robson.x threaded.x

inversion:
	$(CC) $(CFLAGS) link_inversion.c -o link_inversion.x

robson:
	$(CC) $(CFLAGS) rob.c -o robson.x

threaded:
	$(CC) $(CFLAGS) threaded.c -o threaded.x
