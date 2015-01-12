#include "malloc.h"
#include <stdio.h>
#include <string.h>

static char heap[heap_size];
static struct memBlock *head;

//Malloc first fit
void *my_malloc(unsigned int size, char* file, unsigned int line)
{
	static int initializedBlock = 0;
	struct memBlock *curr;
	struct memBlock *next;
	
		if(!initializedBlock)
		{
			head = (struct memBlock *) heap;
			head->next = head->prev = 0;
			head->size = heap_size - sizeof(struct memBlock);
			head->isFree = 1;
			initializedBlock = 1;
		}
		
		curr = head;
	do
	{	
		if(curr->size < size)
		{
			//The requested size is bigger than the current block
			//go to the next block
			curr = curr->next;	 
		}
		else if(!curr->isFree)
		{
			//The block of memory is being used currently
			//go to the next block
			curr = curr->next;
		}
		else if(curr->size < (size + sizeof(struct memBlock)))
		{
			//Check if we do not have enough memory to accomodate the
			//header.  If we do not simply return the memory without
			//allocating space for the header.
			curr->isFree = 0;
			printf("Correctly Malloced memory of size %d\n", size);
			return (char*)curr + sizeof(struct memBlock);
		}
		else
		{
			//Give the user the requested memory
			next = (struct memBlock*)((char*)curr + sizeof(struct memBlock) + size);
			next->prev = curr;
			next->next = curr->next;
			
			//Case for when we have a block inseted into the middle
			//between to other blocks.
			if(curr->next != 0)
			{
				curr->next->prev = next;
			}
			curr->next = next;
			
			next->size = curr->size - sizeof(struct memBlock) - size;
			next->isFree = 1;
			
			curr->size = size;
			curr->isFree = 0;
			
			printf("Correctly Malloced memory of size %d \n", curr->size);
			return (char*)curr + sizeof(struct memBlock);
		}
	} while(curr != 0);
		
		printf("ERROR: Not enough free space at %s:%d\n", file, line);
		return 0;
}

//Free
void my_free(void *p, char *file, unsigned int line)
{
	int offset = p - (void *)heap;
	struct memBlock *curr;
	
	struct memBlock *l = (struct memBlock *)((char *)p - sizeof(struct memBlock));
	
	for(curr = head; curr != NULL; curr = curr->next)
	{
		if(curr == l)
		{
			if(curr->isFree != 0)
			{
				printf("Error INVALID FREE, ALREADY FREED! in file: %s on line: %d \n", file, line);
				return;
			}
			
			printf("Freeing block with offset %d\n", offset);
			curr->isFree = 1; 
			mergeFreeBlocks(curr);
			return;
		}
	}
	printf("Error INVALID POINTER ADDRESS! in file: %s on line: %d \n", file, line);
}

//Recursively merge block curr with all adjacent free blocks 
void mergeFreeBlocks(memBlock *curr) 
{
  
   //If block to the right is free, merge with it
  if(curr != NULL && curr->next != NULL && curr->next->isFree != 0) 
  { 
    curr->size += curr->next->size;
    curr->next = curr->next->next;
    mergeFreeBlocks(curr->next);
  }

  //If blocks to the left are free, merge with them 
  if(curr != NULL && curr->prev != NULL && curr->prev->isFree != 0) 
  { 
    curr->prev->size += curr->size;
    curr->prev->next = curr->next;
    mergeFreeBlocks(curr->prev);
  }
}
