#!/bin/sh

set_md5sum()
{
    if test -n "$MD5SUM" ; then
        return # already set
    fi
    if command -v md5sum ; then
        export MD5SUM='md5sum'
    elif command -v gmd5sum ; then
        export MD5SUM='gmd5sum'
    elif command -v md5 2>/dev/null ; then
        export MD5SUM='md5'
    else
        echo "md5sum utility is missing, please install it"
        echo "aborting tests"
        exit 1
    fi
}


check_md5()
{
    if test -z "$MD5SUM" ; then
        return
    fi
    md5file="$1"
    logfile="$2"

    if [ "$MD5SUM" = "md5" ] ; then
        # BSD
        while read md5 file
        do
            if ! md5 -q -s "$md5" "$file" >/dev/null 2>&1 ; then
                echo "ERROR"
                return 1
            fi
        done < ${md5file}
        echo "OK"
        return 0
    fi

    if ${MD5SUM} -c ${md5file} >${logfile} 2>&1 ; then
        echo "OK"
        return 0
    else
        echo "ERROR"
        return 1
    fi
}

#==============================================================

set_unshield()
{
    if test -n "$UNSHIELD" ; then
        return # already set
    fi
    unshields="$(pwd)/unshield $(pwd)/unshield.exe
$(pwd)/src/unshield
$(pwd)/build/src/unshield
$(pwd)/src/unshield.exe
$(pwd)/build/src/unshield.exe"
    for i in ${unshields}
    do
        if ! test -x "$i" ; then
            continue
        fi
        echo "------------------------------------------------"
        echo "UNSHIELD=${i}"
        echo "------------------------------------------------"
        if test "$i" = "$(pwd)/unshield" || test "$i" = "$(pwd)/unshield" ; then
           echo "*** using custom unshield binary in ./"
           echo "------------------------------------------------"
        fi
        export UNSHIELD=${i}
        break
    done
    sleep 1
    if test -z "$UNSHIELD" ; then
        echo "coult not find unshield in the following locations:"
        echo "${unshields}"
        echo "aborting"
        exit 1
    fi
    case $UNSHIELD in *.exe)
        if [ "$(uname -s)" = "Linux" ] ; then
            UNSHIELD="wine $UNSHIELD"
        fi
        ;;
    esac
}


set_directory()
{
    DIR="$1"
    mkdir -p "$DIR"
    cd "$DIR" || exit 1
}


set_wget()
{
    if test -n "$XWGET" ; then
        return # already set
    fi
    if command -v curl ; then
        export XWGET='curl -sSL -o'
    elif command -v fetch ; then
        # FreeBSD
        export XWGET='fetch -q --no-verify-peer -o'
    elif command -v wget ; then
        export XWGET='wget -q --no-check-certificate -O'
    else
        echo "Cannot find curl/fetch/wget.. aborting"
        exit 1
    fi
}


download_file()
{
    if test -z "$XWGET" ; then
        return
    fi
    dlurl="$1"
    dlfile="$2"
    if ! test -f "${dlfile}" ; then
        #echo "${XWGET} \"${dlfile}\" \"${dlurl}\""
        ${XWGET} "${dlfile}" "${dlurl}"
        if [ $? -ne 0 ] ; then
            echo "Could not download file" >&2
            rm -f "${dlfile}"
            return 1
        fi
    fi
    return 0
}


clean_directory_except()
{
    keepfile="$1"
    cd "$DIR"
    for i in $(ls)
    do
        if test "$i" != "$keepfile" ; then
            rm -rf "$i"
        fi
    done
}


cleanup_func()
{
    if test -z "$KEEP_TESTS" ; then
        trap "$@" TERM INT EXIT
    fi
}

