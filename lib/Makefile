CC = gcc
CCFLAGS = -g -Wall
CCFLAGS_LIB = -c

all: libbtree.a

libbtree.a: btree.c btree_test.c
	$(CC) btree.c $(CCFLAGS_LIB) $(CCFLAGS) -o btree.o
	ar rcs libbtree.a btree.o

btree_test.out: libbtree.a
	$(CC) btree_test.c -L. -lbtree -o btree_test.out $(CCFLAGS)

test: libbtree.a btree_test.out
	./btree_test.out

clean:
	rm -rf *.out *.o *.a *.class *.beam *.dSYM
