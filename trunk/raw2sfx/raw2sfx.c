/************************************************************************/
/*      Copyright (C) 1999 by Udo Munk (munkudo@aol.com)                */
/*                                                                      */
/*      Permission to use, copy, modify, and distribute this software   */
/*      and its documentation for any purpose and without fee is        */
/*      hereby granted, provided that the above copyright notice        */
/*      appears in all copies and that both that copyright notice and   */
/*      this permission notice appear in supporting documentation.      */
/*      The author and contibutors make no representations about the    */
/*      suitability of this software for any purpose. It is provided    */
/*      "as is" without express or implied warranty.                    */
/************************************************************************/

/*
 *   Tool to convert raw sound data into id's sfx format
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sysdep.h"

void usage(char *name)
{
	fprintf(stderr, "Usage: %s infile outfile\n", name);
	fprintf(stderr, "       outfile may be -, to write to standard output\n");
	exit(1);
}

int main(int argc, char **argv)
{
	FILE		*ifp, *ofp;
	int		flen;
	unsigned short	i;
	unsigned char	buf[65535];

	if (argc != 3)
		usage(*argv);

	if ((ifp = fopen(*(argv+1), "rb")) == NULL) {
		fprintf(stderr, "can't open input file for reading\n");
		exit(1);
	}

	flen = filelength(fileno(ifp));
	if (flen > 65535) {
		fprintf(stderr, "fatal: input file has more than 65535 samples\n");
		exit(1);
	} else if (flen < 50) {
		fprintf(stderr, "warning: input file is very short, really a sound sample?\n");
	}

	if(strcmp(argv[2], "-") == 0) {
		ofp = stdout;
	} else if ((ofp = fopen(*(argv+2), "wb")) == NULL) {
		fprintf(stderr, "can't open output file for writing\n");
		exit(1);
	}

	/* magic number for id's sfx format probably */
	i = 3;
	putshort(i, ofp);
	/* 11kHz sample rate */
	i = 11025;
	putshort(i, ofp);
	/* number of samples */
	i = (unsigned short) flen;
	putshort(i, ofp);
	/* separator, whatever */
	i = 0;
	putshort(i, ofp);

	fread(&buf[0], flen, 1, ifp);
	if(flen >= 4) {
		if(buf[0] == 'R' && buf[1] == 'I' && buf[2] == 'F' && buf[3] == 'F') {
			fprintf(stderr, "warning: input looks like a WAV file, you sure it's raw?\n");
		} else if(buf[0] == '\x03' && buf[1] == '\x00' && buf[2] == '\x11' && buf[3] == '\x2b') {
			fprintf(stderr, "warning: input already a sfx file?\n");
		}
	}
	fwrite(&buf[0], flen, 1, ofp);

	fclose(ifp);
	fclose(ofp);
	return 0;
}
