/************************************************************************/
/*      Copyright (C) 1998, 1999 by Udo Munk (munkudo@aol.com)          */
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
 *      Tool to decompile a level map in a WAD file
 *      This version is modified for doom64ex use
 *      Note that MAPxx lumps in doom64.wad are really IWADs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

#include "sysdep.h"
#include "wad.h"
#include "lump_dir.h"
#include "wadfile.h"
#include "wad64.h"

#define VERSION "1.2.64"

int	verbose;

void usage(char *name, char *option) {
	if (option)
		fprintf(stderr, "%s: Unknown option: %s\n", name, option);
	else
		fprintf(stderr, "%s: Missing arguments\n", name);
	fprintf(stderr, "Usage: %s [-v] [-g game] mapname wadfile mapfile\n", name);
	fprintf(stderr, "\t-v: verbose output\n");
	fprintf(stderr, "\t-g: game name, Doom, Doom2, Hexen...\n");
	exit(1);
}

void decompile_vertices(char *map, wadfile_t *wf, FILE *fp) {
	void		*vertices;
	vertex64_t	*v;
	int		size;
	int		i;

	if (verbose)
		printf("Decompiling vertices...\n");

	/* get the lump with the vertices for the map */
	if ((vertices =
		get_map_lump(wf, map, "VERTEXES", &size)) == (void *)0) {
		fprintf(stderr, "can't find VERTEXES lump for %s\n", map);
		exit(1);
	}
	
	/* write vertices start marker */
	fprintf(fp, " VERTEXES_START\n");

	/* loop over all vertices in the lump and decompile */
	v = (vertex64_t *) vertices;
	for (i = 0; i < size / sizeof(vertex64_t); i++) {
		swapint(&v->x);
		swapint(&v->y);
		swapint(&v->x_frac);
		swapint(&v->y_frac);
		fprintf(fp, "  V%d : %d %d %d %d\n", i, v->x, v->x_frac, v->y, v->y_frac);
		v++;
	}

	/* write vertices end marker */
	fprintf(fp, " VERTEXES_END\n\n");

	/* free memory */
	free(vertices);
}

void decompile_sectors(char *map, wadfile_t *wf, FILE *fp) {
	void		*sectors;
	sector64_t	*s;
	int		size;
	int		i;

	if (verbose)
		printf("Decompiling sectors...\n");

	/* get the lump with the sectors for the map */
	if ((sectors = get_map_lump(wf, map, "SECTORS", &size)) == (void *)0) {
		fprintf(stderr, "can't find SECTORS lump for %s\n", map);
		exit(1);
	}

	/*
	fprintf(stderr, "size==%d, sizeof(sector64_t)==%d, %d elements, %d remainder\n",
			size, sizeof(sector64_t), size / sizeof(sector64_t), size % sizeof(sector64_t));
			*/

	/* write sectors start marker */
	fprintf(fp, " SECTORS_START\n");

	/* loop over all sectors in the lump and decompile */
	s = (sector64_t *) sectors;
	for (i = 0; i < size / sizeof(sector64_t); i++) {
		int j;
		swapint(&s->f_height);
		swapint(&s->c_height);
		swapint(&s->f_index);
		swapint(&s->c_index);
		swapint(&s->type);
		swapint(&s->tag);
		swapint(&s->flags);
		fprintf(fp, "  S%d : %d %d", i, s->f_height, s->c_height);
		fprintf(fp, " %d %d", s->f_index, s->c_index);
		fprintf(fp, " %d %d %d", s->type, s->tag, s->flags);
		for(j=0; j<10; j++)
			fprintf(fp, " %02x", s->color_index[j]);
		fprintf(fp, "\n");
		s++;
	}

	/* write sectors end marker */
	fprintf(fp, " SECTORS_END\n\n");

	/* free memory */
	free(sectors);
}

void decompile_linedefs(char *map, wadfile_t *wf, FILE *fp) {
	void		*lines;
	void		*sdefs;
	linedef64_t	*l1;
	sidedef64_t	*s;
	int		size;
	int		size_sd;
	int		i;

	if (verbose)
		printf("Decompiling linedefs...\n");

	/* get the lump with the linedefs for the map */
	if ((lines = get_map_lump(wf, map, "LINEDEFS", &size)) == (void *)0) {
		fprintf(stderr, "can't find LINEDEFS lump for %s\n", map);
		exit(1);
	}

	/* and we need the sidedefs too... */
	if ((sdefs = get_map_lump(wf, map, "SIDEDEFS", &size_sd)) == (void *)0) {
		fprintf(stderr, "can't find SIDEDEFS lump for %s\n", map);
		exit(1);
	}

	/* 14 sep 99 Oliver Kraus */
	/* convert sidedefs before the linedef loop */
	/* this will fix a bug in the sparc port */

#ifdef BIGEND        
	s = (sidedef64_t *)sdefs;
	for (i = 0; i < size_sd/sizeof(sidedef64_t); i++, s++ )
	{
		swapint(&s->x);
		swapint(&s->y);
		swapint(&s->u_texture);
		swapint(&s->m_texture);
		swapint(&s->l_texture);
		swapint(&s->sector);
	}
#endif 

	/* write linedefs start marker */
	fprintf(fp, " LINEDEFS_START\n");

	/* loop over all linedefs in the lump and decompile */
	l1 = (linedef64_t *) lines;
	for (i = 0; i < size / sizeof(linedef64_t); i++, l1++) {

		/* the linedef self */
		swapint(&l1->v_from);
		swapint(&l1->v_to);
		swaplong(&l1->flags);
		// swapint(&l1->sflags);
		swapint(&l1->type);
		swapint(&l1->tag);
		swapint(&l1->r_side);
		swapint(&l1->l_side);
		fprintf(fp, "  V%d V%d : %d %d %d\n", l1->v_from, l1->v_to,
				l1->flags, l1->type, l1->tag);

		/* right sidedef */
		s = (sidedef64_t *)sdefs + l1->r_side;
		/* do NOT swap sidedef values here
			swapint(&s->x);
			swapint(&s->y);
			swapint(&s->sector);
		 */
		fprintf(fp, "   S%d %d %d", s->sector, s->x, s->y);
		fprintf(fp, " %d", s->u_texture);
		fprintf(fp, " %d", s->l_texture);
		fprintf(fp, " %d", s->m_texture);

		/* left sidedef */
		if (l1->l_side == -1)
			fprintf(fp, "   -\n");
		else {
			s = (sidedef64_t *)sdefs + l1->l_side;
			/* do NOT swap sidedef values here
				swapint(&s->x);
				swapint(&s->y);
				swapint(&s->sector);
			 */
			fprintf(fp, "   S%d %d %d", s->sector, s->x, s->y);
			fprintf(fp, " %d", s->u_texture);
			fprintf(fp, " %d", s->l_texture);
			fprintf(fp, " %d\n", s->m_texture);
		}
	}

	/* write linedefs end marker */
	fprintf(fp, " LINEDEFS_END\n\n");

	/* free memory */
	free(lines);
	free(sdefs);
}

void decompile_things(char *map, wadfile_t *wf, FILE *fp) {
	void		*things;
	things64_t	*t1;
	int		size;
	int		i;

	if (verbose)
		printf("Decompiling things...\n");

	/* get the lump with the things for the map */
	if ((things = get_map_lump(wf, map, "THINGS", &size)) == (void *)0) {
		fprintf(stderr, "can't find THINGS lump for %s\n", map);
		exit(1);
	}

	/* write things start marker */
	fprintf(fp, " THINGS_START\n");

	/* loop over all things in the lump and decompile */
	t1 = (things64_t *) things;
	for (i = 0; i < size / sizeof(things64_t); i++, t1++) {
		swapint(&t1->x);
		swapint(&t1->y);
		swapint(&t1->z);
		swapint(&t1->angle);
		swapint(&t1->type);
		swapint(&t1->flags);
		swapint(&t1->tid);
		fprintf(fp, "  %d : %d %d %d %d %d %d\n", t1->type, t1->x, t1->y,
				t1->z, t1->angle, t1->flags, t1->tid);
	}

	/* write things end marker */
	fprintf(fp, " THINGS_END\n\n");

	/* free memory */
	free(things);
}

void decompile_lights(char *map, wadfile_t *wf, FILE *fp) {
	unsigned char *lights;
	int i;
	int		size;

	if (verbose)
		printf("Decompiling lights...\n");

	if ((lights = (unsigned char *)get_map_lump(wf, map, "LIGHTS", &size)) == (unsigned char *)0) {
		fprintf(stderr, "can't find LIGHTS lump for %s\n", map);
		exit(1);
	}

	fprintf(fp, " LIGHTS_START\n");
	for(i = 0; i < size; i += 6) {
		fprintf(fp, "  %u %u %u %u %u %u\n",
				(unsigned int)lights[i],
				(unsigned int)lights[i+1],
				(unsigned int)lights[i+2],
				(unsigned int)lights[i+3],
				(unsigned int)lights[i+4],
				(unsigned int)lights[i+5]);
	}

	fprintf(fp, " LIGHTS_END\n");
}

void decompile_macros(char *map, wadfile_t *wf, FILE *fp) {
	unsigned char *macros;
	int i, j = 0;
	int		size;

	if (verbose)
		printf("Decompiling macros...\n");

	if ((macros = (unsigned char *)get_map_lump(wf, map, "MACROS", &size)) == (unsigned char *)0) {
		fprintf(stderr, "can't find MACROS lump for %s\n", map);
		exit(1);
	}

	fprintf(fp, " MACROS_START");
	for(i=0; i< size; i++) {
		j %= 8;
		if(j == 0)
			fprintf(fp, "\n ");
		fprintf(fp, " %u", (unsigned int)macros[i]);
		j++;
	}

	fprintf(fp, "\n MACROS_END\n");
}

#define checkstructsize(type, size) \
	if(sizeof(type) != size) { \
		fprintf(stderr, "sizeof(%s) is %d, should be %d\n", #type, sizeof(type), size); \
		exit(1); \
	}

int main(int argc, char** argv) {
	char		*s;
	char		*program;
	wadfile_t	*wf;
	FILE		*fp;
	char		*game = "Doom64EX";
	char *mapname;

	checkstructsize(things64_t, 14);
	checkstructsize(vertex64_t, 8);
	checkstructsize(sector64_t, 24);
	checkstructsize(linedef64_t, 16);
	checkstructsize(sidedef64_t, 12);

	/* save program name for usage() */
	program = *argv;

	/* process options */
	while ((--argc > 0) && (**++argv == '-')) {
		for (s = *argv+1; *s != '\0'; s++) {
			switch (*s) {
			case 'v':
				verbose++;
				break;
			case 'g':
				argc--;
				argv++;
				game = *argv;
				break;
			default:
				usage(program, --s);
			}
		}
	}

	if (verbose)
		printf("%s version %s\n\n", program, VERSION);

	/* we need exactely 3 arguments */
	if (argc != 3)
		usage(program, NULL);

	/* try to open WAD file */
	if (verbose)
		printf("Opening WAD file %s...\n", *(argv+1));
	wf = open_wad(*(argv+1));

	/* try to open MAP file */
	if (verbose)
		printf("Opening map file %s...\n", *(argv+2));
	if ((fp = fopen(*(argv+2), "w")) == NULL) {
		perror("can't open map file for writing");
		exit(1);
	}

	/* write comment and level start marker into map file */
	fprintf(fp, "# This map was decompiled with wadldc64\n\n");

	mapname = *argv+3;
	if(*mapname == '0') mapname++;
	fprintf(fp, "LEVEL_START 0 %s 64 %s\n\n", mapname, game);

	/* decompile the sections we need */
	decompile_vertices(*argv, wf, fp);
	decompile_sectors(*argv, wf, fp);
	decompile_linedefs(*argv, wf, fp);
	decompile_things(*argv, wf, fp);
	decompile_lights(*argv, wf, fp);
	decompile_macros(*argv, wf, fp);

	/* write level end marker into map file */
	fprintf(fp, "LEVEL_END\n");

	/* close files */
	close_wad(wf);
	fclose(fp);

	/* and done */
	return 0;
}
