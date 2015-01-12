#include <stdio.h>
#include <stdlib.h>

#include "sorted-list.h"

//Create new node
node *createNode(FileRecord *data, node* nextElement) {
	node* newNode = (node*)malloc(sizeof(struct node_T)); 

	if(newNode == NULL) {	
		return NULL;
	}

        newNode->data = data; 
	newNode->refCount = 1;
	newNode->nextElement = nextElement;
        
        return newNode; 
}

//Create linked list
SortedListPtr *SLCreate(CompareFuncT cf) {

      SortedListPtr *list = (SortedListPtr*)malloc(sizeof(struct SortedList)); 
	if(list != NULL) {			
		list->LHead = NULL;		
		list->compareFunc = cf;	

		return list;
	} else {
		return NULL; 
	}
}


//Create the iterator to traverse linked list
SortedListIteratorPtr *SLCreateIterator(SortedListPtr *list) {

	if(list == NULL)
	{
		return NULL;
	}

	SortedListIteratorPtr *slItr = (SortedListIteratorPtr*)malloc(sizeof(struct SortedListIterator));  

	if(slItr != NULL) {	
		slItr->currElement = list->LHead;   
		
		/*if(slItr->currElement != NULL) {   
			list->LHead->refCount++;
		}*/
		return slItr;
	} else {
		return NULL;  
	}
}


//Free the memory allocated to iterator
void SLDestroyIterator(SortedListIteratorPtr *iter) {

	if(iter != NULL)
	{
	    return;	
	}
	
	free(iter);  
}

//Free memory allocated to linked list
void SLDestroy(SortedListPtr *list) { 
	if(list != NULL)
	{
	     node *nPtr = list->LHead;
	     node *prev = NULL;
	
	     while(nPtr != NULL)
	     {
		prev = nPtr;
		nPtr = nPtr->nextElement;
		free(prev);
	     }
	     free(list);	
	}		
}

//Insert new node into the linked lsit
void SLInsert(SortedListPtr *list, char *token, char *fileName) 
{
    node *newNode; 
    node *curr; 
    node *prev;
    FileRecord *fileRecord; 
    FileRecord *temp;
    int i; 

    //If the list is null return
    if(list == NULL) 
    {
        return;
    }
    
    //Add new node as the head of the list
    if(list->LHead == NULL) 
    {
        fileRecord = createNewFileRecord(token, fileName, 1);
        newNode = createNode(fileRecord, NULL);

        if(fileRecord != NULL && newNode != NULL) 
	{
            list->LHead = newNode;
            return;
        }
        else 
	{
            free(fileRecord);
            free(newNode);
            return;
        }
    }


   //Add new node to the head of the list    
   if((i = list->compareFunc(temp, list->LHead->data)) <= 0) 
   {
	//if i is less than zero than the new node should be intersetd at the
	//front of the head
        if(i < 0) 
	{
            fileRecord = createNewFileRecord(token, fileName, 1);
            newNode = createNode(fileRecord, list->LHead);

            if(fileRecord != NULL && newNode != NULL) 
	    {
                list->LHead = newNode;
                return;
            }
            else 
	    {
                free(fileRecord);
                free(newNode);
                return;
            }
        }
        else 
	{
            //The current item and the item being inserted are the same
	    //increment num hits to indicate another of the same token
	    //was found
            list->LHead->data->numHits++;
            return;
        }
    }
   
        //Node being inserted does not belong at the head of the list
	//or cannot be the head, loop through the list to find an 		
       //appropriate spot to insert the data
        curr = list->LHead;
        prev = NULL;
        
	while(curr != NULL)
	{
            i = list->compareFunc(temp, curr->data);

            if (i == 0) 
	    {
                curr->data->numHits++;
                return;
            }
            else if(i < 0) 
	    {
                fileRecord = createNewFileRecord(token, fileName, 1);
                newNode = createNode(fileRecord, curr);

                if(fileRecord != NULL && newNode != NULL) 
		{
                    prev->nextElement = newNode;
                    return;
                }
                else 
		{
                    free(fileRecord);
                    free(newNode);
                    return;
                }	
            }
	   prev = curr;
	   curr = curr->nextElement; 
	}

        //Add node to the end of the list
        fileRecord = createNewFileRecord(token, fileName, 1);
        newNode = createNode(fileRecord, NULL);

        if(fileRecord != NULL && newNode != NULL) 
	{
            prev->nextElement = newNode;
            return;
        }
        else 
	{
            free(fileRecord);
            free(newNode);
            return;
        }
}


//Get the next item in the list
FileRecord *SLNextItem(SortedListIteratorPtr *iter) 
{
	if(iter == NULL || iter->currElement == NULL)
	{
		return NULL;
	}

	FileRecord *data = iter->currElement->data;
	iter->currElement = iter->currElement->nextElement;
	
	return data;
}





