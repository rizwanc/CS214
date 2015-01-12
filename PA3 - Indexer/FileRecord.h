
//Struct to hold the info obtained from indexing the file
struct FileRecord
{
	char *fileName;
	char *token;
	int numHits;
};
typedef struct FileRecord FileRecord;

//Create a new record 
FileRecord *createNewFileRecord(char *, char *, int);

//Free memory associated with the record
void destoryFileRecord(FileRecord *);

//Compare two records
int compareFileRecordInfo(FileRecord *, FileRecord *); 
