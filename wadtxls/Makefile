INC = ../include
LIB = ../lib

CCFLAGS	= $(CFLAGS) -I$(INC)
LFLAGS =  -L$(LIB) -lwad -lfindwad

# Programs & Objects
PROGRAMS= wadtxls
OBJS	= wads.o levels.o list.o


# Rules & Dependencies
all::	$(PROGRAMS)

wadtxls.o: wadtxls.h dmunix.h
wads.o:    wadtxls.h dmunix.h $(INC)/sysdep.h
levels.o:  wadtxls.h dmunix.h wstructs.h $(INC)/sysdep.h
list.o:    wadtxls.h dmunix.h levels.h wstructs.h


# Commands
wadtxls: wadtxls.o $(OBJS)
	$(CC) $(OBJS) $@.o -o $@ $(LFLAGS) 

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@

# Remove Objects
clean:
	rm -f *.o wadtxls wadtxls.exe

allclean:
	make clean; cd ../lib; make clean
