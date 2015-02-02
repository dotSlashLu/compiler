CC = gcc
CCFLAGS = -g -Wall
JAVAC = javac
ROOT = ..
LIBDIR = $(ROOT)/lib
DIRS = . lexer

all: lexer.out infix_translator.out predictive_parser.out

infix_translator.out: infix_translator.c
	$(CC) $^ $(CCFLAGS) -o infix_translator.out

predictive_parser.out: predictive_parser.c
	$(CC) $^ $(CCFLAGS) -o predictive_parser.out

lexer.out:
	(cd lexer && $(MAKE)) || exit 1

clean:
	for dir in $(DIRS); do \
		(cd $$dir && rm -rf *.out *.o *.a *.class *.beam *.dSYM) || exit 1; \
	done
