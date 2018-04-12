CC=gcc
CFLAGS=-std=c89 -pedantic -Wall -Wextra -O3 -g

all: link_inversion robson threaded tester

clean:
	rm -f link_inversion.x robson.x threaded.x tests.x

link_inversion:
	$(CC) $(CFLAGS) link_inversion_runner.c link_inversion.c -o link_inversion.x

robson:
	$(CC) $(CFLAGS) robson_runner.c robson.c -o robson.x

threaded:
	$(CC) $(CFLAGS) threaded_runner.c threaded.c -o threaded.x
