CFLAGS=-std=c89 -pedantic -Wall -Wextra

all: bin/link_inversion.x bin/robson.x bin/threaded.x

clean:
	rm -f bin/robson.x bin/link_inversion.x bin/threaded.x

bin/link_inversion.x:
	mkdir -p bin
	${CC} $(CFLAGS) src/link_inversion_runner.c src/link_inversion.c -o bin/link_inversion.x

bin/robson.x:
	mkdir -p bin
	${CC} $(CFLAGS) src/robson_runner.c src/robson.c -o bin/robson.x

bin/threaded.x:
	mkdir -p bin
	${CC} $(CFLAGS) src/threaded_runner.c src/threaded.c -o bin/threaded.x

test: clean all
	python3 tests/tests.py
