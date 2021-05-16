#!/bin/sh

if test "$TRAVIS_OS_NAME" = "windows" ; then # see rebuild.sh
   echo "*** Not running tests on Windows"
   exit 0
fi


ALL_RET=0

if command -v md5sum >/dev/null 2>&1 ; then
    export MD5SUM=md5sum
elif command -v gmd5sum >/dev/null 2>&1 ; then
    export MD5SUM=gmd5sum
else
    echo "md5sum utility is missing, please install it"
    echo "aborting tests"
    exit 1
fi

for SCRIPT in $(find $(dirname $0)/test/v* -name '*.sh')
do
  printf "%s" "Running test $SCRIPT..."
  sh ${SCRIPT}
  TEST_RET=$?
  if [ "$TEST_RET" = "0" ]; then
    echo "succeeded"
  else
    echo "FAILED with code $TEST_RET"
    ALL_RET=1
  fi
done
exit $ALL_RET
