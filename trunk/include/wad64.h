#ifndef WAD64_H
#define WAD64_H

#include <inttypes.h>

typedef struct {
	uint16_t     x_frac;         /* x coordinate of vertex */
	int16_t      x;              /* x coordinate of vertex */
	uint16_t     y_frac;         /* y coordinate of vertex */
	int16_t      y;              /* y coordinate of vertex */
} vertex64_t; /* In Doom64 these are 16.16 fixed-point */

typedef struct {
	int16_t      x;         /* x coordinate of thing */
	int16_t      y;         /* y coordinate of thing */
	int16_t      z;         /* you guess? */
	int16_t      angle;     /* angle thing faces */
	int16_t      type;      /* type of thing */
	int16_t      flags;     /* flags */
	int16_t      tid;       /* thing id (for scripting) */
} things64_t;

typedef struct {
	int16_t      f_height;      /* floor height in sector */
	int16_t      c_height;      /* ceiling height in sector */
	uint16_t      f_index;       /* index of floor flat */
	uint16_t      c_index;       /* index of ceiling flat */
	// unsigned char color_index[10];  /* color table lookup index */
	uint16_t color_index[5]; /* color indices for ceil/floor/thing/walls/??? */
	uint16_t      type;          /* sector special type */
	uint16_t      tag;           /* tag number */
	uint16_t      flags;         /* flags */
} sector64_t;

typedef struct {
	int16_t      v_from;       /* from vertex */
	int16_t      v_to;         /* to vertex */
	uint32_t     flags;        /* flags */
	uint16_t     type;       /* type + special flags */
	int16_t      tag;          /* tag */
	int16_t      r_side;       /* number of right sidedef */
	int16_t      l_side;       /* number of left sidedef */
} linedef64_t;

typedef struct {
	int16_t    x;         /* x offset for texture */
	int16_t    y;         /* y offset for texture */
	uint16_t   u_texture; /* index upper texture */
	uint16_t   l_texture; /* index lower texture */
	uint16_t   m_texture; /* index middle texture */
	uint16_t   sector;    /* no. sector facing the sdef */
} sidedef64_t;
#endif
