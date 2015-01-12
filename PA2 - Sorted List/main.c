/*
 * sorted-list.c
 */

#include <string.h>
#include <stdio.h>
#include "sorted-list.h"

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

//Destructor functions
void destroyBasicTypeAlloc(void *p){
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for allocated memory (malloc,calloc,etc.)
	free(p);
}

void destroyBasicTypeNoAlloc(void *p) {
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for memory that has not been allocated (e.g., "int x = 5;SLInsert(mylist,&x);SLRemove(mylist,&x);")
	return;
}

int main(int argc, char *argv[])
{
	SortedListPtr list = SLCreate(compareStrings, destroyBasicTypeAlloc);
	SortedListIteratorPtr itrPtr1;

	char* a = "a";
	char* b = "b";
	char* c = "c";
	char* z = "z";
	//char* e = "e";

	SLInsert(list, (void*)&a);
	SLInsert(list, (void*)&b);
	SLInsert(list, (void*)&c);
	SLInsert(list, (void*)&z);
	SLInsert(list, (void*)&e);

	
	itrPtr1 = SLCreateIterator(list);
	while(itrPtr1->currElement != NULL) {
		
		char** b = (char**)(itrPtr1->currElement->objContents);
		if(b==NULL) {
		     break;
		}
		printf("{%s}", *b);
	        SLNextItem(itrPtr1);
		
	}
    
	
    	SLDestroyIterator(itrPtr1);

	SLRemove(list, (void*)&c);

       itrPtr1 = SLCreateIterator(list);
	while(itrPtr1->currElement != NULL) {
		
		char** b = (char**)(itrPtr1->currElement->objContents);
		if(b==NULL) {
		     break;
		}
		printf("\nREMOVE {%s}", *b);
	        SLNextItem(itrPtr1);
		
	}

 	return 0;
}
