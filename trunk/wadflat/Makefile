INC = ../include
LIB = ../lib

CCFLAGS = $(CFLAGS) -I$(INC)
LFLAGS =  -L$(LIB)

wadflat: wadflat.o
	$(CC) $(LFLAGS) -o $@ wadflat.o -lwad -lfindwad

wadflat.o: wadflat.c $(INC)/sysdep.h $(INC)/strfunc.h $(INC)/wad.h \
	$(INC)/lump_dir.h $(INC)/wadfile.h $(LIB)/libwad.a $(LIB)/libfindwad.a

$(LIB)/libwad.a:
	cd ../lib; make

clean:
	rm -f *.o wadflat wadflat.exe

allclean:
	make clean; cd ../lib; make clean

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@
