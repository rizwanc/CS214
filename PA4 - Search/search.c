#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "search.h"

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Invalid number of inputs.  Please enter the name of an index file\n");
		return 1;
	}

	FILE *file = fopen(argv[1], "r");

	if(file == NULL)
	{
		printf("Error, index file is empty!...quitting\n");
	}

	HashMap *hashMap = parseAndStoreFile(file);
	
	puts("Enter your search queries:");
	
	char* searchInput = malloc(1024);

	while (1 == 1) 
	{
		printf("Search> ");
	    fgets(searchInput, 1024, stdin);
		searchInput[strlen(searchInput) - 1] = '\0';

		if(searchInput[0] == 'q')
		{
			puts("Quitting program...");
		    break;
		}
		else if(searchInput[0] == 's')
		{
			if(searchInput[1] == 'a')
			{
				andSearch(hashMap, searchInput);
			}
		  
			if(searchInput[1] == 'o')
			{
				orSearch(hashMap, searchInput);
			}
		}
	 }
	
	destroyHashMap(hashMap);
	free(searchInput);
	
	return 0;
}

//Create new hash map
HashMap *createHashMap()
{
    return (HashMap*)malloc(sizeof(struct HashMap));
}

//Add a new node to the linked list or update an exisiting node
int insertRecord(HashMap *hashMap, char *token)
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
        hashMap->lists[i] = SLCreate();
	
    }
	SLInsert(hashMap->lists[i], token);

    return i;
}

HashMap *parseAndStoreFile(FILE *file)
{
	char *line;
	HashMap *hashMap;
	hashMap = createHashMap();
	int i;
	int k = 0;

	line = malloc(2048);

	while(fgets(line, 2048, file) != NULL)
	{
		if(strstr(line, "<list>"))
		{
			char *word;
			word = strtok(line + 6, " \n");
			i = insertRecord(hashMap, word);

			//printf("Word in file %s\n", word);
		}
		else if(strstr(line, "</list>"))
		{	
			continue;
		}
		else
		{
			SortedListPtr *list;
			SortedListIteratorPtr *iter;
			char *fileNames;
			int nextNode = 0;
			
			list = hashMap->lists[i];
			iter = SLCreateIterator(list);
			
			if(iter->currElement->data->fileName[0] != NULL && iter->currElement->nextElement != NULL)
			{
				while(iter->currElement->nextElement != NULL)
				{
					iter->currElement = iter->currElement->nextElement;
					if(iter->currElement->data->fileName[0] == NULL)
					{
						break;
					}
				}
				nextNode = 1;
			}
			
			//printf("Here %s\n", line);
			
			fileNames = strtok(line, " \n");
			
			while(fileNames != NULL)
			{
				if(nextNode == 1)
				{
					iter->currElement->data->fileName[k] = (char*)malloc(strlen(fileNames) + 1);
					strcpy(iter->currElement->data->fileName[k], fileNames);
					k++;
					
					fileNames = strtok(NULL, " \n");
					
					if(fileNames == NULL)
					{
						break;
					}
					else if(isdigit(fileNames[0]))
					{
						fileNames = strtok(NULL, " \n");
					}
				}
				else 
				{
					list->LHead->data->fileName[k] = (char*)malloc(strlen(fileNames) + 1);
					strcpy(list->LHead->data->fileName[k], fileNames);
					k++;
					
					fileNames = strtok(NULL, " \n");
					
					if(fileNames == NULL)
					{
						break;
					}
					else if(isdigit(fileNames[0]))
					{
						fileNames = strtok(NULL, " \n");
					}
				}
					
			}
			k = 0;	
			nextNode = 0;
			SLDestroyIterator(iter);
	    }
	}

	fclose(file);
	
	return hashMap;
}

void andSearch(HashMap *hashMap, char *searchInput)
{
	printf("User input %s\n", searchInput);
	
	int i; 
	int first = 0;
	int printCount = 0;
	int wordCount = 0;
	char *fileHolder[5] = {NULL, NULL, NULL, NULL, NULL};
	char *searchWords;
	searchWords = strtok(searchInput, " ");

	while(searchWords != NULL)
	{
		searchWords = strtok(NULL, " ");
		printCount++;
		
		//printf("YAAAAAAAYYYY %d", printCount);
		
		if(searchWords == NULL)
		{
			if(wordCount == 1)
			{
				int i;
				for(i = 0; i < 5; i++)
				{
					if(fileHolder[i] != NULL)
					{
						printf("Search terms are contained in files: %s\n", fileHolder[i]);
					}
				}
					
			}
			
			break;
		}
		
		if(first == 0)
		{
			int i;
			int j;
			SortedListPtr *list;
		    SortedListIteratorPtr *iter;
			int asciiZero = 48;
			int asciiA = 97;			
			i = isalpha(searchWords[0]) != 0 ? (int)searchWords[0] - asciiA : ((int)searchWords[0] - asciiZero + 26);
			
			list = hashMap->lists[i];
			iter = SLCreateIterator(list);
			
			if(hashMap->lists[i] == NULL)
			{
				return;
			}
			
			iter->currElement = hashMap->lists[i]->LHead;
			
			if(strcmp(iter->currElement->data->word, searchWords) != 0)
			{	
				if(iter->currElement->nextElement != NULL)
				{
					while(iter->currElement->nextElement != NULL)
					{
						if(strcmp(iter->currElement->data->word, searchWords) == 0)
						{
								break;
						}
						else
						{
							iter->currElement = iter->currElement->nextElement;
						}
					}
				}
				else
				{
					return;
				}
			}
					
			for(j = 0; j < 5; j++)
			{
				if(iter->currElement->data->fileName[j] != NULL)
				{
					fileHolder[j] =  iter->currElement->data->fileName[j];
				}
			}
			SLDestroyIterator(iter);
			first = 1;
			wordCount++;
			continue;
		}
		
		for(i = 0; i < 36; i++)
		{
			
			int asciiZero = 48;
			int asciiA = 97;			
			int b = isalpha(searchWords[0]) != 0 ? (int)searchWords[0] - asciiA : ((int)searchWords[0] - asciiZero + 26);
			wordCount++;
			
			if(hashMap->lists[b] == NULL)
			{
				printf("ERROR WORD %s, is not contained in the file \n", searchWords);
				return;
			}
			
			SortedListPtr *list;
			SortedListIteratorPtr *iter;
			
			list = hashMap->lists[i];
			
			if(hashMap->lists[i] != NULL)
			{
				iter = SLCreateIterator(list);
				
				if(strcmp(iter->currElement->data->word, searchWords) == 0)
				{
					int j;
					for(j = 0; j < 5; j++)
					{
						if(iter->currElement->data->fileName[j] != NULL)
						{
							int l;
							for(l = 0; l < 5; l++)
							{
								if(fileHolder[l] != NULL)
								{
									if(strcmp(fileHolder[l], iter->currElement->data->fileName[j]) == 0)
									{
										if(printCount >= 3)
										{
											//printf("HERE!!!!!!!!");
											break;
										}
										 printf("Search Terms found in Files: %s\n", fileHolder[l]);
										 break;
									}
								}
							}
						}
						else
						{
							SLDestroyIterator(iter);
							break;
						}
					}
					SLDestroyIterator(iter);
				}
				else if(iter->currElement->nextElement != NULL)
				{
					while(iter->currElement->nextElement != NULL)
					{
						if(strcmp(iter->currElement->data->word, searchWords) == 0)
						{
								break;
						}
						else
						{
							iter->currElement = iter->currElement->nextElement;
						}
					}
					
					int j;
					for(j = 0; j < 5; j++)
					{
						if(iter->currElement->data->fileName[j] != NULL)
						{
							int l;
							for(l = 0; l < 5; l++)
							{
								if(fileHolder[l] != NULL)
								{
									if(strcmp(fileHolder[l], iter->currElement->data->fileName[j]) == 0)
									{
										if(printCount >= 3)
										{
											break;
										}
										 printf("Search Terms found in Files: %s\n", fileHolder[l]);
										 break;
									}
								}
							}
						}
						else
						{
							SLDestroyIterator(iter);
							break;
						}
					}
					SLDestroyIterator(iter);
				}
			}
		}
	}
	return;
}

void orSearch(HashMap *hashMap, char *searchInput)
{
	printf("User input %s\n", searchInput);
	
	int i; 
	char *searchWords;
	searchWords = strtok(searchInput, " ");
	
	while(searchWords != NULL)
	{
		searchWords = strtok(NULL, " ");
		
		if(searchWords == NULL)
		{
			break;
		}
		
		for(i = 0; i < 36; i++)
		{
			if(hashMap->lists[i] != NULL)
			{
				if(strcmp(searchWords, hashMap->lists[i]->LHead->data->word) == 0)
				{
					int j;
					for(j = 0; j < 5; j++)
					{
						if(hashMap->lists[i]->LHead->data->fileName[j] != NULL)
						{
							printf("Search Terms located in files: %s\n", hashMap->lists[i]->LHead->data->fileName[j]);
						}
						else
						{
							break;
						}
					}
				}
			}
		}
	}
}

//Free all memory allocated to the hash map and search record
void destroyHashMap(HashMap *hashMap)
{
	int i;	
	
	if(hashMap != NULL)
	{
		 for (i = 0; i < 36; i++) 
    	 {
			 if(hashMap->lists[i] != NULL)
			 {
				 if(hashMap->lists[i]->LHead->data->word != NULL)
				 {
				    destroySearchRecord(hashMap->lists[i]->LHead->data);
				 }
			 }
        	 SLDestroy(hashMap->lists[i]);
         }
		 free(hashMap);	
	}
}

