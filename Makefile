CC = gcc
CCFLAGS = -g -Wall
DIRS = src

all:
	for i in $(DIRS); do \
		(cd $$i && echo -e "\nMaking $$i" && $(MAKE)) || exit 1; \
	done

clean:
	for i in $(DIRS); do \
		(cd $$i && echo -e "\nCleaning $$i" && $(MAKE) clean) || exit 1; \
	done
