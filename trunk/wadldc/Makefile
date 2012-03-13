INC = ../include
LIB = ../lib

CCFLAGS = $(CFLAGS) -I$(INC)
LFLAGS =  -L$(LIB)

all: wadldc wadldc64

wadldc: wadldc.o
	$(CC) $(LFLAGS) -o $@ wadldc.o -lwad

wadldc64: wadldc64.o
	$(CC) $(LFLAGS) -o $@ wadldc64.o -lwad

wadldc.o: wadldc.c $(INC)/sysdep.h $(INC)/wad.h $(INC)/lump_dir.h \
	  $(INC)/wadfile.h $(LIB)/libwad.a

wadldc64.o: wadldc64.c $(INC)/sysdep.h $(INC)/wad.h $(INC)/lump_dir.h \
	  $(INC)/wadfile.h $(LIB)/libwad.a

$(LIB)/libwad.a:
	cd ../lib; make

clean:
	rm -f *.o wadldc wadldc.exe wadldc64 wadldc64.exe

allclean:
	make clean; cd ../lib; make clean

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@
