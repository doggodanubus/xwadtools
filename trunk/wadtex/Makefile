INC = ../include
LIB = ../lib

CCFLAGS = $(CFLAGS) -I$(INC)
LFLAGS =  -L$(LIB)

wadtex: wadtex.o
	$(CC) $(LFLAGS) -o $@ wadtex.o -lwad -lfindwad

wadtex.o: wadtex.c $(INC)/sysdep.h $(INC)/strfunc.h $(INC)/wad.h \
	$(INC)/lump_dir.h $(INC)/wadfile.h $(LIB)/libwad.a $(LIB)/libfindwad.a

$(LIB)/libwad.a:
	cd ../lib; make

clean:
	rm -f *.o wadtex wadtex.exe

allclean:
	make clean; cd ../lib; make clean

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@
