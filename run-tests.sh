#!/bin/sh

. test/functions.sh
set_md5sum    # ${MD5SUM}
set_wget      # ${XWGET}
set_unshield  # ${UNSHIELD}

ALL_RET=0
for SCRIPT in $(find $(dirname $0)/test/v* -name '*.sh' | sort)
do
    printf "%s" "Running test $SCRIPT... "
    sh ${SCRIPT}
    TEST_RET=$?
    if [ "$TEST_RET" = "0" ]; then
        echo "succeeded"
    else
        echo "FAILED with code $TEST_RET"
        ALL_RET=1
    fi
done

if test -z "${ALLOW_FAIL}" ; then
    exit $ALL_RET
else
    exit 0
fi
