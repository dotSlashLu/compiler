CC = gcc
CCFLAGS = -g -Wall
CCFLAGS_LIB = -c
TESTS = btree symtbl

all: libbtree.a libsymtbl.a

libbtree.a: btree.c btree_test.c
	$(CC) btree.c $(CCFLAGS_LIB) $(CCFLAGS) -o btree.o
	$(AR) rcs libbtree.a btree.o

libsymtbl.a: symtbl.c symtbl.h
	$(CC) symtbl.c $(CCFLAGS_LIB) $(CCFLAGS) -o symtbl.o
	$(AR) rcs libsymtbl.a symtbl.o

btree_test.out: libbtree.a
	$(CC) btree_test.c -L. -lbtree -o btree_test.out $(CCFLAGS)

symtbl_test.out: libsymtbl.a
	$(CC) symtbl_test.c -L. -lsymtbl -lbtree -o symtbl_test.out $(CCFLAGS)

test: btree_test.out symtbl_test.out
	for i in $^; do \
		`./$$i`; \
	done;

clean:
	rm -rf *.out *.o *.a *.class *.beam *.dSYM
