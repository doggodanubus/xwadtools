/* WADLC.H - some data structures for WADLC.C */

typedef struct
{
  char   name[8];
  int16_t x, y;
  uint16_t x_frac, y_frac;
} w_vertex64_t;

typedef struct
{
  char   name[8];
  sector64_t s;
} w_sector64_t;
