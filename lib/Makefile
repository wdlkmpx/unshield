include ../config.mk

LIB_STATIC = libunshield.a

# ls *.c | sed "s%\.c%.o%g" | tr "\n" " " >> Makefile
OBJS = component.o \
	directory.o \
	file.o \
	file_group.o \
	helper.o \
	libunshield.o \
	log.o \
	convert_utf/ConvertUTF.o $(BUILTIN_ZLIB_O)

#CPPFLAGS += -I..
CFLAGS += -I.. $(ZLIB_CFLAGS)
LIBS   += $(ZLIB_LIBS)

all: $(LIB_STATIC)

$(LIB_STATIC): $(OBJS)
	$(AR) rcs $(LIB_STATIC) $(OBJS)

strip:

distclean: clean

clean:
	rm -f *.o *~ *.a *.so convert_utf/*.o zlib/*.o

install: $(LIB_STATIC)
	mkdir -p $(DESTDIR)$(libdir)/pkgconfig
	install -c $(LIB_STATIC) $(DESTDIR)$(libdir)
	install -c ../libunshield.pc $(DESTDIR)$(libdir)/pkgconfig

install-strip: install

uninstall:
	rm -f $(DESTDIR)$(libdir)/$(LIB_STATIC)


