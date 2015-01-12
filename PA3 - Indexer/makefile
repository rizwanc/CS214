CC = gcc
CFLAGS = -Wall

all: index

index: indexer_Main.o inputHelper.o tokenizer.o sorted-list.o FileRecord.o linked_list_hash_map.o
	$(CC) $(CCFLAGS)  -o index indexer_Main.o inputHelper.o tokenizer.o sorted-list.o FileRecord.o linked_list_hash_map.o

indexer_Main.o: indexer_Main.c inputHelper.h linked_list_hash_map.h sorted-list.h FileRecord.h
	$(CC) $(CCFLAGS) -c indexer_Main.c

inputHelper.o: inputHelper.c tokenizer.h inputHelper.h FileRecord.h sorted-list.h FileRecord.h
	$(CC) $(CCFLAGS) -c inputHelper.c

tokenizer.o: tokenizer.c tokenizer.h
	$(CC) $(CCFLAGS) -c tokenizer.c

sorted-list.o: sorted-list.c sorted-list.h FileRecord.h
	$(CC) $(CCFLAGS) -c sorted-list.c 

FileRecord.o: FileRecord.c FileRecord.h
	$(CC) $(CCFLAGS) -c FileRecord.c

linked_list_hash_map.o: linked_list_hash_map.c linked_list_hash_map.h sorted-list.h FileRecord.h
	$(CC) $(CCFLAGS) -c linked_list_hash_map.c

clean:
	@echo "cleaning project"
	-rm index *.o
	@echo "clean completed"
