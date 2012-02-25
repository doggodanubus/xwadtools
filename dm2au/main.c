#include	<sys/types.h>
#include	<fcntl.h>
#include	<stdio.h>
#include	<limits.h>
#include	<stdlib.h>
#include	<string.h>

#include "findwad.h"
#include "convtype.h"

extern int convert_rawsnd(int, char *name, int, int);

int main(int argc, char *argv[])
{
	int	in_fd, out_fd, usage = 0;
	char	*wad = NULL, *soundname = NULL;
	char filename[PATH_MAX] = "\0";
	convtype_t convtype = CT_ULAW;
	char *self = argv[0];

	if(argc < 2) usage = 1;

	while(++argv, --argc) {
		if(strcmp(argv[0], "-f") == 0) {
			if(argc > 1) {
				wad = fw_find_wad(argv[1]);
				++argv, --argc;
			} else {
				usage = 1;
			}
		} else if(strcmp(argv[0], "-r") == 0) {
			convtype = CT_RAW;
		} else if(strcmp(argv[0], "-w") == 0) {
			convtype = CT_WAV;
		} else if(argv[0][0] == '-') {
			fprintf(stderr, "Unknown option: %s\n", argv[0]);
			usage = 1;
		} else if(!soundname) {
			soundname = argv[0];
		} else if(!filename[0]) {
			strcpy(filename, argv[0]);
		} else {
			usage = 1;
		}
	}

	if(!wad) wad = fw_find_iwad();
	if(!soundname) usage = 1;

	if(!filename[0]) {
		char *ext = "au";
		if(convtype == CT_RAW) ext = "snd";
		if(convtype == CT_WAV) ext = "wav";
		sprintf(filename, "%s.%s", soundname, ext);
	}

	if(usage) {
		fprintf(stderr, "Usage: %s [-r | -w] [-f pwad] sndname [filename]\n", self);
		exit(1);
	}

	if(!wad) {
		fprintf(stderr, "Couldn't find WAD file\n");
		exit(2);
	}

	if ((in_fd = open(wad, O_RDONLY, 0)) < 0) {
		perror(wad);
		exit(2);
	}

	if(strcmp(filename, "-") == 0) {
		out_fd = 1;
	} else {
		if((out_fd = open(filename, O_WRONLY | O_CREAT, 0666)) < 0) {
			perror(filename);
			exit(2);
		}
	}

	if (convert_rawsnd(in_fd, soundname, out_fd, convtype)) {
		unlink(filename); // don't leave junk files around on error
		exit(2);
	}

	fprintf(stderr, "Wrote output to %s%s\n",
			(out_fd == 1 ? "" : "file: "),
			(out_fd == 1 ? "standard output" : filename));
	exit(0);
}
