
CC=gcc
override CFLAGS+=-fPIC -Wall -O3 -Iinclude

.PHONY: all clean

all: src/libstrap/lsmemory.o

clean:
	rm -Rf src/libstrap/*.o
