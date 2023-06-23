include ../config.mk

APP  = unshield$(EXE)
# ls *.c | sed "s%\.c%.o%g" | tr "\n" " " >> Makefile
OBJS =  unshield.o

LDFLAGS +=
#CPPFLAGS += -I..
CFLAGS += -I.. -I../lib $(ICONV_CFLAGS)
LIBS   += ../lib/libunshield.a  $(ICONV_LIBS) $(LSHLWAPI)

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(APP) $(LDFLAGS) $(LIBS)

strip: all
	$(STRIP) $(APP)

distclean: clean

clean:
	rm -f *.o *~ $(APP)

install: all
	mkdir -p $(DESTDIR)$(bindir)
	install -c $(APP) $(DESTDIR)$(bindir)

install-strip: strip install

uninstall:
	rm -f $(DESTDIR)$(bindir)/$(APP)

