
/*
 * Queue_DS.c
 *
 * Created: 12 Aug 23
            11:40:53 AM
 *  Author: Mahmoud Sheham
 */



#include "Queue_DS.h"

/**
    *@pref      This function create and initialize a queue to the user
    *@pramt     (maxSize) the max size of the queue
    *@pramt     (*queueStatus) pointer to the queue status
    *@retval    (Queue_t *) return a pointer to the queue that has been created
**/
Queue_t *QueueDS_CreateQueue(uint32_t maxSize, QueueStatus_t *queueStatus)
{
    Queue_t *queue_obj = NULL;

    if((NULL == queueStatus) || (0 == maxSize))
    {
        #ifdef DEBUG
        printf("Error       \a: QueueDS_CreateQueue Function \"NULL pointer is passed\"\n");;
        #endif // DEBUG
        queue_obj = NULL;
        if(queueStatus)
        {
            *queueStatus = QUEUE_NULL_POINTER;
        }
    }
    else
    {
        queue_obj = (Queue_t*)malloc(sizeof(Queue_t));
        if(!queue_obj)
        {
            *queueStatus = QUEUE_NOK;
            queue_obj =NULL;
            #ifdef DEBUG
            printf("Error       \a: QueueDS_CreateQueue Function \"Can not create the queue\"\n");
            #endif // DEBUG
        }
        else
        {
            queue_obj->QueueMaxSize = maxSize;
            queue_obj->QueueArray = (void**)calloc(queue_obj->QueueMaxSize, sizeof(void*));
            if(!queue_obj->QueueArray)
            {
                #ifdef DEBUG
                printf("Error       \a: QueueDS_CreateQueue Function \"Can not create the queue\"\n");
                #endif // DEBUG
                *queueStatus = QUEUE_NOK;
                free(queue_obj);
                queue_obj = NULL;
            }
            else
            {
                #ifdef DEBUG
                printf("Notification: QueueDS_CreateQueue Function \"The queue created successfully\"\n");
                #endif // DEBUG
                queue_obj->QueueFront = -1;
                queue_obj->QueueRear = -1;
                queue_obj->QueueCount = 0;
                *queueStatus = QUEUE_OK;
            }
        }
    }

    return queue_obj;
}

/**
    *@pref      This function enqueue an element to the queue
    *@pramt     (*queue_obj) a pointer to the queue
    *@pramt     (*element_ptr) pointer to the element that want to add to the queue
    *@retval    (QueueStatus_t) return the status of the enqueue operation
**/
QueueStatus_t QueueDS_EnqueueElement(Queue_t *queue_obj, void *element_ptr)
{
    QueueStatus_t queueStatus = QUEUE_NOK;

    if((NULL == queue_obj) || (NULL == element_ptr))
    {
        #ifdef DEBUG
        printf("Error       \a: QueueDS_EnqueueElement Function \"NULL pointer is passed\"\n");
        #endif // DEBUG
        queueStatus = QUEUE_NULL_POINTER;
    }
    else
    {
        if(queue_obj->QueueCount == queue_obj->QueueMaxSize)
        {
            #ifdef DEBUG
            printf("Error       \a: QueueDS_EnqueueElement Function \"Queue is full\"\n");
            #endif // DEBUG
            queueStatus = QUEUE_FULL;
        }
        else
        {
            if(0 == queue_obj->QueueCount)
            {
                queue_obj->QueueCount = 1;
                queue_obj->QueueFront = 0;
                queue_obj->QueueRear = 0;
                queue_obj->QueueArray[queue_obj->QueueRear] = element_ptr;
                queueStatus = QUEUE_OK;
            }
            else
            {
                (queue_obj->QueueCount)++;
                queue_obj->QueueRear = (queue_obj->QueueRear + 1) % (queue_obj->QueueMaxSize);
                queue_obj->QueueArray[queue_obj->QueueRear] = element_ptr;
                queueStatus = QUEUE_OK;
            }
            #ifdef DEBUG
            printf("Notification: QueueDS_EnqueueElement Function \"The element is enqueued successfully\"\n");
            #endif // DEBUG
        }
    }

    return queueStatus;
}

/**
    *@pref      This function dequeue an element from the queue
    *@pramt     (*queue_obj) a pointer to the queue
    *@pramt     (*queueStatus) pointer to the queue status
    *@retval    (void *) return a pointer to the element that has been dequeued from the queue
**/
void *QueueDS_DequeueElement(Queue_t *queue_obj, QueueStatus_t *queueStatus)
{
    void *data_ptr = NULL;

    if((NULL == queue_obj) || (NULL == queueStatus))
    {
        data_ptr = NULL;
        if(queueStatus)
        {
            #ifdef DEBUG
            printf("Error       \a: QueueDS_DequeueElement Function \"NULL pointer is passed\"\n");
            #endif // DEBUG
            *queueStatus = QUEUE_NULL_POINTER;
        }
    }
    else
    {
        if(0 == queue_obj->QueueCount)
        {
            #ifdef DEBUG
            printf("Error       \a: QueueDS_DequeueElement Function \"Queue is empty\"\n");
            #endif // DEBUG
            *queueStatus = QUEUE_EMPTY;
            data_ptr = NULL;
        }
        else
        {
            if(1 == queue_obj->QueueCount)
            {
                data_ptr = queue_obj->QueueArray[queue_obj->QueueFront];
                queue_obj->QueueCount = 0;
                queue_obj->QueueFront = -1;
                queue_obj->QueueRear = -1;
                *queueStatus = QUEUE_OK;
            }
            else
            {
                data_ptr = queue_obj->QueueArray[queue_obj->QueueFront];
                queue_obj->QueueCount--;
                queue_obj->QueueFront = (queue_obj->QueueFront + 1) %(queue_obj->QueueMaxSize);
                *queueStatus = QUEUE_OK;
            }
            #ifdef DEBUG
            printf("Notification: QueueDS_DequeueElement Function \"The element is dequeued successfully\"\n");
            #endif // DEBUG
        }
    }

    return data_ptr;
}

/**
    *@pref      This function get the front element in the queue
    *@pramt     (*queue_obj) a pointer to the queue
    *@pramt     (*queueStatus) pointer to the queue status
    *@retval    (void *) return a pointer to the front element in the queue
**/
void *QueueDS_QueueFront(Queue_t *queue_obj, QueueStatus_t *queueStatus)
{
    void *data_ptr = NULL;

    if((NULL == queue_obj) || (NULL == queueStatus))
    {
        #ifdef DEBUG
        printf("Error       \a: QueueDS_QueueFront Function \"NULL pointer is passed\"\n");
        #endif // DEBUG
        data_ptr = NULL;
        if(queueStatus)
        {
            *queueStatus = QUEUE_NULL_POINTER;
        }
    }
    else
    {
        if(0 == queue_obj->QueueCount)
        {
            #ifdef DEBUG
            printf("Error       \a: QueueDS_QueueFront Function \"Queue is empty\"\n");
            #endif // DEBUG
            *queueStatus = QUEUE_EMPTY;
            data_ptr = NULL;
        }
        else
        {
            #ifdef DEBUG
            printf("Notification: QueueDS_QueueFront Function \"The front is get successfully\"\n");
            #endif // DEBUG
            data_ptr = queue_obj->QueueArray[queue_obj->QueueFront];
            *queueStatus = QUEUE_OK;
        }
    }

    return data_ptr;
}

/**
    *@pref      This function get the rear element in the queue
    *@pramt     (*queue_obj) a pointer to the queue
    *@pramt     (*queueStatus) pointer to the queue status
    *@retval    (void *) return a pointer to the rear element in the queue
**/
void *QueueDS_QueueRear(Queue_t *queue_obj, QueueStatus_t *queueStatus)
{
    void *data_ptr = NULL;

    if((NULL == queue_obj) || (NULL == queueStatus))
    {
        #ifdef DEBUG
        printf("Error       \a: QueueDS_QueueRear Function \"NULL pointer is passed\"\n");
        #endif // DEBUG
        data_ptr = NULL;
        if(queueStatus)
        {
            *queueStatus = QUEUE_NULL_POINTER;
        }
    }
    else
    {
        if(0 == queue_obj->QueueCount)
        {
            #ifdef DEBUG
            printf("Error       \a: QueueDS_QueueRear Function \"The queue is empty\"\n");
            #endif // DEBUG
            *queueStatus = QUEUE_EMPTY;
            data_ptr = NULL;
        }
        else
        {
            #ifdef DEBUG
            printf("Notification: QueueDS_QueueRear Function \"The rear is get successfully\"\n");
            #endif // DEBUG
            data_ptr = queue_obj->QueueArray[queue_obj->QueueRear];
            *queueStatus = QUEUE_OK;
        }
    }

    return data_ptr;
}

/**
    *@pref      This function get the number fo element in the queue
    *@pramt     (*queue_obj) a pointer to the queue
    *@pramt     (*queueCount_ptr) pointer to the queue count
    *@retval    (QueueStatus_t) return the status of the get queue count operation
**/
QueueStatus_t QueueDS_GetQueueCount(Queue_t *queue_obj, uint32_t *queueCount_ptr)
{
    QueueStatus_t queueStatus = QUEUE_NOK;

    if((NULL == queue_obj) || (NULL == queueCount_ptr))
    {
        #ifdef DEBUG
        printf("Error       \a: QueueDS_GetQueueCount Function \"NULL pointer is passed\"\n");
        #endif // DEBUG
        queueStatus = QUEUE_NULL_POINTER;
        *queueCount_ptr = -1;
    }
    else
    {
        if(queue_obj->QueueCount == queue_obj->QueueMaxSize)
        {
            #ifdef DEBUG
            printf("Notification: QueueDS_GetQueueCount Function \"Queue is full\"\n");
            #endif // DEBUG
            queueStatus = QUEUE_FULL;
        }
        else if(0 == queue_obj->QueueCount)
        {
            #ifdef DEBUG
            printf("Notification: QueueDS_GetQueueCount Function \"Queue is empty\"\n");
            #endif // DEBUG
            queueStatus = QUEUE_EMPTY;
        }
        else
        {
            #ifdef DEBUG
            printf("Notification: QueueDS_GetQueueCount Function \"Queue not full not empty\"\n");
            #endif // DEBUG
            queueStatus = QUEUE_OK;
        }
        *queueCount_ptr = queue_obj->QueueCount;
    }

    return queueStatus;
}

/**
    *@pref      This function get the number fo element in the queue
    *@pramt     (*queue_obj) a pointer to the queue
    *@retval    (QueueStatus_t) return the status of the destroy operation
**/
QueueStatus_t QueueDS_DestroyQueue(Queue_t *queue_obj)
{
    QueueStatus_t queueStatus = QUEUE_NOK;

    if(!queue_obj)
    {
        #ifdef DEBUG
        printf("Error       \a: QueueDS_DestroyQueue Function \"NULL pointer is passed\"\n");
        #endif // DEBUG
        queueStatus = QUEUE_NULL_POINTER;
    }
    else
    {
        if(!queue_obj->QueueArray)
        {
            #ifdef DEBUG
            printf("Error       \a: QueueDS_DestroyQueue Function \"NULL pointer is passed\"\n");
            #endif // DEBUG
            free(queue_obj);
            queueStatus = QUEUE_NULL_POINTER;
        }
        else
        {
            #ifdef DEBUG
            printf("Notification: QueueDS_DestroyQueue Function \"Queue destroyed successfully\"\n");
            #endif // DEBUG
            free(queue_obj->QueueArray);
            free(queue_obj);
            queue_obj = NULL;
            queueStatus = QUEUE_OK;
        }
    }

    return queueStatus;
}


