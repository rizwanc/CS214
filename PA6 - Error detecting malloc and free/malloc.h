#include <stdlib.h>

#define heap_size 5000
#define malloc(x) my_malloc(x, __FILE__, __LINE__)
#define free(x) my_free(x, __FILE__, __LINE__)

//Header struct before each block of memory
struct memBlock
{
	struct memBlock *next;  // next pointer on free list
	struct memBlock *prev;
	unsigned int isFree:1;  // > 0 if this block is free
	unsigned int size:24; // the size of this block of memory
};
typedef struct memBlock memBlock;

//Allocate specified size of memory given by the user
void *my_malloc(unsigned int, char*, unsigned int);

//Free a block of allocated memory and merge the newly free block
//of memory with and adjacent block of memory
void my_free(void *, char *, unsigned int);

//Merge all immediately adjacent free blocks
void mergeFreeBlocks(memBlock *p);
