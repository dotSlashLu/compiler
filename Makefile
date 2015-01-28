CC = gcc
CCFLAGS = -Wall

btreetest: btree.c btree-test.c
	$(CC) $^ -o btree-test.out $(CCFLAGS)

clean:
	rm -rf *.out *.class *.beam *.dSYM
