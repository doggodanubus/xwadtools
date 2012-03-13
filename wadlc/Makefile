INC = ../include
LIB = ../lib

CCFLAGS = $(CFLAGS) -I$(INC)
LFLAGS =  -L$(LIB)

all: wadlc wadlc64

wadlc: wadlc.o
	$(CC) $(LFLAGS) -o $@ wadlc.o -lwad

wadlc.o: wadlc.c wadlc.h $(LIB)/libwad.a $(INC)/sysdep.h $(INC)/wad.h

wadlc64: wadlc64.o
	$(CC) $(LFLAGS) -o $@ wadlc64.o -lwad

wadlc64.o: wadlc64.c wadlc64.h $(LIB)/libwad.a $(INC)/sysdep.h $(INC)/wad.h

$(LIB)/libwad.a:
	cd ../lib; make

clean:
	rm -f *.o wadlc wadlc.exe wadlc64 wadlc64.exe

allclean:
	make clean; cd ../lib; make clean

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@
