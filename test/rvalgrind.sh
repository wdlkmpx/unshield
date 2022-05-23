#!/bin/sh
valgrind --num-callers=10 --leak-check=yes src/unshield $@
