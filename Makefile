CFLAGS+=	-Wall -Wextra
CFLAGS+=	-I/usr/local/include
CFLAGS+=	-O2

CFLAGS+=	-L/usr/local/lib
LDFLAGS+=	-static

LDLIBS+=	-lkcgi -lz

all: ip.fcgi

clean: ;	rm -f ip.fcgi
install: ;	install -s -m755 ip.fcgi /var/www/fcgi-bin

.PHONY: all clean
