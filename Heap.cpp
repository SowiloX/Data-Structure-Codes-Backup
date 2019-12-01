#include <stdio.h>
#include <stdlib.h>

#define HeapType int

typedef struct heap
{
	int Capacity;
	int Size;
	HeapType *Element;
}*Heap;

Heap CreatHeap(int Max);
void Insert(HeapType X, Heap H);
HeapType DeleteMin(Heap H);

int main()
{
	Heap H;
	H = CreatHeap(50);
	int i;
	for (i = 36; i > 5; i--)
		Insert(i, H);
	for (i = 1; i <= H->Size; i++)
		printf("%d ", H->Element[i]);
	DeleteMin(H);
	printf("\n");
	for (i = 1; i <= H->Size; i++)
		printf("%d ", H->Element[i]);
}

Heap CreatHeap(int Max)
{
	Heap H;
	H = (Heap)malloc(sizeof(struct heap));
	if (H == NULL)
	{
		printf("Out of Space!");
		exit(-1);
	}

	H->Element = (HeapType *)malloc(sizeof(HeapType) * (Max + 1)); //多一位给哑值
	if (H->Element == NULL)
	{
		printf("Out of Space!");
		exit(-1);
	}

	H->Capacity = Max;
	H->Size = 0;
	H->Element[0] = -32767;

	return H;
}

void Insert(HeapType X, Heap H)
{
	if (H->Size == H->Capacity)
		printf("Heap is full!");
	else
	{
		int i;
		for (i = ++H->Size; H->Element[i / 2] > X; i /= 2)
			H->Element[i] = H->Element[i / 2];
		H->Element[i] = X;
	}
}

HeapType DeleteMin(Heap H)
{
	if (H->Size == 0)
		printf("Heap is empty!");
	else
	{
		int i, Child;
		HeapType Min, Last;
		Min = H->Element[1];
		Last = H->Element[H->Size--];

		for (i = 1; i * 2 <= H->Size; i = Child)
		{
			Child = i * 2;
			if (Child != H->Size && H->Element[Child + 1] < H->Element[Child])
				Child++;
			if (Last > H->Element[Child])
				H->Element[i] = H->Element[Child];
			else
				break;
		}
		H->Element[i] = Last;
		return Min;
	}
}