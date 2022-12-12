CC = gcc
CFLAGS = -g -Wall -O0
#SRC = p3.c headed_linked_list.c headed_linked_list.h headed_linked_memorylist.h headed_linked_joblist.h
OBJ = p3.o headed_linked_list.o headed_linked_memorylist.o headed_linked_joblist.o

all : $(OBJ)
	$(CC) $(CFLAGS) -o shell $(OBJ)
	
clean :
	$(RM) $(OBJ) shell


headed_linked_list.o : 
	$(CC) $(CFLAGS) -c headed_linked_list.c
	
headed_linked_memorylist.o : 
	$(CC) $(CFLAGS) -c headed_linked_memorylist.c
	
headed_linked_joblist.o : 
	$(CC) $(CFLAGS) -c headed_linked_joblist.c
		
p2.o: 
	$(CC) $(CFLAGS) -c p3.c
	
