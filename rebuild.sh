#!/bin/sh
# no param = cmake

set -e
set -x

rm -rf /var/tmp/unshield

if test -z "$1" ; then
    export CFLAGS="$CFLAGS -Wall -ggdb3"
    mkdir -p build
    cd build
    cmake -DBUILD_STATIC=1 -DCMAKE_INSTALL_PREFIX:PATH=/var/tmp/unshield .. && \
        make && make install
else
    export CFLAGS="$CFLAGS -ggdb3"
    ./configure --prefix=/var/tmp/unshield --enable-static --disable-shared && \
    make clean && \
    make install
fi

exit $?
