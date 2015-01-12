#include "sorted-list.h"
#include <stdio.h>

node* createNode(void* objContents, node* nextElement) {
	node* newNode = (node*)malloc(sizeof(node)); 

	if(newNode == NULL) {	
		return NULL;
	}

        newNode->objContents = objContents; 
	newNode->refCount = 1;
	newNode->nextElement = nextElement;
        
        return newNode; 
}

void destroyNode(node* n) {
	free(n);
}

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df) {

      SortedListPtr list = (SortedListPtr)malloc(sizeof(struct SortedList)); /*Malloc space for List*/

	if(list != NULL) {			/*Check if the malloc succeeded*/
		list->LHead = NULL;		/*ititialize the head to null*/
		list->compareFunc = cf;	/*Add compare function*/
	
		list->destructFunc = df;
	
		return list; /*return the list*/
	} else {
		return NULL; /*return null if the list was not created*/
	}
};

SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {

	SortedListIteratorPtr slItr = (SortedListIteratorPtr)malloc(sizeof(struct SortedListIterator));  

	if(slItr != NULL) {	
		slItr->currElement = list->LHead;   
		
		if(slItr->currElement != NULL) {   
			list->LHead->refCount++;
		}
		return slItr;
	} else {
		return NULL;  
	}
}

void SLDestroyIterator(SortedListIteratorPtr iter) {

	if(iter->currElement != NULL) {	
		if(iter->currElement->refCount <= 1) {	
			destroyNode(iter->currElement);
		} else {
			iter->currElement->refCount--; 
		}
	} 
	free(iter);  
}

void SLDestroy(SortedListPtr list) {
	free(list);	/*Free memory allocated to list struct*/
}

int SLInsert(SortedListPtr list, void *newObj) {
	
	int compVal;		
	void* currElement;	

	SortedListIteratorPtr iteratorPtr = SLCreateIterator(list);	

	if(iteratorPtr == NULL) {	
		return 0;
	}

	node *prevElement = iteratorPtr->currElement;	
	
	if(iteratorPtr->currElement == NULL || (*list->compareFunc)(newObj, iteratorPtr->currElement->objContents) == 1) {

		list->LHead = createNode(newObj, iteratorPtr->currElement);	
		SLDestroyIterator(iteratorPtr);		
		return 1; 	
	}

	currElement = SLNextItem(iteratorPtr);	  

	while(iteratorPtr->currElement != NULL) {	  
		
		compVal = (*list->compareFunc)(newObj, currElement);	

		if(compVal == 1) {	
			break;
		} else if(compVal == 0) {	
			SLDestroyIterator(iteratorPtr);
			return 1;
		} else {	
			prevElement = iteratorPtr->currElement;
			currElement = SLNextItem(iteratorPtr);
		}
	 }
		
   prevElement->nextElement = createNode(newObj, iteratorPtr->currElement);  
	
		SLDestroyIterator(iteratorPtr);		

		return 1;	
}

int SLRemove(SortedListPtr list, void *newObj) {

	void* currElement;
	SortedListIteratorPtr removePtr = SLCreateIterator(list);
	
	if(removePtr == NULL) {
		return 0;
	}

	node *prevElement = removePtr->currElement;

	int i = (*list->compareFunc)(newObj, list->LHead->objContents);
	
	if(i == 0) {  /*object is the head*/
		list->LHead = list->LHead->nextElement;

		if(removePtr->currElement->refCount == 2) {/*Remove node*/
			destroyNode(removePtr->currElement);
		}
		SLDestroyIterator(removePtr);
		return 1;
	}

	currElement = SLNextItem(removePtr);

	while(removePtr->currElement != NULL) {  /*object is somehwere else in the list*/
		int i = (*list->compareFunc)(newObj, currElement);

		if(i == 0) {
			prevElement->nextElement = removePtr->currElement->nextElement;

	if(removePtr->currElement->refCount == 2) {	
		destroyNode(removePtr->currElement);
	}

	SLDestroyIterator(removePtr);
	return 1;
    } else {
	prevElement = removePtr->currElement;
	currElement = SLNextItem(removePtr);
    }
 }
 SLDestroyIterator(removePtr);
	return 0;
}
		

void *SLNextItem(SortedListIteratorPtr iter) {

	node *ELEMENT = iter->currElement->nextElement;

	if(iter->currElement->refCount == 1) {	/*Check to see if the current element has been removed*/
		destroyNode(iter->currElement);
	} else {
		iter->currElement->refCount--;
	}
	iter->currElement = ELEMENT;
	if(iter->currElement != NULL) {		/*Return the element or return null if end of list*/
		iter->currElement->refCount++;
		return iter->currElement->objContents;
	} else {
		return NULL;
	}
}





