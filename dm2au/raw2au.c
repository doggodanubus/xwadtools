/* This module extracts raw sound information from a wadfile */

#include	<stdio.h>
#include	<unistd.h>
#include	"doomdefs.h"
#include	"directory.h"
#include	"convtype.h"

#define SND_MAGIC	3
struct snd_header {
	two_byte magic;			/* The magic number 3 */
	two_byte sample_rate;		/* The sample rate (11025) */
	two_byte num_samples;		/* The number of samples */
	two_byte zero;			/* Null integer */
};

extern int sample_cvt(int);

int convert_rawsnd(int fd, char *name, int outfd, convtype_t convtype)
{
	struct dir_entry	entry;
	struct snd_header	header;
	char			outfile[BUFSIZ];
	FILE			*output;
	int			i, samplei;
	unsigned char		sample, ulaw;
	float			sum = 0, increment;

	/* Set the fd to the start of the directory entries */
	if (set_directory(fd) < 0) {
		fprintf(stderr, "Can't find start of directories.\n");
		return(-1);
	}

	/* Now cycle through the entries, looking for the sound  */
	if (get_entry(fd, name, &entry) < 0) {
		fprintf(stderr, "Couldn't find directory entry for %s\n", name);
		return(-1);
	}

	/* Go to the entry and retrieve the sound */
	if (lseek(fd, entry.res_start, SEEK_SET) < 0) {
		perror("lseek()");
		return(-1);
	}
	if (read(fd, (char *)&header, sizeof(header)) != sizeof(header)) {
		perror("header read error");
		return(-1);
	}
	if (header.magic != SND_MAGIC) {
		fprintf(stderr, "%s is not a sound resource (%d).\n",name,header.magic);
		return(-1);
	}
	/* Print out the header for now */
	printf("Sound: sample rate = %d, holds %d samples.\n",
				header.sample_rate, header.num_samples);

	/* increment is the number of bytes to read each time */
	increment = ((float)header.sample_rate) / 8000;

	output = fdopen(outfd, "wb");
	if(!output) {
		perror("fdopen");
		return(-1); // not sure this can ever happen, *shrug*
	}

	if(convtype == CT_WAV) {
		/* write RIFF header. This is a dumb way to do it, but it works. */
		unsigned char riffhdr[] = {
			/* 00 */ 'R', 'I', 'F', 'F',
			/* 04 */ 0xff, 0xff, 0xff, 0xff, // riff length, fill in later
			/* 08 */ 'W', 'A', 'V', 'E',
			/* 0c */ 'f', 'm', 't', ' ',
			/* 10 */ 0x10, 0x00, 0x00, 0x00,
			/* 14 */ 0x01, 0x00, 0x01, 0x00,
			/* 18 */ 0xff, 0xff, 0x00, 0x00, // sample rate, fill in later
			/* 1c */ 0xff, 0xff, 0x00, 0x00, // avg bytes/sec (sample rate), fill in later
			/* 20 */ 0x01, 0x00, 0x08, 0x00,
			/* 24 */ 'd', 'a', 't', 'a',
			/* 28 */ 0xff, 0xff, 0xff, 0xff  // actual length, fill in later
		};
		unsigned int rifflen = header.num_samples + 36;

		riffhdr[0x04] = rifflen & 0xff;
		riffhdr[0x05] = (rifflen >> 8) & 0xff;
		riffhdr[0x06] = (rifflen >> 16) & 0xff;
		riffhdr[0x07] = (rifflen >> 24) & 0xff;

		riffhdr[0x28] = header.num_samples & 0xff;
		riffhdr[0x29] = (header.num_samples >> 8) & 0xff;
		riffhdr[0x2a] = (header.num_samples >> 16) & 0xff;
		riffhdr[0x2b] = (header.num_samples >> 24) & 0xff;

		riffhdr[0x18] = riffhdr[0x1c] = header.sample_rate & 0xff;
		riffhdr[0x19] = riffhdr[0x1d] = (header.sample_rate >> 8) & 0xff;

		fwrite(riffhdr, sizeof(riffhdr), 1, output);
	}

	/* Write the output file */
	for (i = 0, read(fd, &sample, 1); i < header.num_samples;) {
		if(convtype == CT_ULAW) {
			/* convert the excess 128 to two's complement */
			samplei = 0x80 - sample;
			/* increase the volume, convert to uLAW */
			ulaw = (unsigned char)sample_cvt(samplei * 16);
			/* Output the converted sample */
			fputc((char)ulaw, output);

			/* skip input to compensate for sampling frequency diff */
			sum += increment;
			while(sum > 0) {
				if (read(fd, &sample, 1) != 1) {
					perror("read()");
					return(-1);
				}
				++i; --sum;
			}
		}
		else /* Raw snd format */
		{
			fputc(sample, output);
			++i;
			if (read(fd, &sample, 1) != 1) {
				perror("read()");
				return(-1);
			}
		}
	}

	fclose(output);

	/* Done! */
	return(0);
}
