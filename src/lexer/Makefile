ROOT = ../..
LIBDIR = $(ROOT)/lib

all: lexer.out

lexer.out:	lexer.c lexer.h
	gcc lexer.c -I. -I$(LIBDIR) -L$(LIBDIR) -lbtree -o lexer.out

clean:
	rm -rf *.out *.o *.a *.class *.beam *.dSYM
