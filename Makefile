
AR=ar
CC=gcc
INSTALL=install -Dm0644
RM=rm -f
RMDIR=rm -Rf
XCOPY=cp -dr --no-preserve=ownership

override CFLAGS+=-fPIC -Wall -O3 -Iinclude

DESTDIR=
PREFIX=$(DESTDIR)/usr
SRCDIR=src/libstrap
OBJS=$(SRCDIR)/lsmemory.o $(SRCDIR)/lsstring.o $(SRCDIR)/lsversion.o

.PHONY: all install install-dynamic install-static install-dev uninstall clean

all: libstrap.so libstrap.a

install: install-dynamic install-static install-dev
 
install-dynamic: libstrap.so
	$(INSTALL) libstrap.so $(PREFIX)/lib/libstrap.so

install-static: libstrap.a
	$(INSTALL) libstrap.a $(PREFIX)/lib/libstrap.a

install-dev:
	$(XCOPY) include $(PREFIX)/
	$(INSTALL) pkgconfig/libstrap.pc $(PREFIX)/lib/pkgconfig/libstrap.pc

uninstall:
	$(RM) $(PREFIX)/lib/pkgconfig/libstrap.pc
	$(RM) $(PREFIX)/include/libstrap.h
	$(RMDIR) $(PREFIX)/include/libstrap
	$(RM) $(PREFIX)/lib/libstrap.so $(PREFIX)/lib/libstrap.a

libstrap.so: $(OBJS)
	$(CC) $(CFLAGS) -shared -o $@ $^ $(LDFLAGS)

libstrap.a: $(OBJS)
	$(AR) crs $@ $^

clean:
	$(RM) libstrap.so libstrap.a
	$(RM) src/libstrap/*.o
