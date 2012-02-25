#include "findwad.h"

static char filename[PATH_MAX];

static int file_exists(const char *file) {
	struct stat statbuf;
	return (stat(file, &statbuf) == 0);
}

static const char *get_wad_name(const char *wad) {
	strcpy(filename, wad);
	if(!strstr(filename, ".wad")) {
		strcat(filename, ".wad");
	}
	return filename;
}

static const char *get_iwad_name(void) {
	const char *iwad = getenv("DOOMWAD");
	if(!iwad) iwad = "doom2";
	return get_wad_name(iwad);
}

static const char *_find_wad(const char *wad) {
	static char fullpath[PATH_MAX];
	char *doomwaddir = getenv("DOOMWADDIR");
	(void)get_wad_name(wad);

	/* search the search path, for both plain and .wad versions */
	if(file_exists(wad))
		return wad;

	if(file_exists(filename))
		return filename;

	if(doomwaddir) {
		sprintf(fullpath, "%s/%s", doomwaddir, wad);
		if(file_exists(fullpath))
			return fullpath;

		sprintf(fullpath, "%s/%s", doomwaddir, filename);
		if(file_exists(fullpath))
			return fullpath;
	}

	sprintf(fullpath, "%s/%s", DEFAULT_WAD_DIR, wad);
	if(file_exists(fullpath))
		return fullpath;

	sprintf(fullpath, "%s/%s", DEFAULT_WAD_DIR, filename);
	if(file_exists(fullpath))
		return fullpath;

	return NULL;
}

/* return filename of IWAD file if found, or NULL on failure */
const char *fw_find_iwad(void) {
	return _find_wad(get_iwad_name());
}

/* return filename of given WAD file, or the original filename on failure */
const char *fw_find_wad(const char *wad) {
	const char *got = _find_wad(wad);
	if(got)
		fprintf(stderr, "looked for wad '%s', found '%s'\n", wad, got);
	else
		fprintf(stderr, "failed to find wad '%s' in search path\n", wad);
	return got ? got : wad;
}


/* return a read-only file pointer to the IWAD, or NULL on failure */
FILE *fw_fopen_iwad(void) {
	const char *fn = fw_find_iwad();
	if(fn)
		return fopen(fn, "rb");
	return NULL;
}

/* return a file pointer to the given WAD, or NULL on failure */
FILE *fw_fopen_wad(const char *wad, const char *mode) {
	const char *fn = fw_find_wad(wad);
	if(fn)
		return fopen(fn, mode);
	return NULL;
}

/* return a filehandle to the IWAD, or -1 on failure */
int fw_open_iwad(void) {
	const char *fn = fw_find_wad(fw_find_iwad());
	if(fn)
		return open(fn, O_RDONLY);
	return -1;
}

/* return a filehandle to the given WAD, or -1 on failure */
int fw_open_wad(const char *wad, int flags, mode_t mode) {
	const char *fn = fw_find_wad(wad);
	if(fn)
		return open(fn, flags, mode);
	return -1;
}

/* return true if given WAD exists, otherwise false */
int fw_wad_exists(const char *wad) {
	return file_exists(wad) || file_exists(get_wad_name(wad));
}

#ifdef TESTMAIN
// gcc -o test -Wall -DTESTMAIN -I../include findwad.c
// strace -eopen,stat ./test <arg>
int main(int argc, char **argv) {

	/*
	if(argc == 1)
		fprintf(stderr, "%s\n", fw_find_iwad());
	else
		fprintf(stderr, "%s\n", fw_find_wad(argv[1]));
	*/

	/*
	FILE *fh = fw_fopen_iwad();
	if(!fh) {
		fprintf(stderr, "failed to fw_fopen_iwad()\n");
	} else {
		fprintf(stderr, "fw_fopen_iwad() OK\n");
	}
	*/

	int fd = fw_open_wad(argv[1], O_RDONLY, 0);
	if(fd < 0) {
		fprintf(stderr, "failed to fw_open_wad()\n");
	} else {
		fprintf(stderr, "fw_open_wad() fh==%d\n", fd);
	}

	return 0;
}
#endif

