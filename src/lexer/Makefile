ROOT = ../..
LIBDIR = $(ROOT)/lib

all: lexer.out

lexer.out:	lexer.c lexer.h
	gcc lexer.c -g -I. -I$(LIBDIR) -L$(LIBDIR) -lbtree -o lexer.out

test: lexer.out
	./lexer.out lexer.in

clean:
	rm -rf *.out *.o *.a *.class *.beam *.dSYM
