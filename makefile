CC = gcc
CFLAGS = -g -Wall -O0
SRC = p0.c headed_linked_list.c headed_linked_list.h
OBJ = p0.o headed_linked_list.o

all : $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)
	
clean :
	$(RM) $(OBJ) main


headed_linked_list.o : 
	$(CC) $(CFLAGS) -c headed_linked_list.c
	
	
p0.o: 
	$(CC) $(CFLAGS) -c p0.c
	
