INC = ../include
LIB = ../lib

CCFLAGS = $(CFLAGS) -I$(INC)
LFLAGS =  -L$(LIB)

spitwad: spitwad.o
	$(CC) $(LFLAGS) -o $@ spitwad.o -lwad # -lfindwad

spitwad.o: spitwad.c $(INC)/sysdep.h $(INC)/strfunc.h $(INC)/wad.h \
	$(INC)/lump_dir.h $(INC)/wadfile.h $(LIB)/libwad.a

$(LIB)/libwad.a:
	cd ../lib; make

clean:
	rm -f *.o spitwad spitwad.exe

allclean:
	make clean; cd ../lib; make clean

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@
