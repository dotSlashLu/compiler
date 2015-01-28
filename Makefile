CC=gcc
CCFLAGS=-g -Wall

btree_test: btree.c btree_test.c
	$(CC) $^ -o btree_test.out $(CCFLAGS)

predictive_parser:	btree_test
	$(CC) predictive_parser.c -o predictive_parser.out $(CCFLAGS)

clean:
	rm -rf *.out *.class *.beam *.dSYM
