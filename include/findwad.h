
/* findwad.h - API for finding WAD files in a uniform manner.

	All functions search the current directory, then $DOOMWADDIR in the
	environment if set, then DEFAULT_WAD_DIR

	The *_iwad(void) functions use DOOMWAD in the environment (set
	to e.g. "doom" or "doom.wad"). If not set, defaults to "doom2".
	If the ".wad" extender is missing, it's added.

	None of this is thread-safe, but xwadtools doesn't use threads.
 */

#ifndef FINDWAD_H
#define FINDWAD_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DEFAULT_WAD_DIR "/usr/share/games/doom"

/* return filename of IWAD file, or NULL on failure */
const char *fw_find_iwad(void);

/* return filename of given WAD file, or the original filename on failure
	We don't return NULL, so that the calling code can try to fopen()
	our result (it will fail, and the caller can check for fopen()
	failure normally).
 */
const char *fw_find_wad(const char *wad);

/* return a read-only file pointer to the IWAD, or NULL on failure */
FILE *fw_fopen_iwad(void);

/* return a file pointer to the given WAD, or NULL on failure */
FILE *fw_fopen_wad(const char *wad, const char *mode);

/* return a filehandle to the IWAD, or -1 on failure */
int fw_open_iwad(void);

/* return a filehandle to the given WAD, or -1 on failure */
int fw_open_wad(const char *wad, int flags, mode_t mode);

/* return true if given WAD exists, otherwise false */
int fw_wad_exists(const char *wad);

#endif
