CC = gcc
CCFLAGS = -g -Wall
DIRS = lib src

all:
	for i in $(DIRS); do \
		(cd $$i && echo "Making $$i" && $(MAKE)) || exit 1; \
	done

clean:
	for i in $(DIRS); do \
		(cd $$i && echo "Cleaning $$i" && $(MAKE) clean) || exit 1; \
	done
