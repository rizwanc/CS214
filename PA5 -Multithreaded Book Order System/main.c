#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "database.h"

int main(int argc, char **argv)
{
	//Producer
	pthread_t producer;
	
	//Variable used to check for thread errors
	int error;
	
	//Check for proper input
	if(argc != 4)
	{
		printf("Error, proper input: name of customer database input file, name of book order input file, name of category input file\n");
		exit(1);
	}
	
	//Add customer to customer database
	CustomerPtr *customerList = createCustomerDB(argv[1]);
	
	/*Create new Producer thread
	 * pthread_t *thread, 
	 * const pthread_attr_t *attr,
	 * void *(*start_routine) (void *), 
	 * void *arg
	 */
    error = pthread_create(&producer, NULL, createNewOrder,argv[2]);
    
    //Check for pthread create error
    if(error != 0)
    {
		printf("Error");
		exit(1);
	}
       
    /*Wait for consumer threads to terminate
     * pthread_t thread, 
     * void **value_ptr
     */
    error = pthread_join(producer, NULL);

	//Check for pthread join error
	if(error != 0)
    {
		printf("Error");
		exit(1);
	}
	
	//Print output to screen and file
	printUserReciepts(customerList);
    
    //Free all memory allocated to customer database and queues
    destroyCustomerDatabase(customerList);
	
	//Return with success
	return 0;
}
