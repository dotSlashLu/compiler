CC = gcc
CCFLAGS = -g -Wall
JAVAC = javac
ROOT = ..
LIBDIR = $(ROOT)/lib

all: infix_translator.out predictive_parser.out

infix_translator.out: infix_translator.c
	$(CC) $^ $(CCFLAGS) -o infix_translator.out

predictive_parser.out: predictive_parser.c
	$(CC) $^ $(CCFLAGS) -o predictive_parser.out

clean:
	rm -rf *.out *.o *.a *.class *.beam *.dSYM
