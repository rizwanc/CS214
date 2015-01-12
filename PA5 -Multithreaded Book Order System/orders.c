#include "database.h"
#include <semaphore.h>

//Semaphore for keeping track of consumer threads to ensure they all 
//finish 
sem_t sem;

//Function to create a new order 
void *createNewOrder(void *orderFile)
{
	Order *order;
	char line[1024];
	FILE *file;
	int count = 0;
	sem_init(&sem,0,0);
	
	//Open book order file 
	file = fopen(orderFile, "r");
	
	//Check if the book order input file exists
	if(file == NULL)
	{
		printf("Error: book order input file not found");
		exit(1);
	}
	
	//Read in book order input file
	while(fgets(line, 1024, file) != NULL)
	{
		order = (Order*)malloc(sizeof(struct Order));
		
		//Check if memory was properly allocated
		if(order == NULL)
		{
			printf("Error, unsuccessful in creating new order");
			exit(1);
		}
		
		//Fill in customer order
		
		//Initialize order title
		strcpy(order->title, strtok(line, "\""));
		
		//Initialize order price
		order->price = atof(strtok(NULL, "|"));
		
		//Initialize customer ID
		order->customerID = atoi(strtok(NULL, "|"));
		
		//Intitialize order category
		strcpy(order->category, strtok(NULL, "\r\n"));
		
		//Set next var in list to null
		order->next = NULL;
		
		//Consumer thread
		pthread_t consumer;
		
		//Keep track of number of consumers
		count++;
		
		//Create new consumer thread
		pthread_create(&consumer, NULL, processOrder, order);
		
		//Reclaim storage from terminated consumer thread
		pthread_detach(consumer);
		
	}
	
	//Close the orders.txt file
	fclose(file);
	
	//Wait for all consumer threads to finish
	int i;
	for(i = 0; i < count; i++)
	{
		sem_wait(&sem);
	}
	
	return NULL;
}

//Process the user's order
void *processOrder(void *obj)
{
	//Case void * param as order object
	Order *order = (Order*)obj;
	
	//Find the customer corresponding to the order
	Customer *curr = findCustomer(order->customerID);
	
	//Give this consumer thread exclusive access to the data
    pthread_mutex_lock(&(curr->customerLock));
	
	//Create customer queue
    queue *currCustomer;
    
    //Check if the user has enough credit to buy the book
    if(curr->creditLimit >= order->price)
    {
		curr->creditLimit -= order->price;
        order->remainingCredit = curr->creditLimit;
        currCustomer = curr->transactionCompleted;
    }
    else
    {
        currCustomer = curr->transactionFailed;
    }
    
    //Lock the current customer queue
    pthread_mutex_lock(&(currCustomer->muLock));
    
    //Enqueue the current customer's order
    enqueue(currCustomer,order);
    
    //unlock the current customer queue
    pthread_mutex_unlock(&(currCustomer->muLock));
	
	//unlock the current customer
	pthread_mutex_unlock(&(curr->customerLock));
	
	//increment the value of the semaphore and wake up blocked consumer
	//threads waiting on the semaphore
	sem_post(&sem); 
	
	return NULL;
}

//Destroy user order
void destroyOrder(Order *order)
{
	//Check if the order is null
	if(order == NULL)
	{
        return;
    }
        
    //If the order was not null then free it
    free(order);
}
