#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "orders.h"

//Queue data structure to hold user order's
struct queue
{
    Order *rear; //pointer to the tail of the queue
    int size; //Size of the queue
    pthread_mutex_t muLock; //Consumer lock for a customer order
};
typedef struct queue queue;

//Create the queue
queue *createQueue();

//Insert data into the queue
void enqueue(queue *, Order *);

//Remove data from the queue
Order *dequeue(queue *);

//Destroy queue
void destroyQueue(queue *);
