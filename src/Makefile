CC = gcc
CCFLAGS = -g -Wall
ROOT = ..
LIBDIR = lib
DIRS = lib . lexer

all: libs lexer.out infix_translator.out predictive_parser.out

infix_translator.out: infix_translator.c
	$(CC) $^ $(CCFLAGS) -o infix_translator.out

predictive_parser.out: predictive_parser.c
	$(CC) $^ $(CCFLAGS) -o predictive_parser.out

lexer.out: libs
	(cd lexer && $(MAKE)) || exit 1

libs:
	cd $(LIBDIR) && $(MAKE)

test: infix_translator.out
	echo "Testing C version:"
	./infix_translator.out "1+2+3"
	echo -e "\nTesting erl version:"
	./infix_translator.erl "1+2+3"

clean:
	for dir in $(DIRS); do \
		(cd $$dir && rm -rf *.out *.o *.a *.class *.beam *.dSYM) || exit 1; \
	done
