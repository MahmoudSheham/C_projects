#include <stdio.h>
#include <stdlib.h>

#include "Queue/Queue_DS.h"
void printQueueState(QueueStatus_t queueStatus);

int main()
{
    QueueStatus_t myQueueState;
    int mahmoud = 88;
    void *data = &mahmoud;
    Queue_t *myQueue = QueueDS_CreateQueue(2, &myQueueState);
    printQueueState(myQueueState);

    myQueueState = QueueDS_EnqueueElement(myQueue, data);
    printQueueState(myQueueState);

    myQueueState = QueueDS_EnqueueElement(myQueue, data);
    printQueueState(myQueueState);

    myQueueState = QueueDS_EnqueueElement(myQueue, data);
    printQueueState(myQueueState);

    myQueueState = QueueDS_EnqueueElement(myQueue, data);
    printQueueState(myQueueState);

    myQueueState = QueueDS_EnqueueElement(myQueue, data);
    printQueueState(myQueueState);

    myQueueState = QueueDS_EnqueueElement(myQueue, data);
    printQueueState(myQueueState);

    myQueueState = QueueDS_EnqueueElement(myQueue, data);
    printQueueState(myQueueState);

    data = QueueDS_DequeueElement(myQueue, &myQueueState);
    printQueueState(myQueueState);

    data = QueueDS_QueueFront(myQueue, &myQueueState);
    printQueueState(myQueueState);

    data = QueueDS_QueueRear(myQueue, &myQueueState);
    printQueueState(myQueueState);

    myQueueState = QueueDS_EnqueueElement(myQueue, data);
    printQueueState(myQueueState);

    myQueueState = QueueDS_EnqueueElement(myQueue, data);
    printQueueState(myQueueState);

    myQueueState = QueueDS_DestroyQueue(myQueue);
    printQueueState(myQueueState);

    return 0;
}

void printQueueState(QueueStatus_t queueStatus)
{
    switch(queueStatus)
    {
        case QUEUE_EMPTY:
            printf("Queue State is QUEUE_EMPTY\n");
            break;
        case QUEUE_FULL:
            printf("Queue State is QUEUE_FULL\n");
            break;
        case QUEUE_NOK:
            printf("Queue State is QUEUE_NOK\n");
            break;
        case QUEUE_NULL_POINTER:
            printf("Queue State is QUEUE_NULL_POINTER\n");
            break;
        case QUEUE_OK:
            printf("Queue State is QUEUE_OK\n");
            break;
        default:
            printf("Error\a\n");
            break;
    }
}







