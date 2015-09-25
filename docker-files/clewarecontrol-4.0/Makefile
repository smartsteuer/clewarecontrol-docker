# $Revision: 100 $
VERSION=4.0

DEBUG=-g -W -pedantic #-pg #-fprofile-arcs
LDFLAGS+=`pkg-config --libs hidapi-libusb`
CXXFLAGS+=-O3 -Wall -DVERSION=\"$(VERSION)\" $(DEBUG) `pkg-config --cflags hidapi-libusb`
CFLAGS+=$(CXXFLAGS)

OBJS=main.o USBaccessBasic.o USBaccess.o error.o

all: clewarecontrol

clewarecontrol: $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o clewarecontrol

cleware_python:
	swig -c++ -python cleware.i
	python setup.py build_ext --inplace
	./install-lib.py

cleware_perl:
	swig -c++ -perl5 cleware.i
	g++ -c `perl -MConfig -e 'print join(" ", @Config{qw(ccflags optimize cccdlflags)}, "-I$$Config{archlib}/CORE")'` cleware_wrap.cxx USBaccessBasic.cpp USBaccess.cpp
	g++ `perl -MConfig -e 'print $$Config{lddlflags}'` cleware_wrap.o USBaccessBasic.o USBaccess.o -o cleware.so
	./install-lib.pl

install: clewarecontrol
	cp clewarecontrol $(DESTDIR)/usr/bin
	cp clewarecontrol.1 $(DESTDIR)/usr/share/man/man1/clewarecontrol.1

uninstall: clean
	rm -f $(DESTDIR)/usr/bin/clewarecontrol
	rm -f $(DESTDIR)/usr/share/man/man1/clewarecontrol.1.gz

clean:
	rm -rf $(OBJS) clewarecontrol core gmon.out *.da build cleware_wrap.cxx _cleware.so cleware.py* cleware.pm *.o cleware.so

package: clean
	# source package
	rm -rf clewarecontrol-$(VERSION)*
	mkdir clewarecontrol-$(VERSION)
	cp -a *.c* *.h *.i *.pl *py readme*.txt clewarecontrol.1 Makefile license.txt clewarecontrol-$(VERSION)
	tar cf - examples --exclude=.svn  | tar xvf - -C clewarecontrol-$(VERSION)
	tar czf clewarecontrol-$(VERSION).tgz clewarecontrol-$(VERSION)
	rm -rf clewarecontrol-$(VERSION)

check:
	cppcheck -v --enable=all --inconclusive -I. . 2> err.txt
