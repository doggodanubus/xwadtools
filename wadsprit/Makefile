INC = ../include
LIB = ../lib

CCFLAGS = $(CFLAGS) -I$(INC)
LFLAGS =  -L$(LIB)

wadsprit: wadsprit.o
	$(CC) $(LFLAGS) -o $@ wadsprit.o -lwad -lfindwad

wadsprit: wadsprit.c $(INC)/sysdep.h $(INC)/strfunc.h $(INC)/wad.h \
	$(INC)/lump_dir.h $(INC)/wadfile.h $(LIB)/libwad.a $(LIB)/libfindwad.a

$(LIB)/libwad.a:
	cd ../lib; make

clean:
	rm -f *.o wadsprit wadsprit.exe

allclean:
	make clean; cd ../lib; make clean

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@
