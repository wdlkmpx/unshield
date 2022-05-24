#!/bin/sh
set -e
cd `dirname $0`
MD5_FILE=`pwd`/`basename $0 .sh`.md5

. ../functions.sh
set_md5sum    # ${MD5SUM}
set_wget      # ${XWGET}
set_unshield  # ${UNSHIELD}
set_directory ${HOME}/.cache/unshieldtest/thefeeblefiles

download_file "https://www.dropbox.com/s/1ng0z9kfxc7eb1e/unshield-the-feeble-files-spanish.zip?dl=1" test.zip
clean_directory_except test.zip
cleanup_func 'clean_directory_except test.zip'

unzip -o -q test.zip 'data*'

# ===================================================================

set +e

${UNSHIELD} -O -d extract1 x data1.cab > log2 2>&1
CODE=$?
if [ ${CODE} -ne 0 ]; then
    cat log2 >&2
    echo "unshield failed with error $CODE" >&2
    echo "See https://github.com/twogood/unshield/issues/27" >&2
    exit 2
fi

cd extract1
if ! check_md5 ${MD5_FILE} md5.log ; then
    echo "MD5 sums diff" >&2
    echo "See https://github.com/twogood/unshield/issues/27" >&2
    exit 4
fi

exit 0
