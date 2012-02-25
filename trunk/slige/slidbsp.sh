#!/bin/sh

# Copyright (C) 1999-2000 by Udo Munk (munkudo@aol.com)
#
# Modified by B. Watson (yalhcru@gmail.com)
#
# Permission to use, copy, modify, and distribute this software
# and its documentation for any purpose and without fee is
# hereby granted, provided that the above copyright notice
# appears in all copies and that both that copyright notice and
# this permission notice appear in supporting documentation.
# The author and contibutors make no representations about the
# suitability of this software for any purpose. It is provided
# "as is" without express or implied warranty.
#
# Example shell script to generate a Doom ][ level with slige and build
# nodes with idbsp. The output PWAD is ready for playing.
#

trap 'rm -f slcust.wad tmp*-$$.wad tmp*-$$.map' 0

if [ $# -eq 1 ]; then
	WAD="$1"
elif [ $# -eq 2 ]; then
	CONF="-config $1"
	WAD="$2"
else
	echo "usage: $0 [config-file] wad-file"
	exit 1
fi

slige -doom2 -cwad slcust.wad || {
	echo "oops, slige problem generating custom PWAD"
	exit 1
}

slige -doom2 -nocustom -noslinfo $CONF tmp1-$$.wad || {
	echo "oops, slige problem generating level map"
	exit 1
}

wadldc MAP01 tmp1-$$.wad tmp1-$$.map || {
	echo "oops, wadldc problem decompiling level map"
	exit 1
}

idbsp -q tmp1-$$.map tmp1-$$.wad || {
	echo "oops, idbsp problem"
	exit 1
}

wadcat -o "$WAD" tmp1-$$.wad slcust.wad || {
	echo "oops, wadcat problem concatenating PWADS"
	exit 1
}

exit 0
