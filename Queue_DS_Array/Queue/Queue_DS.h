
/*
 * Queue_DS.h
 *
 * Created: 12 Aug 23
            11:40:53 AM
 *  Author: Mahmoud Sheham
 */


#ifndef __QUEUE_DS_H__
#define __QUEUE_DS_H__

#include <stdio.h>
#include <stdlib.h>

#include "../Utilities/std_types.h"

//#define DEBUG

/***
    * User define data types section
**/

/**The queue user define data type**/
typedef struct
{
    /**Pointer to the data that will be stored in the queue**/
    void **QueueArray;

    /**The index of the front element in the queue**/
    sint32_t QueueFront;

    /**The index of the rear element in the queue**/
    sint32_t QueueRear;

    /**The number of elements present in the queue**/
    uint32_t QueueCount;

    /**The max number of elements that can be stored in the queue**/
    uint32_t QueueMaxSize;
}Queue_t;

/**The queue status user define data type**/
typedef enum
{
    /**If no problem**/
    QUEUE_OK            = 0,

    /**If something goes wrong in side the function**/
    QUEUE_NOK           = 1,

    /**If the queue is full**/
    QUEUE_FULL          = 2,

    /**If the queue is empty**/
    QUEUE_EMPTY         = 3,

    /**If a NULL pointer is passed to the function**/
    QUEUE_NULL_POINTER  = 4,
}QueueStatus_t;

/***
    * Functions section
**/

/**
    *@pref      This function create and initialize a queue to the user
    *@pramt     (maxSize) the max size of the queue
    *@pramt     (*queueStatus) pointer to the queue status
    *@retval    (Queue_t *) return a pointer to the queue that has been created
**/
Queue_t *QueueDS_CreateQueue(uint32_t maxSize, QueueStatus_t *queueStatus);

/**
    *@pref      This function enqueue an element to the queue
    *@pramt     (*queue_obj) a pointer to the queue
    *@pramt     (*element_ptr) pointer to the element that want to add to the queue
    *@retval    (QueueStatus_t) return the status of the enqueue operation
**/
QueueStatus_t QueueDS_EnqueueElement(Queue_t *queue_obj, void *element_ptr);

/**
    *@pref      This function dequeue an element from the queue
    *@pramt     (*queue_obj) a pointer to the queue
    *@pramt     (*queueStatus) pointer to the queue status
    *@retval    (void *) return a pointer to the element that has been dequeued from the queue
**/
void *QueueDS_DequeueElement(Queue_t *queue_obj, QueueStatus_t *queueStatus);

/**
    *@pref      This function get the front element in the queue
    *@pramt     (*queue_obj) a pointer to the queue
    *@pramt     (*queueStatus) pointer to the queue status
    *@retval    (void *) return a pointer to the front element in the queue
**/
void *QueueDS_QueueFront(Queue_t *queue_obj, QueueStatus_t *queueStatus);

/**
    *@pref      This function get the rear element in the queue
    *@pramt     (*queue_obj) a pointer to the queue
    *@pramt     (*queueStatus) pointer to the queue status
    *@retval    (void *) return a pointer to the rear element in the queue
**/
void *QueueDS_QueueRear(Queue_t *queue_obj, QueueStatus_t *queueStatus);

/**
    *@pref      This function get the number fo element in the queue
    *@pramt     (*queue_obj) a pointer to the queue
    *@pramt     (*queueCount_ptr) pointer to the queue count
    *@retval    (QueueStatus_t) return the status of the get queue count operation
**/
QueueStatus_t QueueDS_GetQueueCount(Queue_t *queue_obj, uint32_t *queueCount_ptr);

/**
    *@pref      This function get the number fo element in the queue
    *@pramt     (*queue_obj) a pointer to the queue
    *@retval    (QueueStatus_t) return the status of the destroy operation
**/
QueueStatus_t QueueDS_DestroyQueue(Queue_t *queue_obj);



#endif // __QUEUE_DS_H__
