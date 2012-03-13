/* wadlc64.c, modified version of wadlc.c that supports Doom64EX (only) */

/* WADLC.C */
/* A simple program to make custom Doom levels.
   Temporary beta version only - no support guaranteed!
   Author: Stefan Gustavson (stefang@isy.liu.se) 1994
   The entries SEGS, SSECTORS, NODES, REJECT and BLOCKMAP
   are left empty, but they are created in order not to
   confuse level editors and the program WAD_DWD used as
   a preprocessor to IDBSP.
*/

/*
 * AYM 1999-05-23 : Made wadlc pipeable (input file "-" means
 * stdin and output file "-" means stdout).
 *
 * UM 1999-06-26
 * - raised size of the thing, linedef, ... arrays to max possible size
 *
 * UM 1999-06-28
 * - fixed warning from GNU C/EGCS
 *
 * UM 1999-06-29
 * - reformated a bit, to be able to work better with the source
 * - use wad structures from wad.h in the include directory, removed
 *   the unused ones from wadlc.h
 * - replaced all magic number voodoo with sizeof(some structure) logic
 * - then added support for Hexen map type and if so, write Hexen wad
 *   with empty BEHAVIOR lump
 *
 * UM 1999-07-02
 * - read and ignore the game type in LEVEL_START
 *
 * UM 1999-07-08
 * - a BEHAVIOR lump with a size of 0 bytes crashes Hexen engines. Write
 *   one which has the memory footprint of an empty compiled script source.
 *
 * AYM 2004-01-29
 * - removed arbitrary limits on the object counts (32766 vertices,
 *   8192 sectors, 32766 sidedefs, 16383 linedefs)
 * - added missing include <stdlib.h>
 * - compile large levels faster by noticing when object names contain
 *   the object number (for a 32,768-linedef test level, the time went
 *   down from 100s to 2s).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "sysdep.h"
#include "wad.h"
#include "wad64.h"
#include "wadlc64.h"

static int quiet = 0;  /* No messages to stdout AT ALL */

void addentry(int *pos, int length, const char *name, FILE *wadfile)
{
  static char entryname8[8];

  putlong(*pos, wadfile);
  putlong(length, wadfile);
  *pos += length;
  strncpy(entryname8, name, 8);
  fwrite(entryname8, 8, 1, wadfile);
  if (!quiet)
    printf("Adding entry %s (%d bytes)\n", name, length);
}

int findmatch(const char *name, const char *table, int shortcut,
    int numentries, int length)
{
  int i = 0;

  /* KLUDGE to speed things up, notice when names contain the object
   * number and avoid scanning the whole array. For a more general fix,
   * use a hash or a sorted array.
   */
  if (shortcut)
  {
    const char *p;
    long num = 0;

    /* Skip over the non-numeric prefix */
    for (p = name; *p != '\0' && (*p < '0' || *p > '9'); p++)
      ;
    for (; *p >= '0' && *p <= '9'; p++)
      num = 10 * num + *p - '0';
    if (num >= numentries)
    {
      fprintf(stderr,"Bad object number: %s/%d\n", name, numentries);
      exit(-1);
    }
    return num;
  }

  while (strncmp(name, table, 8) && (i < numentries))
  {
    i++;
    table += length;
  }
  if (i == numentries)
  {
    fprintf(stderr,"Couldn't match name: %s\n", name);
    exit(-1);
  }
  return(i);
}

void allowcomment(FILE *infile)
{
  while (ungetc(getc(infile), infile) == '#')
    while (getc(infile) != '\n');
}

int main(int argc, char *argv[]) {
  FILE      *infile, *wadfile;
  char      keyword[20];
  char      vertexname[20], sectorname[20];
  char      fromvertexname[20], tovertexname[20];
  int      ox, oy, x, y, z, xf, yf;
  int      numentries, reslength;
  int      i;
  int      episode, level, maptype = 0;
  char      gametype[20];
  int      lastitem;
  int      floorh, ceilingh, brightness, special, tag, type, attrs, angle, flags;
  int      arg1, arg2, arg3, arg4, arg5;
  int       floort, ceilingt;
  int      uppert, lowert, normalt;
  char      thingname[20];
  int      tid;
  int      fromvertexindex, tovertexindex;
  int      rightsidedefindex, leftsidedefindex;
  int      sectorindex;
  char      behavior[16] = { 'A', 'C', 'S', '\0', 0x08, '\0', '\0', '\0',
             '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
                };

  w_vertex64_t   vertices[32768];
  w_sector64_t   sectors[32768];
  sidedef64_t  sidedefs[32768];
  linedef64_t  linedefs[32768];
  things64_t   things[32768];
  char lights[100000], macros[100000];
  int lightbytes = 0, macrobytes = 0;
  int      numvertices = 0, numsectors = 0, numsidedefs = 0,
			  numlinedefs = 0, numthings = 0;
  int      vertexshortcut = 1;
  int      sectorshortcut = 1;

  char      entryname[9];
  int      entrypos;

  if (argc != 3) {
    fprintf(stderr,"Usage: %s infile outfile\n", argv[0]);
    exit(-1);
  }
  if (!strcmp(argv[1], "-"))
    infile = stdin;
  else
    infile = fopen(argv[1], "r");
  if (infile == NULL) {
    fprintf(stderr,"Unable to open input file %s\n", argv[1]);
    exit(-1);
  }
  if (!strcmp(argv[2], "-"))
    wadfile = stdout;
  else
    wadfile = fopen(argv[2], "wb");
  if (wadfile == NULL) {
    fprintf(stderr,"Unable to create output file %s\n", argv[2]);
    exit(-1);
  }
  if (wadfile == stdout)
    quiet = 1;
  allowcomment(infile);
  fscanf(infile, " %s ", keyword);

  if (!strcmp(keyword, "LEVEL_START")) {
    fscanf(infile, " %d %d %d %s ", &episode, &level, &maptype, &gametype[0]);
    if(maptype != 64) {
       fprintf(stderr, "map file is not for Doom64EX\n");
       exit(-1);
    }
    allowcomment(infile);
    fscanf(infile, " %s ", keyword);
  } else {
    fprintf(stderr,"LEVEL_START marker missing!\n");
    exit(-1);
  }

  if (!strcmp(keyword, "VERTEXES_START") |
		  !strcmp(keyword, "VERTICES_START"))
  {
	  /* Process vertices until VERTEXES_END is found */
	  lastitem = 0;
	  numvertices = 0;
	  while (!lastitem) {
		  allowcomment(infile);
		  fscanf(infile, " %s ", vertexname);
		  if (!strcmp(vertexname, "VERTEXES_END") |
				  !strcmp(vertexname, "VERTICES_END"))
			  lastitem = 1;
		  else {
			  /* KLUDGE to speed things up, notice when vertex names contain
				* the vertex number and avoid the long scan of vertices[].
				*/
			  {
				  const char *p;
				  long num = 0;
				  int digits = 0;

				  /* Skip over the non-numeric prefix */
				  for (p = vertexname; *p != '\0' && (*p < '0' || *p > '9'); p++)
					  ;
				  for (; *p >= '0' && *p <= '9'; p++) {
					  num = 10 * num + *p - '0';
					  digits++;
				  }
				  if (digits == 0 || num != numvertices)
					  vertexshortcut = 0;
			  }
			  fscanf(infile, " : %d %d %d %d ", &x, &xf, &y, &yf);
			  allowcomment(infile);
			  vertices[numvertices].x = x;
			  vertices[numvertices].y = y;
			  vertices[numvertices].x_frac = xf;
			  vertices[numvertices].y_frac = yf;
			  strncpy(vertices[numvertices].name, vertexname, 8);
			  numvertices++;
		  }
	  }
	  fscanf(infile, " %s ", keyword);
  } else {
	  fprintf(stderr,"VERTEXES_START marker missing!\n");
	  exit(-1);
  }

  if (!strcmp(keyword, "SECTORS_START")) {
	  int i;
	  uint32_t flags;
	  uint16_t sflags;
	  /* Process sectors until SECTORS_END is found */
	  lastitem = 0;
	  numsectors = 0;
	  while (!lastitem) {
		  allowcomment(infile);
		  fscanf(infile, " %s ", sectorname);
		  if (!strcmp(sectorname, "SECTORS_END"))
			  lastitem = 1;
		  else {
			  fscanf(infile, " : %d %d %d %d %d %d %d ", &floorh, &ceilingh,
					  &floort, &ceilingt, &type, &tag, &flags);
			  /* KLUDGE to speed things up, notice when sector names contain
				* the sector number and avoid the long scan of sectors[].
				*/
			  {
				  const char *p;
				  long num = 0;
				  int digits = 0;

				  /* Skip over the non-numeric prefix */
				  for (p = sectorname; *p != '\0' && (*p < '0' || *p > '9'); p++)
					  ;
				  for (; *p >= '0' && *p <= '9'; p++)
				  {
					  num = 10 * num + *p - '0';
					  digits++;
				  }
				  if (digits == 0 || num != numsectors)
					  sectorshortcut = 0;
			  }
			  allowcomment(infile);
			  sectors[numsectors].s.f_height = floorh;
			  sectors[numsectors].s.c_height = ceilingh;
			  sectors[numsectors].s.type = type;
			  sectors[numsectors].s.flags = flags;
			  sectors[numsectors].s.tag = tag;
			  strncpy(sectors[numsectors].name, sectorname, 8);
			  sectors[numsectors].s.f_index = floort;
			  sectors[numsectors].s.c_index = ceilingt;

			  for(i=0; i<10; i++) {
				  int got;
				  fscanf(infile, " %x ", &got);
				  sectors[numsectors].s.color_index[i] = got & 0xff;
			  }

			  numsectors++;
		  }
	  }
	  fscanf(infile, " %s ", keyword);
  } else {
	  fprintf(stderr,"SECTORS_START marker missing!\n");
	  exit(-1);
  }

  if (!strcmp(keyword, "LINEDEFS_START")) {
	  uint32_t flags;
	  uint16_t sflags;

	  /* Process lines until LINEDEFS_END is found */
	  lastitem = 0;
	  numlinedefs = 0;
	  while (!lastitem) {
		  allowcomment(infile);
		  fscanf(infile, " %s ", fromvertexname);
		  if (!strcmp(fromvertexname, "LINEDEFS_END"))
			  lastitem = 1;
		  else {
			  fscanf(infile, " %s : %u %hu %d ", tovertexname, &flags, &type, &tag);
			  allowcomment(infile);
			  fromvertexindex = findmatch(fromvertexname, (char*)vertices,
					  vertexshortcut, numvertices,
					  sizeof(w_vertex64_t));
			  tovertexindex = findmatch(tovertexname, (char*)vertices,
					  vertexshortcut, numvertices,
					  sizeof(w_vertex64_t));

			  /* Read one or two SIDEDEFS */
			  fscanf(infile, " %s %d %d %d %d %d ", sectorname, &ox, &oy,
					  &uppert, &lowert, &normalt);
			  allowcomment(infile);
			  sectorindex = findmatch(sectorname, (char*)sectors, sectorshortcut,
					  numsectors, sizeof(w_sector64_t));
			  sidedefs[numsidedefs].sector = sectorindex;
			  sidedefs[numsidedefs].x = ox;
			  sidedefs[numsidedefs].y = oy;
			  sidedefs[numsidedefs].u_texture = uppert;
			  sidedefs[numsidedefs].l_texture = lowert;
			  sidedefs[numsidedefs].m_texture = normalt;
			  rightsidedefindex = numsidedefs;
			  numsidedefs++;
			  fscanf(infile, "%s", sectorname);
			  if (!strcmp(sectorname, "-")) {
				  allowcomment(infile);
				  leftsidedefindex = -1;
			  } else {
				  fscanf(infile, " %d %d %u %u %u ", &ox, &oy, &uppert, &lowert, &normalt);
				  allowcomment(infile);
				  sectorindex = findmatch(sectorname, (char*)sectors, sectorshortcut,
						  numsectors, sizeof(w_sector64_t));
				  sidedefs[numsidedefs].sector = sectorindex;
				  sidedefs[numsidedefs].x = ox;
				  sidedefs[numsidedefs].y = oy;
				  sidedefs[numsidedefs].u_texture = uppert;
				  sidedefs[numsidedefs].l_texture = lowert;
				  sidedefs[numsidedefs].m_texture = normalt;
				  leftsidedefindex = numsidedefs;
				  numsidedefs++;
			  }
			  linedefs[numlinedefs].v_from = fromvertexindex;
			  linedefs[numlinedefs].v_to = tovertexindex;
			  linedefs[numlinedefs].flags = flags;
			  linedefs[numlinedefs].type = sflags;
			  linedefs[numlinedefs].tag = tag;
			  linedefs[numlinedefs].r_side = rightsidedefindex;
			  linedefs[numlinedefs].l_side = leftsidedefindex;
			  numlinedefs++;
		  }
	  }
	  fscanf(infile, " %s ", keyword);
  } else {
    fprintf(stderr,"LINEDEFS_START marker missing!\n");
    exit(-1);
  }

  if (!strcmp(keyword, "THINGS_START")) {
	  /* Process things until THINGS_END is found */
	  lastitem = 0;
	  numthings = 0;
	  while (!lastitem) {
		  allowcomment(infile);
		  fscanf(infile, " %s ", thingname);
		  if (!strcmp(thingname, "THINGS_END"))
			  lastitem = 1;
		  else {
			  sscanf(thingname, "%hd", &(things[numthings].type));
			  fscanf(infile, " : %hd %hd %hd %hd %hd %hd",
					  &(things[numthings].x),
					  &(things[numthings].y),
					  &(things[numthings].z),
					  &(things[numthings].angle),
					  &(things[numthings].flags),
					  &(things[numthings].tid));
			  allowcomment(infile);
			  numthings++;
		  }
	  }
	  fscanf(infile, " %s ", keyword);
  } else {
	  fprintf(stderr,"THINGS_START marker missing!\n");
	  exit(-1);
  }

  if (!strcmp(keyword, "LIGHTS_START")) {
	  lightbytes = 0;
	  fscanf(infile, " %s ", keyword);
	  while(strcmp(keyword, "LIGHTS_END")) {
		  unsigned int got;
		  sscanf(keyword, " %d ", &got);
		  lights[lightbytes++] = (unsigned char)(got & 0xff);
		  fscanf(infile, " %s ", keyword);
	  }
  } else {
	  fprintf(stderr,"LIGHTS_START marker missing!\n");
	  exit(-1);
  }

  fscanf(infile, " %s ", keyword);
  if (!strcmp(keyword, "MACROS_START")) {
	  macrobytes = 0;
	  fscanf(infile, " %s ", keyword);
	  while(strcmp(keyword, "MACROS_END")) {
		  unsigned int got;
		  sscanf(keyword, " %d ", &got);
		  macros[macrobytes++] = (unsigned char)(got & 0xff);
		  fscanf(infile, " %s ", keyword);
	  }
  } else {
	  fprintf(stderr,"MACROS_START marker missing!\n");
	  exit(-1);
  }


  if (infile != stdin)
	  fclose(infile);

  /* Concatenate all the data into the final PWAD file */

  /* Header */
  fprintf(wadfile,"PWAD");

  /* Doom64 map type */
  numentries = 14;
  putlong(numentries, wadfile);
  reslength = numthings * sizeof(things64_t) +
	  numlinedefs * sizeof(linedef64_t) +
	  numsidedefs * sizeof(sidedef64_t) +
	  numvertices * sizeof(vertex64_t) +
	  numsectors * sizeof(sector64_t) +
	  lightbytes +
	  macrobytes +
	  sizeof(wadinfo_t);
  putlong(reslength, wadfile);

  /* ExMy - start at position 12 (zero length entry) */

  /* THINGS - start at position 12 */
  for (i = 0; i < numthings; i++) {
      /* Doom map type */
      putshort(things[i].x, wadfile);
      putshort(things[i].y, wadfile);
      putshort(things[i].z, wadfile);
      putshort(things[i].angle, wadfile);
      putshort(things[i].type, wadfile);
      putshort(things[i].flags, wadfile);
      putshort(things[i].tid, wadfile);
  }

  /* LINEDEFS - start at position 12 + numthings * sizeof(things_t) */
  for (i = 0; i < numlinedefs; i++) {
	  /* Doom map type */
	  putshort(linedefs[i].v_from, wadfile);
	  putshort(linedefs[i].v_to, wadfile);
	  putlong(linedefs[i].flags, wadfile);
	  putshort(linedefs[i].type, wadfile);
	  putshort(linedefs[i].tag, wadfile);
	  putshort(linedefs[i].r_side, wadfile);
	  putshort(linedefs[i].l_side, wadfile);
  }

  /* SIDEDEFS - start at position 12 + numthings * sizeof(things_t) +
   * numlinedefs * sizeof(linedef_t)
   */
  for (i = 0; i < numsidedefs; i++) {
    putshort(sidedefs[i].x, wadfile);
    putshort(sidedefs[i].y, wadfile);
    putshort(sidedefs[i].u_texture, wadfile);
    putshort(sidedefs[i].l_texture, wadfile);
    putshort(sidedefs[i].m_texture, wadfile);
    putshort(sidedefs[i].sector, wadfile);
  }

  /* VERTEXES - start at position 12 + numthings * sizeof(things_t) +
   * numlinedefs * sizeof(linedef_t) + numsidedefs * sizeof(sidedef_t)
   */
  for (i = 0; i < numvertices; i++) {
    putshort(vertices[i].x_frac, wadfile);
    putshort(vertices[i].x, wadfile);
    putshort(vertices[i].y_frac, wadfile);
    putshort(vertices[i].y, wadfile);
  }

  /* SECTORS - start at position 12 + numthings * sizeof(things_t) +
   * numlinedefs * sizeof(linedef_t) + numsidedefs * sizeof(sidedef_t) +
   * numvertices * sizeof(vertex_t)
   */
  for (i = 0; i < numsectors; i++) {
    putshort(sectors[i].s.f_height, wadfile);
    putshort(sectors[i].s.c_height, wadfile);
    putshort(sectors[i].s.f_index, wadfile);
    putshort(sectors[i].s.c_index, wadfile);
	 fwrite(sectors[i].s.color_index, 10, 1, wadfile);
    putshort(sectors[i].s.type, wadfile);
    putshort(sectors[i].s.tag, wadfile);
    putshort(sectors[i].s.flags, wadfile);
  }

  fwrite(lights, lightbytes, 1, wadfile);
  fwrite(macros, macrobytes, 1, wadfile);

  /* Now, write the main directory */
  entrypos = 12;
  if (episode > 0)
      sprintf(entryname, "E%1dM%1d", episode, level);
  else
      sprintf(entryname, "MAP%02d", level);
  addentry(&entrypos, 0,            entryname,  wadfile);
    addentry(&entrypos, numthings*sizeof(things64_t),   "THINGS",   wadfile);
    addentry(&entrypos, numlinedefs*sizeof(linedef64_t),   "LINEDEFS", wadfile);
  addentry(&entrypos, numsidedefs*sizeof(sidedef64_t),   "SIDEDEFS", wadfile);
  addentry(&entrypos, numvertices*sizeof(vertex64_t),   "VERTEXES", wadfile);
  addentry(&entrypos, 0,                       "SEGS",     wadfile);
  addentry(&entrypos, 0,                       "SSECTORS", wadfile);
  addentry(&entrypos, 0,                       "NODES",    wadfile);
  addentry(&entrypos, numsectors*sizeof(sector64_t),   "SECTORS",  wadfile);
  addentry(&entrypos, 0,                       "REJECT",   wadfile);
  addentry(&entrypos, 0,                       "BLOCKMAP", wadfile);
  addentry(&entrypos, 0,                       "LEAFS", wadfile);
  addentry(&entrypos, lightbytes,                       "LIGHTS", wadfile);
  addentry(&entrypos, macrobytes,                       "MACROS", wadfile);

  /* DONE! */
  if (wadfile != stdout)
    fclose(wadfile);
  return 0;
}
