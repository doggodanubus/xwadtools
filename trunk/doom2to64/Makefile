INC = ../include
LIB = ../lib

CCFLAGS = $(CFLAGS) -I$(INC)
LFLAGS =  -L$(LIB)

all: doom2to64

doom2to64: doom2to64.o
	$(CC) $(LFLAGS) -o $@ doom2to64.o -lwad -lfindwad

doom2to64.o: doom2to64.c $(LIB)/libwad.a $(INC)/sysdep.h $(INC)/wad.h

$(LIB)/libwad.a:
	cd ../lib; make

clean:
	rm -f *.o doom2to64 doom2to64.exe

allclean:
	make clean; cd ../lib; make clean

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@
