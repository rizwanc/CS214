#include "linked_list_hash_map.h"

//Checks whether the given directory is a valid directory and can be opened
int isValidDirectory(char *directory);

//Checks whether the given file is a valid file and can be opened
int isValidFile(char *fileName);

//Given the name of a file, that file will be deleted from the system
int deleteFile(char *fileName);

//Checks whether the given file name exists
int fileExists(char *fileName);

//Make given string lower case
void toLowerCase(char *str);

//Ask's the user whether they would like to overwrite the exisiting file or not
int overWriteFile(char *outputFile);

//Index single file into hash map
void handleFile(HashMapPtr *, char *fileName);

//Recusrsively index the given directory
void recurDirectory(HashMapPtr *, char *directory);



