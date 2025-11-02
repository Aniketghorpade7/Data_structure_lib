//queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include<stdbool.h>
#include<stdlib.h>

//node structure
typedef struct node{
    void *dataptr;
    struct node* next;
}QUEUE_NODE;

//queue structure
typedef struct {
    QUEUE_NODE* front;
    QUEUE_NODE* rear;
    int count;
}QUEUE;

//Function declarations
QUEUE* createQueue (void);
QUEUE* destroyQueue (QUEUE* queue);

bool dequeue (QUEUE* queue, void** iteamPtr);
bool enqueue (QUEUE* queue, void* itemptr);
bool queueFront (QUEUE* queue, void** itemPtr);
bool queueRear (QUEUE* queue, void** itemPtr);
int queueCount (QUEUE* queue);

bool emptyQueue(QUEUE* queue);
bool fullQueue(QUEUE* queue);

#endif