INC = ../include
LIB = ../lib

CCFLAGS = $(CFLAGS) -I$(INC)
LFLAGS = -L$(LIB) 

wadps: wadps.o $(INC)/sysdep.h $(INC)/swapfunc.h $(LIB)/libfindwad.a $(LIB)/libwad.a
	$(CC) $(LFLAGS) -o $@ wadps.o -lwad -lfindwad 

wadps.o: wadps.c

$(LIB)/libwad.a:
	cd ../lib; make

clean:
	rm -f *.o wadps wadps.exe

allclean:
	make clean; cd ../lib; make clean

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@
