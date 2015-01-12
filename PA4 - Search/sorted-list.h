#include "SearchRecord.h"

//Define node structure
struct node_T
{
   SearchRecord *data;
   struct node_T* nextElement;
};
typedef struct node_T node;

//Create a new node
node *createNode(SearchRecord *data, struct node_T *);

//Define sorted list structure
struct SortedList
{	
   node* LHead;	
};
typedef struct SortedList SortedListPtr;

//Define sorted list iterator structure
struct SortedListIterator
{
  node* currElement;
};
typedef struct SortedListIterator SortedListIteratorPtr;

//Create new list
SortedListPtr *SLCreate();

//free all memory associated with the list
void SLDestroy(SortedListPtr* list);

//Insert node into list
void SLInsert(SortedListPtr* list, char *);

//Create iterator to traverse the list
SortedListIteratorPtr *SLCreateIterator(SortedListPtr* list);

//Free all memory associated with the iterator
void SLDestroyIterator(SortedListIteratorPtr* iter);

//Get the ne the next item in the list
SearchRecord *SLNextItem(SortedListIteratorPtr* iter);
