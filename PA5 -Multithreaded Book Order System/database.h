#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "queue.h"

//Customer database struct
struct CustomerDB
{
	char name[20]; //Arrray to hold the customers name
	int id; //Integer to holed the customer ID number
	float creditLimit; //Customer's available assets
	char address[20]; //Array to hold the customer address
	char state[20]; //Array to hold the customer sate
	char zipcode[10]; //Array to the hold the customer zipcode
	
	queue *transactionCompleted; //Queue for completed transactions
	queue *transactionFailed; //Queue for failed transactions
	
	pthread_mutex_t customerLock; //Mutex lock for consumer thread
	struct CustomerDB *next; //Pointer to the next customer
};
typedef struct CustomerDB Customer;

//Pointer to customer linked list
struct CustomerPtr
{
	Customer *cusListHead;
};
typedef struct CustomerPtr CustomerPtr;

//Create the customer database 
CustomerPtr *createCustomerDB(char *customerFile);

//Find customer in customer database
Customer *findCustomer(int customerID);

//Destory customer database
void destroyCustomerDatabase(CustomerPtr *);

//Print customer reciepts
void printUserReciepts(CustomerPtr *);
