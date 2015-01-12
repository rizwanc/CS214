CC = gcc
CFLAGS = -Wall

all: bookorder

bookorder: main.o database.o orders.o queue.o
	$(CC) $(CCFLAGS)  -o bookorder main.o database.o orders.o queue.o -lpthread

main.o: main.c database.h queue.h orders.h
	$(CC) $(CCFLAGS) -c main.c

database.o: database.c database.h queue.h orders.h
	$(CC) $(CCFLAGS) -c database.c 

orders.o: orders.c database.h queue.h orders.h
	$(CC) $(CCFLAGS) -c orders.c

queue.o: queue.c queue.h orders.h database.h
	$(CC) $(CCFLAGS) -c queue.c

clean:
	@echo "cleaning project"
	-rm bookorder *.o
	@echo "clean completed"
