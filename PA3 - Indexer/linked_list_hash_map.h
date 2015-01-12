#include "sorted-list.h"
#include <stdio.h>

//An array of sorted lists, 26 letters, 10 digits, total = 36
struct HashMap
{
    SortedListPtr *lists[36];
};
typedef struct HashMap HashMap;

//Holds a pointer to an array of sorted lists
struct HashMapPtr
{
    HashMap *hashMap;	
};
typedef struct HashMapPtr HashMapPtr;

//Create new hash map to hold file info
HashMap *createHashMap();

//Create hash map pointer
HashMapPtr *createHashMapPtr();

//Add a new node to the linked list or update an exisiting node
void insertRecord(HashMap *, char *, char *);

//Output the contents of the map to file
int outputMapToFile(HashMapPtr *, FILE *);

//free all memory allocated to the hash map and hash map pointer
void destroyHashMapPtr(HashMapPtr *);

