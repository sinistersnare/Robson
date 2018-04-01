all:
	@echo "nothing here..."

inversion:
	gcc -g link_inversion.c -o inv.x

robson:
	gcc -g robstack.c robson.c bintree.c -o rob.x

thread:
	gcc -g threaded.c -o thread.x
