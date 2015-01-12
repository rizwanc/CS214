#include "sorted-list.h"
#include <stdio.h>

//An array of sorted lists, 26 letters, 10 digits, total = 36
struct HashMap
{
    SortedListPtr *lists[36];
};
typedef struct HashMap HashMap;

//Create new hash map to hold file info
HashMap *createHashMap();

//Add a new node to the linked list or update an exisiting node
int insertRecord(HashMap *, char *);

HashMap *parseAndStoreFile(FILE *file);

void andSearch(HashMap *hashMap, char* searchInput);

void orSearch(HashMap *hashMap, char *searchInput);

//free all memory allocated to the hash map and hash map pointer
void destroyHashMap(HashMap *);

