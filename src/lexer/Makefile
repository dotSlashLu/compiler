ROOT = ../..
LIBDIR = ../lib

all: lexer.out

lexer.out:	lexer.c scanner.c scanner.h
	gcc scanner.c lexer.c -g -I. -I$(LIBDIR) -L$(LIBDIR) -lsymtbl -lbtree -o lexer.out

test: lexer.out
	./lexer.out lexer.in

clean:
	rm -rf *.out *.o *.a *.class *.beam *.dSYM
