
CC=gcc
override CFLAGS+=-fPIC -Wall -O3 -Iinclude
SRCDIR=src/libstrap

.PHONY: all clean

all: $(SRCDIR)/lsmemory.o $(SRCDIR)/lsstring.o $(SRCDIR)/lsversion.o

clean:
	rm -Rf src/libstrap/*.o
