INC = ../include
LIB = ../lib

CCFLAGS = $(CFLAGS) -I$(INC)
LFLAGS =  -L$(LIB)

OBJS = convert.o  main.o  midimerge.o  parsemidi.o  smalloc.o

midi3mus: $(OBJS)
	$(CC) $(LFLAGS) -o $@ $(OBJS)
	
clean:
	rm -f midi3mus midi3mus.exe $(OBJS)

allclean:
	make clean; cd ../lib; make clean

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@
