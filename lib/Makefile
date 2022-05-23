include ../config.mk

LIB_STATIC = libunshield.a

# ls *.c | sed "s%\.c%.o%g" | tr "\n" " " >> Makefile
OBJS = component.o directory.o file.o file_group.o helper.o libunshield.o log.o \
	convert_utf/ConvertUTF.o \
	zlib/adler32.o zlib/inffast.o zlib/inflate.o zlib/inftrees.o zlib/zutil.o

#CPPFLAGS += -I..
CFLAGS += -I.. -Izlib
LIBS   += 

all: $(LIB_STATIC)

$(LIB_STATIC): $(OBJS)
	$(AR) rcs $(LIB_STATIC) $(OBJS)

strip:

distclean: clean

clean:
	rm -f *.o *~ *.a *.so convert_utf/*.o zlib/*.o

install: $(LIB_STATIC)
	mkdir -p $(DESTDIR)$(libdir)
	install -c $(LIB_STATIC) $(DESTDIR)$(libdir)

install-strip: install

uninstall:
	rm -f $(DESTDIR)$(libdir)/$(LIB_STATIC)*


