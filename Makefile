CC=gcc
CFLAGS=-std=c89 -pedantic -Wall -Wextra -g

all: link_inversion robson threaded

clean:
	rm -f link_inversion.x robson.x threaded.x

link_inversion:
	$(CC) $(CFLAGS) src/link_inversion_runner.c src/link_inversion.c -o link_inversion.x

robson:
	$(CC) $(CFLAGS) src/robson_runner.c src/robson.c -o robson.x

threaded:
	$(CC) $(CFLAGS) src/threaded_runner.c src/threaded.c -o threaded.x
