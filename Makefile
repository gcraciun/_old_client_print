CC      = gcc
CFLAGS  = -O -Wall -I. -I/usr/include/mysql
LDFLAGS = -L/usr/lib/mysql
LIBS    = -lmysqlclient -lz
OBJS	= util.o client_print.o

all:	clean client_print

.c.o:
	$(CC) $(CFLAGS) -c $<
	

client_print:$(OBJS)
	$(CC) $(CFLAGS) -o client_print $(OBJS) $(LDFLAGS) $(LIBS)

clean:
	rm -f *.o *~ client_print
install: all
	cp client_print /admin/bin/
	cp client_print.conf /admin/etc/
uninstall:
	rm /admin/bin/client_print
	rm /admin/etc/client_print.conf
