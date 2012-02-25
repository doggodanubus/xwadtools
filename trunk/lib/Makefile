AR = ar -ru

INC = ../include

CCFLAGS = $(CFLAGS) -I$(INC)

all: libwad.a libfindwad.a

ifneq ($(HAVE_FNMATCH),yes)
EXTRAOBJ=obsd_fnmatch.o
endif

libwad.a: lump_dir.o lump_cpy.o wadfile.o sysdep.o swapfunc.o \
	scriplib.o cmdlib.o palettes.o strfunc.o mygetopt.o $(EXTRAOBJ)
	$(AR) $@ $?

libfindwad.a: findwad.o
	$(AR) $@ $?

findwad.o:	findwad.c $(INC)/findwad.h
lump_dir.o:	lump_dir.c $(INC)/wad.h $(INC)/lump_dir.h
lump_cpy.o:	lump_cpy.c $(INC)/sysdep.h $(INC)/lump_cpy.h
wadfile.o:	wadfile.c $(INC)/sysdep.h $(INC)/wad.h $(INC)/lump_dir.h \
		$(INC)/wadfile.h
sysdep.o:	sysdep.c
scriplib.o:	scriplib.c $(INC)/cmdlib.h $(INC)/scriplib.h
cmdlib.o:	cmdlib.c $(INC)/sysdep.h $(INC)/strfunc.h $(INC)/cmdlib.h
strfunc.o:	strfunc.c $(INC)/strfunc.h
mygetopt.o:	mygetopt.c $(INC)/mygetopt.h
palettes.o:	palettes.c
swapfunc.o:	swapfunc.c $(INC)/sysdep.h $(INC)/wad.h
obsd_fnmatch.o:	obsd_fnmatch.c $(INC)/obsd_fnmatch.h $(INC)/charclass.h

clean:
	rm -f *.o libwad.a libfindwad.a

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@
