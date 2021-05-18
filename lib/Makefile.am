## useful flags

ZLIBCFLAGS  = -Izlib
ZLIBSOURCES = zlib/adler32.c zlib/inffast.c zlib/inflate.c zlib/inftrees.c zlib/zutil.c

AM_CPPFLAGS = $(ZLIBCFLAGS)

## create this library
lib_LTLIBRARIES = libunshield.la

## use these sources
libunshield_la_SOURCES = \
	convert_utf/ConvertUTF.c convert_utf/ConvertUTF.h \
	$(ZLIBSOURCES) \
	component.c \
	directory.c \
	file.c \
	file_group.c \
	helper.c \
	internal.h \
	libunshield.h libunshield.c \
	log.h log.c \
	cabfile.h

#libunshield_la_LDFLAGS = -no-undefined -version-info 0:0:0
libunshield_la_LDFLAGS = -no-undefined
libunshield_la_LIBADD  = $(ZLIBLIBS)

include_HEADERS = libunshield.h
