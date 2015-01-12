//Struct to hold the info obtained from indexing the file
struct SearchRecord
{
	char *fileName[5];
	char *word;
};
typedef struct SearchRecord SearchRecord;

//Create a new record 
SearchRecord *createNewSearchRecord(char *);

//Free memory associated with the record
void destroySearchRecord(SearchRecord *);

