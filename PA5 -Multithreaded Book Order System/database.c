#include "database.h"

//Pointer to the customer linked list (i.e. customer database)
CustomerPtr *cusList;

//Create the customer database
CustomerPtr *createCustomerDB(char *customerFile)
{
	FILE *file;
	Customer *customer;
	char line[1024];
	Customer *curr = NULL;
	
	//Allocate memory to list pointer 
	cusList = (CustomerPtr*)malloc(sizeof(struct CustomerPtr));
	
	//If memory was properly allocated to the customer linked list
	//then intitialize the head to null
	if(cusList != NULL)
	{
		cusList->cusListHead = NULL;
	}
	else
	{
		printf("Unable to create customer databse");
		exit(1);
	}
	
	//Open customer databse file
	file = fopen(customerFile, "r");
	
	//Check if the customer databse file exists
	if(file == NULL)
	{
		printf("Error: customer database input file not found");
		exit(1);
	}
	
	//Read in customer database input file
	while(fgets(line, 1024, file) != NULL)
	{
		//Initialize customer struct
		customer = (Customer*)malloc(sizeof(struct CustomerDB));
		
		//Initialize Next customer to null
		customer->next = NULL;
		
		//Check for error
		if(customer == NULL)
		{
			printf("Error: unsuccessful in creating new customer");
			exit(1);
		}
		
		//Fill in customer info
		
		//User Name
		strcpy(customer->name, strtok(line, "|\""));
		
		//Customer IDs
		customer->id = atoi(strtok(NULL, "|"));
		
		//Credit limit
		customer->creditLimit = atof(strtok(NULL, "|"));
		
		//Address
		strcpy(customer->address, strtok(NULL, "|"));
		
		//State
		strcpy(customer->state, strtok(NULL, "|"));
		
		//Zipcode
		strcpy(customer->zipcode, strtok(NULL, "|"));
		
		//Customer Lock
		pthread_mutex_init(&customer->customerLock, NULL); 
		
		//Create a new queue for completed transactions
		customer->transactionCompleted = createQueue();
		
		//Create a new queue for failed transactions
		customer->transactionFailed = createQueue();
		
		//Add customer to customer list
		if(cusList->cusListHead == NULL)
		{
			cusList->cusListHead = customer;
			curr = customer;
		}
		else
		{
			curr->next = customer;
			curr = curr->next;
		}
	}
	
	//close the file
	fclose(file);
	
	//return the pointer to the customer database
	return cusList;
}

//Find the customer based on the given customer ID
Customer *findCustomer(int customerID)
{
	//Pointer to the current customer
	Customer *curr;
	
	//Set pointer to the beginning of the linked list
	curr = cusList->cusListHead;
	
	//While we are not at the end of the list
	//go through each node and compare the customer id given
	//to the one in the node and check for a match
	while(curr != NULL)
	{
		if(customerID == curr->id)
		{
			return curr;	
		}
		else
		{
			curr = curr->next;
		}
	}
	return NULL;
}


//Free all memory associated with the customer databse
void destroyCustomerDatabase(CustomerPtr *cusPtr)
{
    if (cusPtr == NULL)
    {
        return;
    }
	
	Customer *ptr = cusPtr->cusListHead;
   
    while(ptr != NULL)
    {
		destroyQueue(ptr->transactionCompleted);
		destroyQueue(ptr->transactionFailed);
		Customer *temp = ptr;
		ptr = ptr->next;
		free(temp);
	}
	free(cusPtr);
}

//Print the users reciept
void printUserReciepts(CustomerPtr *cusList)
{
	//Pointer to the head of the customer database
    Customer *curr = cusList->cusListHead;
    FILE *file;
    float totalRevenueGained = 0;
    
    //Create and open file for printing output to
    file = fopen("finalreport.txt", "w");
    
    while (curr != NULL)
    {
		printf("===BEGIN CUSTOMER INFO===\n");
        printf("Customer name: %s\n",curr->name);
        printf("Customer ID number: %d\n",curr->id);
        printf("Remaining credit balance after all purchases (a dollar amount): %.2f\n",curr->creditLimit);
		
		//Print output to file
        fprintf(file, "===BEGIN CUSTOMER INFO===\n");
        fprintf(file, "Customer name: %s\n",curr->name);
        fprintf(file, "Customer ID number: %d\n",curr->id);
        fprintf(file, "Remaining credit balance after all purchases (a dollar amount): %.2f\n",curr->creditLimit);
        
        printf("### SUCCESSFUL ORDERS ###\n");
        
        //Print output to file
        fprintf(file, "### SUCCESSFUL ORDERS ###\n");
        Order *order = dequeue(curr->transactionCompleted);
        
        //Keep dequeuing until there are no more oders to print
        while (order != NULL)
        {
			printf("%s| %.2f| %.2f\n",order->title,order->price,order->remainingCredit);
			
			totalRevenueGained += order->price;
			
			//Print output to file
            fprintf(file, "%s| %.2f| %.2f\n",order->title,order->price,order->remainingCredit);
            
            destroyOrder(order);
            order = dequeue(curr->transactionCompleted);
        }
        
        printf("### REJECTED ORDERS ###\n");
        
        //Print output to file
        fprintf(file, "### REJECTED ORDERS ###\n");
        order = dequeue(curr->transactionFailed);
        
        //Keep dequeuing until there are no more oders to print
        while (order != NULL)
        {
			printf("%s| %.2f\n",order->title,order->price);
			
			//Print output to file
            fprintf(file, "%s| %.2f\n",order->title,order->price);
            
            destroyOrder(order);
            order = dequeue(curr->transactionFailed);
        }
        
        printf("===END CUSTOMER INFO===\n");
        
        //Print output to file
        fprintf(file, "===END CUSTOMER INFO===\n");
        
        curr = curr->next;
        
        if(curr != NULL)
        {
			printf("\n");
			
			//Print output to file`
            fprintf(file, "\n");
        }
    }
    
    printf("Total revenue gained: %f\n", totalRevenueGained);
    
    //Print output to file
    fprintf(file, "Total revenue gained: %.2f\n", totalRevenueGained);
    
    //Close output file
    fclose(file);
}
