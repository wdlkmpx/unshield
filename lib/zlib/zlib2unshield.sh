#!/bin/sh

# must not use ./configure --solo
# Z_SOLO makes functions behave differently

# linux
git checkout -- .
./configure

sed -i '/OBJG = /d' Makefile

#deflate='deflate.c deflate.h trees.c trees.h'

# don't need crc32.c/crc32.h only adler32.c
sed -i '/define GUNZIP/d' inflate.h
#gzip='crc32.c crc32.h'

#  Normally either infback.o or inflate.o would be linked into an application--not both
#extra='infback.c'

mkdir -p zlib-nogz
cp -fv ${deflate} \
	adler32.c \
	${gzip} \
	${extra} \
	inffast.c inffast.h \
	inffixed.h \
	inflate.c inflate.h \
	inftrees.c inftrees.h \
	zutil.c zutil.h \
	zconf.h zlib.h \
	zlib-nogz

# copy zlib-nogz/* to unshield/lib/zlib/
# try to compile: run ./rebuild.sh and fix any issues until it compiles

# reduce size

# zlib.h
#    /* basic functions */
#        delete only deflate*
#    /* Advanced functions */
#        (delete all defalte* functions)
#    /* utility functions */
#        (until /* gzip file access functions */)
#    /* gzip file access functions */
#        (keep only: typedef struct gzFile_s *gzFile;

