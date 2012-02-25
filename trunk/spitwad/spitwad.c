#define VERSION	"1.1"

/*
=============================================================================

							  SPITWAD

						  by John Carmack

=============================================================================
*/


#include <stdint.h>

#include "cmdlib.h"

#include "sysdep.h"
#define LittleLong(x) bswapl(x)

//================
//
// wad file types
//
//================

typedef struct
{
	uint32_t		filepos;
	uint32_t		size;
	char		name[8];
} lumpinfo_t;


typedef struct
{
	char	identification[4];
	uint32_t	numlumps;
	uint32_t	infotableofs;
} wadinfo_t;


/*
===============
=
= main
=
===============
*/

int main (int argc, char **argv)
{
	char	filename[128];
	int		handle;
	wadinfo_t	wad;
	lumpinfo_t	*lumps, *lump_p;
	int		i,j;
	char	name[9];
	uint32_t	datasize, wadsize, infosize;
	char	*lzss;


	printf ("SPITWAD "VERSION" by John Carmack, copyright (c) 1992 Id Software\n");

	if (CheckParm ("?") || (argc != 2 && argc != 4))
	{
		printf ("SPITWAD filename<.wad> [start end]\n");
		exit (1);
	}

	strcpy (filename, argv[1]);
	DefaultExtension (filename, ".wad");

	handle = SafeOpenRead (filename);
	wadsize = filelength(handle);
	datasize = 0;

	SafeRead (handle, &wad, sizeof(wad));

	if (strncmp(wad.identification,"IWAD",4) && strncmp(wad.identification,"PWAD",4))
		Error ("Wad file %s doesn't have IWAD or PWAD id\n",filename);

	wad.numlumps = LittleLong(wad.numlumps);
	wad.infotableofs = LittleLong(wad.infotableofs);

	infosize = wad.numlumps*sizeof(lumpinfo_t);
	lumps = lump_p = SafeMalloc(infosize);
	lseek (handle, wad.infotableofs, SEEK_SET);
	SafeRead (handle, lumps, infosize);
	infosize += sizeof(wadinfo_t);

	printf ("\n");
	printf ("WAD file    : %s\n",filename);
	printf ("numlumps    : %u\n",wad.numlumps);
	printf ("infotableofs: %u\n",wad.infotableofs);
	printf ("\n");
	printf ("lump name       size  filepos    0xsize 0xfpos\n");
	printf ("---- -------- ------ --------    ------ ------\n");

	name[8] = 0;

	for (i=0 ; i<wad.numlumps ; i++, lump_p++)
	{
		datasize += LittleLong (lump_p->size);
		strncpy (name,lump_p->name,8);
		for (j=7 ; j>=0 ; j--)
			if (!name[j])
				name[j] = ' ';
			else
				break;
		if (name[0] & 0x80)
		{
			lzss = "(lzss)";
			name[0] &= 0x7f;
		}
		else lzss = "";
		printf ("%4i %s %6i %8i    %6x %6x %s\n", i, name
		, LittleLong(lump_p->size), LittleLong(lump_p->filepos)
		, LittleLong(lump_p->size), LittleLong(lump_p->filepos),
		lzss );
	}

	printf ("\n");
	printf ("File size:%9i\n", wadsize);
	printf ("Data size:%9i\n", datasize);
	printf ("Info size:%9i\n", infosize);
	printf ("Wasted   :%9i\n", wadsize-(datasize+infosize));

	return 0;
}
