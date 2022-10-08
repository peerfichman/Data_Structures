#include <stdio.h>

#define MAXQUEUE 3

/*Item_type held by node is defined by customer for example we use simple int*/
typedef struct Item_type
{
    int data;

} Item_type;

/*Definition of Queue*/
typedef struct queue_tag
{
    int front;
    int rear;
    Item_type entry[MAXQUEUE];
} Queue_type;

/* Initialize: initialize queue. */
void Initialize(Queue_type *queue_ptr)
{
    queue_ptr->front = 0;
    queue_ptr->rear = -1;
}

/* AddQueue: add item to te end of the queue. */
void AddQueue(Item_type item, Queue_type *queue_ptr)
{
    if ((queue_ptr->rear == queue_ptr->front - 1 &&
         queue_ptr->rear > -1) ||
        (queue_ptr->rear == MAXQUEUE - 1 &&
         queue_ptr->front == 0))
        Error("Queue is full");
    else
    {
        queue_ptr->rear = (queue_ptr->rear + 1) % MAXQUEUE;
        queue_ptr->entry[queue_ptr->rear] = item;
    }
}

/* DeleteQueue: delete and return item in front of queue. */
void DeleteQueue(Item_type *item_ptr, Queue_type *queue_ptr)
{
    if (queue_ptr->rear <= -1)
        Error("Queue is empty");
    else
    {
        *item_ptr = queue_ptr->entry[queue_ptr->front];
        if (queue_ptr->front != queue_ptr->rear)
            queue_ptr->front = (queue_ptr->front + 1) % MAXQUEUE;
        else
        {
            queue_ptr->front = 0;
            queue_ptr->rear = -1;
        }
    }
}
