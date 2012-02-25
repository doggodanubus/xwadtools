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
# nodes with warm. The output PWAD is ready for playing.
#

if [ $# -eq 1 ]; then
	WAD="$1"
elif [ $# -eq 2 ]; then
	CONF="-config $1"
	WAD="$2"
else
	echo "usage: $0 [config-file] wad-file"
	exit 1
fi

slige -doom2 -nulls $CONF "$WAD" || {
	echo "oops, slige problem generating level map"
	exit 1
}

warm "$WAD" || {
	echo "oops, warm problem"
	exit 1
}

exit 0
