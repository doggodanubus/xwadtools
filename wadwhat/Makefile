INC = ../include

CCFLAGS = $(CFLAGS) -I$(INC)
LFLAGS = -L../lib -lfindwad 

wadwhat: wadwhat.o
	$(CC) $(LFLAGS) -o $@ wadwhat.o $(LFLAGS)

wadwhat.o: wadwhat.c

clean:
	rm -f *.o wadwhat wadwhat.exe

allclean:
	make clean

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@
