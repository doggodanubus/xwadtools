#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "sysdep.h"
#include "wad.h"
#include "wad64.h"
#include "lump_dir.h"
#include "wadfile.h"
#include "findwad.h"

#include "linespecials.c"

/* Rough conversion of doom2 levels to doom64 */

const char *progname;

things64_t things[32768];
sector64_t sectors[32768];
linedef64_t linedefs[32768];
sidedef64_t sidedefs[32768];
vertex64_t vertices[32768];
int thingcount = 0;
int sectorcount = 0;
int linedefcount = 0;
int sidedefcount = 0;
int vertexcount = 0;

void usage(char *msg) {
	if(msg) fprintf(stderr, "%s: %s\n", progname, msg);
	fprintf(stderr, "Usage: %s [ -t | <map> ] input.wad [output.wad]\n", progname);
	exit(msg != NULL);
}

void *safe_get_map_lump(wadfile_t *wf, const char *map, const char *lump, int *size) {
	void *got = get_map_lump(wf, (char *)map, (char *)lump, size);
	if(!got) {
		fprintf(stderr, "Can't find lump %s\n", lump);
		exit(1);
	}

	return got;
}

uint16_t hash_lump_name(const char *str) {
	unsigned int hash = 1315423911;
	unsigned int i    = 0;

	if(strcmp(str, "-") == 0)
		str = "?";

	for(i = 0; i < 8 && *str != '\0'; str++, i++)
		hash ^= ((hash << 5) + toupper((int)*str) + (hash >> 2));

	return hash % 65536;
}

void convert_vertices(wadfile_t *wf, const char *map) {
	int size, i;
	vertex_t *vert = (vertex_t *)safe_get_map_lump(wf, map, "VERTEXES", &size);

	for(i = 0; i < size / sizeof(vertex_t); i++) {
		vertex64_t *vert64 = &vertices[vertexcount];
		vert64->x = vert->x;
		vert64->y = vert->y;
		vert64->x_frac = vert64->y_frac = 0;

		vert++, vertexcount++;
	}
}

void convert_sectors(wadfile_t *wf, const char *map) {
	int size, i, j;
	sector_t *sector = (sector_t *)safe_get_map_lump(wf, map, "SECTORS", &size);

	for(i = 0; i < size / sizeof(sector_t); i++) {
		sector64_t *sec64 = &sectors[sectorcount];
		sec64->f_height = sector->f_height;
		sec64->c_height = sector->c_height;
		sec64->tag = sector->tag;
		sec64->type = sector->flags; /* TODO: actual conversion */
		sec64->flags = 0;

		sec64->f_index = hash_lump_name(sector->f_texture);
		sec64->c_index = hash_lump_name(sector->c_texture);

		for(j = 0; j < 5; j++)
			sec64->color_index[j] = sector->light;

		sector++, sectorcount++;
	}
}

/* Linedef flags:
	Bit - effect
	0 - impassable
	1 - block monsters
	2 - two-sided
	3 - unpeg upper
	4 - unpeg lower
	5 - secret
	6 - block sound
	7 - never map
	8 - always on map
	9 - show middle texture on 2-sided line

	Bits 0-8 are in old Doom, bit 9 is 64 only. The other
	doom64 bits (10 and up) aren't relevant here (yet?)
*/

void convert_linedefs(wadfile_t *wf, const char *map) {
	int size, i;
	linedef_t *ldef = (linedef_t *)safe_get_map_lump(wf, map, "LINEDEFS", &size);

	for(i = 0; i < size / sizeof(linedef_t); i++) {
		linedef64_t *ldef64 = &linedefs[linedefcount];
		ldef64->v_from = ldef->v_from;
		ldef64->v_to = ldef->v_to;
		ldef64->l_side = ldef->l_side;
		ldef64->r_side = ldef->r_side;
		ldef64->tag = ldef->tag;
		ldef64->flags = ldef->flags & 0xff; /* TODO: figure out when to set 0x200 flag */
		// ldef64->type = ldef->type;
		ldef64->type = linedef_type_conv[ldef->type & 0xff];
		// if(!ldef64->type) ldef64->type = ldef->type;

		if(ldef->flags != 0)
			fprintf(stderr, "linedef %d was flags %d, now %d\n", i, ldef->flags, ldef64->flags);

		if(ldef->type != 0)
			fprintf(stderr, "linedef %d was type %d, now %d\n", i, ldef->type, ldef64->type);
		ldef++, linedefcount++;
	}
}

void convert_sidedefs(wadfile_t *wf, const char *map) {
	int size, i;
	sidedef_t *sdef = (sidedef_t *)safe_get_map_lump(wf, map, "SIDEDEFS", &size);

	for(i = 0; i < size / sizeof(sidedef_t); i++) {
		sidedef64_t *sdef64 = &sidedefs[sidedefcount];
		sdef64->x = sdef->x;
		sdef64->y = sdef->y;
		sdef64->sector = sdef->sector;
		sdef64->u_texture = hash_lump_name(sdef->u_texture);
		sdef64->l_texture = hash_lump_name(sdef->l_texture);
		sdef64->m_texture = hash_lump_name(sdef->m_texture);

		sdef++, sidedefcount++;
	}
}

void convert_things(wadfile_t *wf, const char *map) {
	int size, i;
	things_t *thing = (things_t *)safe_get_map_lump(wf, map, "THINGS", &size);

	for(i = 0; i < size / sizeof(things_t); i++) {
		things64_t *t64 = &things[thingcount];
		t64->x = thing->x;
		t64->y = thing->y;
		t64->angle = thing->angle;
		t64->type = thing->type; // TODO: actual conversion
		t64->flags = thing->flags; // TODO: actual conversion
		t64->z = t64->tid = 0; // TODO: is z relative to the floor or not?

		thing++, thingcount++;
	}
}

void addentry(int *pos, int length, const char *name, FILE *wadfile) {
	static char entryname8[8];

	putlong(*pos, wadfile);
	putlong(length, wadfile);
	*pos += length;
	strncpy(entryname8, name, 8);
	fwrite(entryname8, 8, 1, wadfile);
	fprintf(stderr, "Adding entry %s (%d bytes)\n", name, length);
}


int write_output(const char *map, const char *output) {
	FILE *outfile;
	int numentries, entrypos, reslength, i;

	outfile = fopen(output, "wb");
	if(!outfile) {
		perror(output);
		return -1;
	}

	/* ugh. libwad doesn't make this much easier. */
	fprintf(outfile, "PWAD");
	numentries = 14;
	putlong(numentries, outfile);
	reslength =
		vertexcount * sizeof(vertex64_t) +
		thingcount * sizeof(things64_t) +
		sectorcount * sizeof(sector64_t) +
		linedefcount * sizeof(linedef64_t) +
		sidedefcount * sizeof(sidedef64_t) +
		sizeof(wadinfo_t);
	putlong(reslength, outfile);

	for(i = 0; i < thingcount; i++)
		fwrite(&things[i], sizeof(things64_t), 1, outfile);

	for(i = 0; i < linedefcount; i++)
		fwrite(&linedefs[i], sizeof(linedef64_t), 1, outfile);

	for(i = 0; i < sidedefcount; i++)
		fwrite(&sidedefs[i], sizeof(sidedef64_t), 1, outfile);

	for(i = 0; i < vertexcount; i++)
		fwrite(&vertices[i], sizeof(vertex64_t), 1, outfile);

	for(i = 0; i < sectorcount; i++)
		fwrite(&sectors[i], sizeof(sector64_t), 1, outfile);

	entrypos = 12;
	addentry(&entrypos, 0, map, outfile);
	addentry(&entrypos, thingcount * sizeof(things64_t), "THINGS", outfile);
	addentry(&entrypos, linedefcount * sizeof(linedef64_t), "LINEDEFS", outfile);
	addentry(&entrypos, sidedefcount * sizeof(sidedef64_t), "SIDEDEFS", outfile);
	addentry(&entrypos, vertexcount * sizeof(vertex64_t), "VERTEXES", outfile);
	addentry(&entrypos, 0, "SEGS", outfile);
	addentry(&entrypos, 0, "SSECTORS", outfile);
	addentry(&entrypos, 0, "NODES", outfile);
	addentry(&entrypos, sectorcount * sizeof(sector64_t), "SECTORS", outfile);
	addentry(&entrypos, 0, "REJECT", outfile);
	addentry(&entrypos, 0, "BLOCKMAP", outfile);
	addentry(&entrypos, 0, "LEAFS", outfile);
	addentry(&entrypos, 0, "LIGHTS", outfile);
	addentry(&entrypos, 0, "MACROS", outfile);

	fclose(outfile);
	return 0;
}

int convert_map(const char *map, const char *input, const char *output) {
	wadfile_t *inputwf;

	inputwf = open_wad(fw_find_wad(input));
	if(!inputwf) return -1;

	convert_vertices(inputwf, map);
	convert_sectors(inputwf, map);
	convert_linedefs(inputwf, map);
	convert_sidedefs(inputwf, map);
	convert_things(inputwf, map);

	close_wad(inputwf);

	return write_output(map, output);
}

int main(int argc, char **argv) {
	const char *output = "conv.wad";
	const char *input;
	char map[10] = "MAP01";
	int converting_textures = 0;
	int result;

	progname = argv[0];

	if(argc < 3) usage("Not enough arguments");
	if(argc > 4) usage("Too many arguments");

	if(strcmp(argv[1], "-t") == 0) {
		converting_textures = 1;
		output = "doom2textures64.wad";
	} else {
		result = atoi(argv[1]);
		if(result < 1) usage("Invalid map number (should be 1-32)");
		snprintf(map, 8, "MAP%02d", result);
	}

	input = argv[2];
	if(argc == 4)
		output = argv[3];

	fprintf(stderr, "Converting %s in %s, result in %s\n",
			(converting_textures ? "textures" : map), input, output);

	if(converting_textures) {
		fprintf(stderr, "(textures not yet supported)\n");
		result = -1;
	} else {
		result = convert_map(map, input, output);
	}

	return result;
}
