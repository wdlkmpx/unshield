#!/bin/sh

. test/functions.sh

if test "$TRAVIS_OS_NAME" = "windows" ; then # see rebuild.sh
    export UNSHIELD="$(pwd)/build/src/unshield.exe"
    set_md5sum    # ${MD5SUM}
else
    set_md5sum    # ${MD5SUM}
    set_unshield  # ${UNSHIELD}
fi

ALL_RET=0
for SCRIPT in $(find $(dirname $0)/test/v* -name '*.sh' | sort)
do
  echo -n "Running test $SCRIPT..."
  bash ${SCRIPT}
  TEST_RET=$?
  if [ "$TEST_RET" = "0" ]; then
    echo "succeeded"
  else
    echo "FAILED with code $TEST_RET"
    ALL_RET=1
  fi
done

exit $ALL_RET
