#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#include "tokenizer.h"
#include "inputHelper.h"

/*
 *This input helper class contains functions to handle the users input
 *and to process it in terms of what file and directories to access
 *and where to write the output to. 
 */

//Check if the given directory is valid
int isValidDirectory(char *directory) 
{
	DIR* dir = opendir(directory);
	if(dir == NULL) 
	{
	   return 0;
	} 
	closedir(dir);
	return 1;
}

//Check if the the given file exists
int fileExists(char *fileName)
{
	FILE *file = fopen(fileName, "r");
	if(file != NULL)	
	{
		fclose(file);
		return 1;
	} 	
	return 0;
}

//Check if the given file is falid
int isValidFile(char *fileName)
{
	FILE *file = fopen(fileName,"w");
	if(file == NULL)
	{
		return 0;
	}
	fclose(file);
	return 1;
}

//Delete the given file
int deleteFile(char *fileName)
{
	int i = remove(fileName);
	if(i == -1)
	{
		return 0;
	}
	else if(i == 0)
	{
		return 1;
	}
	return 0;
}

//Convert string to lower case
void toLowerCase(char *str)
{
	int i;
	
	for(i = 0; i < strlen(str); i++)
	{
		str[i] = tolower(str[i]);
	}
}

//OverWrite the given file
int overWriteFile(char *outputFile)
{
	printf("The output file \"%s\" you specified already exists.  Do you wish to overwrite it? (y for yes or anything for no)\n", outputFile);
	
	char input;
	scanf("%c", &input);
	if(input == 'y' || input == 'Y')
	{
		return 1;
	}
	return 0;
}

//Parse given file
void handleFile(HashMapPtr *hashMapPtr,char *fileName)
{
	FILE *pfile;
	TokenizerT *tok;
	char *string;
	char *token;
	long fSize;

	//Open file for reading
	pfile = fopen(fileName, "r");
	
	//Start at the beginning of the file going through the file until
	//we hit EOF
	fseek(pfile, 0, SEEK_END);

	//Get the size of the file
	fSize = ftell(pfile);

	//reset the position to the beginning of the file
	rewind(pfile);

	//malloc memory to stroe string
	string = (char*)malloc(fSize * sizeof(char));
	
	//copy file into text
	fread(string, sizeof(char), fSize, pfile);

	//close the stream
	fclose(pfile);

	/*File is now loaded into memory buffer*/
	
	//Begin tokenizing and storing the string into the inverse index
	tok = TKCreate(string);

	if(tok != NULL)
	{
		while((token = TKGetNextToken(tok)) != NULL)
		{
			//make characters lower case
			toLowerCase(token);

			//printf("Token: %s\n", token);
			insertRecord(hashMapPtr->hashMap, token, fileName);
			
		}
		TKDestroy(tok);
	}
}


//Recursively traverse index
void recurDirectory(HashMapPtr *hashMapPtr, char *directory)
{
	DIR *pDir;
	struct dirent *pDirent;

	pDir = opendir(directory);
	
	while((pDirent = readdir(pDir)) != NULL)
	{
		char c[strlen(pDirent->d_name)+1];
		//printf("Here: %s\n", pDirent->d_name);

		strcpy(c, pDirent->d_name);

		//printf("Here to: %s\n", c);
	
		char newStr[(strlen(directory)+1)+(strlen(c)+1)+1];
		strcpy(newStr, directory);
		strcat(newStr,"/");
		strcat(newStr,c);

		//printf("Here as well: %s\n", newStr);

		//printf("Here!!%s\n", c);

		//Check for if same directory or parent directory
		if(strcmp(c,".") != 0 && strcmp(c,"..") != 0 && c[0] != '.')
		{	
			if(isValidDirectory(newStr) == 1)
			{
				recurDirectory(hashMapPtr, newStr);
			}
			else if(fileExists(newStr) == 1)
			{
				handleFile(hashMapPtr, newStr);
			}
		} 		
	}
	closedir(pDir);
}










