include ../config.mk

APP  = unshield
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
	@if test -f $(APP).exe ; then \
		echo $(STRIP) $(APP).exe; \
		$(STRIP) $(APP).exe; \
	else \
		echo $(STRIP) $(APP); \
		$(STRIP) $(APP); \
	fi;

distclean: clean

clean:
	rm -f *.o *~ $(APP) $(APP).exe

install: all
	mkdir -p $(DESTDIR)$(bindir)
	install -c $(APP) $(DESTDIR)$(bindir)

install-strip: strip install

uninstall:
	rm -f $(DESTDIR)$(bindir)/$(APP)

