#!/bin/sh
set -e
cd `dirname $0`
MD5_FILE=`pwd`/`basename $0 .sh`.md5

. ../functions.sh
set_md5sum    # ${MD5SUM}
set_wget      # ${XWGET}
set_unshield  # ${UNSHIELD}
set_directory ${HOME}/.cache/unshieldtest/avigomanager

download_file "https://www.dropbox.com/s/8r4b6752swe3nhu/unshield-avigomanager11b22.zip?dl=1" test.zip
clean_directory_except test.zip
cleanup_func 'clean_directory_except test.zip'

unzip -o -q test.zip 'data*'

# ===================================================================

set +e

${UNSHIELD} -d extract1 x data1.cab > log1 2>&1
CODE=$?
if [ ${CODE} -ne 1 ]; then
    cat log1 >&2
    echo "unshield should have failed with error 1 but was $CODE" >&2
    exit 2
fi

${UNSHIELD} -O -d extract2 x data1.cab > log2 2>&1
CODE=$?
if [ ${CODE} -ne 0 ]; then
    cat log2 >&2
    echo "unshield failed with error $CODE" >&2
    exit 3
fi

cd extract2
if ! check_md5 ${MD5_FILE} md5.log ; then
    echo "MD5 sums diff" >&2
    exit 4
fi

exit 0
