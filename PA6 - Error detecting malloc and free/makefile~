CC = gcc
CFLAGS = -Wall

all: malloc

malloc: main.o malloc.o
	$(CC) $(CCFLAGS)  -o malloc main.o malloc.o

main.o: main.c malloc.h
	$(CC) $(CCFLAGS) -c main.c

malloc.o: malloc.c malloc.h
	$(CC) $(CCFLAGS) -c malloc.c 

clean:
	@echo "cleaning project"
	-rm malloc *.o
	@echo "clean completed"
