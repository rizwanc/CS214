#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

#include "inputHelper.h"


//Main method check the users input for errors than create the hashmap
//recurse through the directories, index the files, and output everything
//to the given output file
int main(int argc, char **argv) 
{
	printf("Indexer Program by Rizwan Chaudry\n");

	FILE* invertedIndexFile;
	char* outpath = argv[1];
	char* inpath = argv[2];

	//Accept and check user input for correctness
	if(argc != 3) 
	{	    
		printf("Invalid number of arguments <inverted-index file name> <directory or file name>! \n");
		return 1;
	}

	//CAUSES SEGFAULT not sure why :-(
	//Check if the file exists and ask if the user would like to 
	//overwrite it
	/*if(fileExists(outpath) == 1)
	{
		int response = overWriteFile(outpath);
	
		if(response == 1)
		{
			//continue
		} 
		else
		{
			//If no, quit the program 
			printf("Quitting, please choose a different filename\n");
			return 0;
		}

	}*/

	// Create the pointer to the array of linked lists
    	HashMapPtr *hashMapPtr = createHashMapPtr();
    	if (hashMapPtr == NULL) 
	{
        	printf("Failed to create index pointer.\n");
        	return 1;
    	}

	//Perform the indexing on either a directory or a file
	if(isValidDirectory(inpath) == 1)
	{
		recurDirectory(hashMapPtr, inpath);
	}
	else if(fileExists(inpath) == 1)
	{
		handleFile(hashMapPtr, inpath);	
	}
	else
	{
		printf("Error, not a valid file or directory %s\n", inpath);
		destroyHashMapPtr(hashMapPtr);
		return 1;
	}

	//Open the given index file for writing
	invertedIndexFile = fopen(outpath, "w");

	//Return if failed to open the file
	if(invertedIndexFile == NULL)
	{
		printf("Failed to open inverted-index Fle\n");
		destroyHashMapPtr(hashMapPtr);
		return 1;
	}

	//Output data to the given index file
	if(outputMapToFile(hashMapPtr, invertedIndexFile) == 1)
	{
		printf("Output written to file, Thank you for using indexer\n");
		return 1;
	}

	destroyHashMapPtr(hashMapPtr);
	fclose(invertedIndexFile);

	return 0;	

}



