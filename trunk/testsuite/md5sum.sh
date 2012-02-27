#!/bin/sh

# Some of our target platforms use GNU coreutils (e.g. Linux),
# and some don't (e.g. FreeBSD). This script exists to reformat
# the output of the BSD-style md5(1) so it looks like the GNU
# md5sum(1)'s output.

# Tested on FreeBSD-9.0

set -e

if which md5sum >/dev/null 2>/dev/null; then
	md5sum "$@"
	status="$?"
elif which md5 >/dev/null 2>/dev/null; then
	md5 "$@" | sed 's/^MD5 (\([^)]*\)) = \([0-9a-f]*\)$/\2  \1/'
	status="$?"
else
	echo "$0: can't find either md5 or md5sum, failed" 2>&1
	exit 1
fi

exit "$status"
