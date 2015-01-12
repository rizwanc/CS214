#include <string.h>
#include <stdlib.h>
#include "linked_list_hash_map.h"
//#include "FileRecord.h"

//This class contains methods to create, insert, and destroy the hashmap and hashmap pointer

//Create new hash map
HashMap *createHashMap()
{
    return (HashMap*)malloc(sizeof(struct HashMap));
}

//Add a new node to the linked list or update an exisiting node
void insertRecord(HashMap *hashMap, char *token, char *fileName)
{
    int i;
    SortedListPtr *list;

    int asciiZero = 48;
    int asciiA = 97;

    //Hash functiom if the token is a digit subtract the ascii value for a from the
    //token to bring it into the 1 to 26 number range in order to correspon that to 
    //the array index number.  The same is done for digits except we add 26
    //so to have the digits start at index 26 and go on from there so as not to 
    //overwrote the letters stored in the first 10 slots.
    i = isalpha(token[0]) != 0 ? (int)token[0] - asciiA : ((int)token[0] - asciiZero + 26);

    list = hashMap->lists[i];

    if(list == NULL) 
    {
        hashMap->lists[i] = SLCreate(compareFileRecordInfo);
	
    }
	SLInsert(hashMap->lists[i], token, fileName);
}

//Create index pointer to allow access to the array of linked lists in
//order to store data in those lists
HashMapPtr *createHashMapPtr() 
{
    HashMapPtr *hashMapPtr = (HashMapPtr*)malloc(sizeof(struct HashMapPtr));

    	if(hashMapPtr == NULL)
	{
	     return NULL;
	}
    
        hashMapPtr->hashMap = createHashMap();

        if (hashMapPtr->hashMap != NULL) 
	{
            return hashMapPtr;
        }
	else
	{
            free(hashMapPtr);
    	    return NULL;
	}
}

int outputMapToFile(HashMapPtr *hashMapPtr, FILE *file)
{
    FileRecord *fileRecord;
    SortedListPtr *list;
    SortedListIteratorPtr *iterator;
    char *token;
    int i;
    int count;

    // Loop through each list
    for (i = 0; i < 36; i++) 
    {
        count = 0;
        token = NULL;

        list = hashMapPtr->hashMap->lists[i];

        if (list != NULL) 
	{
             iterator = SLCreateIterator(list);

	    //Loop through the linked lis, token is null or the token previously stored
	    //is  ot equal to the current token then we are on a new token 
	    //reset the count and continue otherwise it is the same token
	    //write the information to file but only print up to five files
	    //where the word was found
            while ((fileRecord = SLNextItem(iterator)) != NULL) 
	    {
                if (token == NULL || strcmp(fileRecord->token, token) != 0) 
		{
                    count = 1;
                    token = fileRecord->token;
                    fprintf(file, "<list> %s\n%s %d", token,
                    fileRecord->fileName, fileRecord->numHits);
		    fprintf(file, "\n</list>\n");
                }
                else 
		{
                    if (count < 5) 
		    {
                        fprintf(file, " %s %d", fileRecord->fileName, fileRecord->numHits);
			count++;
                    }
                }
            }
            SLDestroyIterator(iterator);
	}
    } 
    return 1;
}

//Free all memory allocated to the hash map and hash map pointer
void destroyHashMapPtr(HashMapPtr *hashMapPtr)
{
	int i;	
	
	if(hashMapPtr != NULL)
	{
		 for (i = 0; i < 36; i++) 
    		 {
        		SLDestroy(hashMapPtr->hashMap->lists[i]);
    		 }
		free(hashMapPtr->hashMap);
		free(hashMapPtr);	
	}
}


