#include "FileRecord.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This class contains methods to create, destroy, and compare file records
//which contain the information from a given file.  These file records will
//be stored in the hashmap

//Create a new FileRecord to hold the information from a given file
FileRecord *createNewFileRecord(char *token, char *fileName, int numHits) 
{
    FileRecord *fileRecord = (FileRecord *) malloc(sizeof(struct FileRecord));

    if(fileRecord == NULL)
    {
	return NULL;
    }	

    fileRecord->fileName = (char*)malloc(strlen(fileName) + 1);
    fileRecord->token = (char*)malloc(strlen(token) + 1);

    if(fileRecord->token != NULL || fileRecord->fileName != NULL)
    {
	strcpy(fileRecord->fileName, fileName);
    	strcpy(fileRecord->token, token);
    	fileRecord->numHits = numHits;
	return fileRecord;
    }

    free(fileRecord);
    return NULL;
}

//Free all memory associated with the file Record
void destroyFileRecord(FileRecord *fileRecord) 
{
    if(fileRecord != NULL) 
    {
        free(fileRecord->token);
        free(fileRecord->fileName);
        free(fileRecord);
    }
}

 //Compare two records. If they are equal then do not add to the list and check if the filenames are the same.
 //If yes, then increment the numHits variable otherwise simpley add the new item to proper position in
 //the linked list
int compareFileRecordInfo(FileRecord *fileInfo1, FileRecord *fileInfo2) 
{
    int compareValue;

    FileRecord *fileRecord1 = (FileRecord *)fileInfo1; 
    FileRecord *fileRecord2 = (FileRecord *)fileInfo2;

    compareValue = strcmp(fileRecord1->token, fileRecord2->token);

    if(compareValue == 0)
    {
	compareValue = strcmp(fileRecord1->fileName,fileRecord2->fileName);
	return compareValue;
    }		
    return compareValue;
}

