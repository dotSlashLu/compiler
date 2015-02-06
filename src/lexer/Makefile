ROOT = ../..
LIBDIR = ../lib

all: lexer.out scoped_lexer.out

lexer.out: libs lexer.c scanner.c scanner.h
	gcc scanner.c lexer.c -g -I. -I$(LIBDIR) -L$(LIBDIR) -lsymtbl -lbtree -o lexer.out

scoped_lexer.out: libs
	gcc scanner.c scoped_lexer.c -g -I. -I$(LIBDIR) -L$(LIBDIR) -lsymtbl -lbtree -o scoped_lexer.out

test: lexer.out scoped_lexer.out
	./lexer.out lexer.in
	./scoped_lexer.out scoped_lexer.in

libs:
	cd $(LIBDIR) && $(MAKE)

clean:
	rm -rf *.out *.o *.a *.class *.beam *.dSYM
