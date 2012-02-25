INC = ../include
LIB = ../lib

CCFLAGS = $(CFLAGS) -I$(INC)
LFLAGS =  -L$(LIB)

OBJS = main.o raw2au.o directory.o snd2au.o

dm2au: $(OBJS) $(LIB)/libfindwad.a
	$(CC) $(LFLAGS) -o $@ $(OBJS) -lfindwad
	
clean:
	rm -f dm2au dm2au.exe $(OBJS)

allclean:
	make clean; cd ../lib; make clean

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@
