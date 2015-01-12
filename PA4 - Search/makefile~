CC = gcc
CFLAGS = -Wall

all: search

search: search.o sorted-list.o SearchRecord.o
	$(CC) $(CCFLAGS)  -o search search.o sorted-list.o SearchRecord.o

search.o: search.c search.h sorted-list.h SearchRecord.h
	$(CC) $(CCFLAGS) -c search.c

sorted-list.o: sorted-list.c sorted-list.h SearchRecord.h
	$(CC) $(CCFLAGS) -c sorted-list.c 

SearchRecord.o: SearchRecord.c SearchRecord.h
	$(CC) $(CCFLAGS) -c SearchRecord.c

clean:
	@echo "cleaning project"
	-rm search *.o
	@echo "clean completed"
