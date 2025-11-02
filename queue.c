#include "queue.h"
#include <stdio.h> // For potential debugging/error messages (though not strictly needed for core functions)

/**
 * @brief Creates and initializes a new empty queue.
 * * @return QUEUE* A pointer to the newly created queue, or NULL if allocation fails.
 */
QUEUE* createQueue (void){
    QUEUE* q = (QUEUE*)malloc(sizeof(QUEUE));
    
    if(q){
        // Initialize all members
        q -> front = NULL;
        q -> rear = NULL;
        q -> count = 0; 
    }

    return q;
}

/**
 * @brief Adds an item to the rear of the queue.
 * * @param queue Pointer to the queue structure.
 * @param itemptr Pointer to the data item to be added.
 * @return bool True if successful, false if memory allocation fails.
 */
bool enqueue(QUEUE* queue, void* itemptr) {
    // 1. Allocate memory for the new node
    QUEUE_NODE* newptr = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
    if (newptr == NULL) {
        // Memory allocation failed
        return false;
    }

    // 2. Populate the new node
    newptr->dataptr = itemptr;
    newptr->next = NULL;

    // 3. Update the links
    if(queue->count == 0){
        // Queue is empty, the new node is both front and rear
        queue->front = newptr;
    } else {
        // Queue is not empty, link the current rear to the new node
        queue->rear->next = newptr;
    }

    // 4. Update queue structure (rear and count)
    queue->rear = newptr;
    queue->count++;

    return true;
}

/**
 * @brief Removes the item from the front of the queue.
 * * @param queue Pointer to the queue structure.
 * @param itemPtr Pointer to a void* where the dequeued data pointer will be stored.
 * @return bool True if successful, false if the queue is empty.
 */
bool dequeue(QUEUE* queue, void** itemPtr) {
    // Check for empty queue
    if (queue->count == 0) {
        return false;
    }

    // 1. Save the node to be removed and extract its data
    QUEUE_NODE* temp = queue->front;
    *itemPtr = temp->dataptr;

    // 2. Move front pointer to the next node
    queue->front = queue->front->next;
    
    // 3. Check if the queue became empty after dequeue
    if (!queue->front) {
        queue->rear = NULL;
    }

    // 4. Decrement count and free the removed node
    queue->count--;
    free(temp);
    
    return true;
}

/**
 * @brief Returns the data item at the front of the queue without removing it.
 * * @param queue Pointer to the queue structure.
 * @param itemPtr Pointer to a void* where the front data pointer will be stored.
 * @return bool True if successful, false if the queue is empty.
 */
bool queueFront (QUEUE* queue, void** itemPtr) {
    if (queue->count == 0) {
        return false;
    }
    *itemPtr = queue->front->dataptr;
    return true;
}

/**
 * @brief Returns the data item at the rear of the queue without removing it.
 * * @param queue Pointer to the queue structure.
 * @param itemPtr Pointer to a void* where the rear data pointer will be stored.
 * @return bool True if successful, false if the queue is empty.
 */
bool queueRear (QUEUE* queue, void** itemPtr) {
    if (queue->count == 0) {
        return false;
    }
    *itemPtr = queue->rear->dataptr;
    return true;
}

/**
 * @brief Returns the current number of items in the queue.
 * * @param queue Pointer to the queue structure.
 * @return int The number of elements in the queue.
 */
int queueCount (QUEUE* queue) {
    return queue->count;
}

/**
 * @brief Checks if the queue is empty.
 * * @param queue Pointer to the queue structure.
 * @return bool True if empty, false otherwise.
 */
bool emptyQueue(QUEUE* queue) {
    return queue->count == 0;
}

/**
 * @brief Checks if the queue is full.
 * * @param queue Pointer to the queue structure.
 * @return bool Always returns false for a linked-list implementation 
 * unless a specific memory check is performed.
 */
bool fullQueue(QUEUE* queue) {
    return false;
}

/**
 * @brief Destroys the queue, freeing all memory used by the nodes and the queue structure itself.
 * * @param queue Pointer to the queue structure.
 * @return QUEUE* Returns NULL.
 */
QUEUE* destroyQueue (QUEUE* queue) {
    if (queue) {
        QUEUE_NODE* current = queue->front;
        QUEUE_NODE* next_node;

        // Traverse the list and free each node
        while (current != NULL) {
            next_node = current->next;
            // NOTE: We only free the node structure. The user is responsible 
            // for freeing the memory pointed to by dataptr if needed.
            free(current); 
            current = next_node;
        }
        
        // Finally, free the queue structure
        free(queue);
    }
    return NULL;
}