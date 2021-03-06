#include "SearchRecord.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This class contains methods to create, destroy, and compare file records
//which contain the information from a given file.  These file records will
//be stored in the hashmap

//Create a new FileRecord to hold the information from a given file
SearchRecord *createNewSearchRecord(char *word) 
{
   SearchRecord *searchRecord = (SearchRecord *) malloc(sizeof(struct SearchRecord));

    if(searchRecord == NULL)
    {
		return NULL;
    }	

    searchRecord->word = (char*)malloc(strlen(word) + 1);

    if(searchRecord->word != NULL)
    {
    	strcpy(searchRecord->word, word);
		return searchRecord;
    }

    free(searchRecord);
    return NULL;
}

//Free all memory associated with the file Record
void destroySearchRecord(SearchRecord *searchRecord) 
{
    if(searchRecord != NULL) 
    {
        free(searchRecord->word);
        
        int i;
        for(i = 0; i < 5; i++)
        {
			if(searchRecord->fileName[i] != NULL)
			{
				free(searchRecord->fileName[i]);
			}
		}
		free(searchRecord->fileName);
    }
}
