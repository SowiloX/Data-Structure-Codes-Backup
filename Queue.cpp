#include <stdio.h>
#include <stdlib.h>

#define QueueType int

typedef struct queue
{
	int front;
	int rear;
	QueueType *Array;
	int Capacity;
}*Queue;

Queue CreatQueue(int size);
int isEmpty(Queue Q);
int isFull(Queue Q);
void Enqueue(QueueType X, Queue Q);
void Dequeue(Queue Q);
void DisposeQueue(Queue Q);

int main()
{
	Queue Q;
	Q = CreatQueue(50);

	DisposeQueue(Q);
}

Queue CreatQueue(int size)
{
	Queue Q;
	Q = (Queue)malloc(sizeof(struct queue));
	Q->front = 0;
	Q->rear = 1;
	Q->Array = (QueueType *)malloc(sizeof(QueueType) * size);
	Q->Capacity = size;

	return Q;
}

int isEmpty(Queue Q)
{
	if ((Q->rear - Q->front) == 1)
		return 1;
	else
		return 0;
}

int isFull(Queue Q)
{
	if (Q->rear == Q->front)
		return 1;
	else
		return 0;
}

void Enqueue(QueueType X, Queue Q)
{
	if (isFull(Q) == 1)
		printf("Queue is Full!");
	else
	{
		Q->Array[Q->rear - 1] = X;
		Q->rear = (Q->rear + 1) % Q->Capacity;
	}
}

void Dequeue(Queue Q)
{
	if (isEmpty(Q) == 1)
		printf("Queue is Empty!");
	else
	{
		Q->front = (Q->front + 1) % Q->Capacity;
	}
}

void DisposeQueue(Queue Q)
{
	if (Q != NULL)
	{
		free(Q->Array);
		free(Q);
	}
}