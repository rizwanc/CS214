#include "queue.h"

//Create queue
queue* createQueue()
{
	//Malloc memory for the queue
    queue *orderQueue=(queue *)malloc(sizeof(queue));
    
    //Check if the malloc was succesfull
    if(orderQueue == NULL)
    {
		printf("Error creating queue exiting...");
		exit(1);
	}
    
    //Initialize queue
    
    //Set the rear of the queue to null
    orderQueue->rear = NULL;
    
    //Set the initial size of the queue to 0
    orderQueue->size = 0;
    
    //Initialize mutex lock used by consumer thread for the queue
    pthread_mutex_init(&(orderQueue->muLock),NULL);
    
    //return the queue
    return orderQueue;
}

//Enqueue new order's into the queue
void enqueue(queue *q, Order *order)
{
	//Check if the rear is null, if so then this is the first node of 
	//the queue.  Otherwise insert the new order at the rear of the list
	 if(q->rear == NULL)
	 {
		 q->rear = order;
		 order->next = order;
     } 
     else 
     {
		 order->next = q->rear->next;
		 q->rear->next = order;
		 q->rear = order;
     }
     //Increment the size of the queue to indicate that a new order
     //has been added
     q->size++;
}

//Remove order's from the queue
Order *dequeue(queue *q)
{
	//Check if the queue is empty
	if(q == NULL || q->rear == NULL)
	{
        return NULL;
    }
    
    //Pointer removed order from queue
    Order *returnOrder = NULL;
    
    //Check if the queue only contains one order
    //if not then move to the next node in the queue
    if(q->rear->next == NULL)
    {
        returnOrder = q->rear;
    } 
    else 
    {
        returnOrder = q->rear->next;
        q->rear->next = q->rear->next->next;
    }
    //Decrement the size of the queue to indicate a node has been 
    //removed
    q->size--;
    
    //if the size of the queue is 0 then there are no more nodes to 
    //remove, so then set the rear pointer to null
    if(q->size == 0)
    {
        q->rear = NULL;
    }
    
    //Return the removed order
    return returnOrder;
}

//Destroy queue
void destroyQueue(queue *q)
{
	//Check if the queue is null
    if(q == NULL)
    {
        return;
    }
    
    //Dequeue the first node in the queue
    Order *order = dequeue(q);
    
    //Destroy the order by freeing the memory allocated to it
    while(order != NULL)
    {
        destroyOrder(order);
    }
    
    //Free the memory allocated to the queue
    free(q);
}
