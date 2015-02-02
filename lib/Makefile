CC = gcc
CCFLAGS = -g -Wall
CCFLAGS_LIB = -c

all: btree

btree: btree.c btree_test.c
	$(CC) btree.c $(CCFLAGS_LIB) $(CCFLAGS) -o btree.o
	ar rcs libbtree.a btree.o
	$(CC) btree_test.c -L. -lbtree -o btree_test.out $(CCFLAGS)

clean:
	rm -rf *.out *.o *.a *.class *.beam *.dSYM
