#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

using namespace std;

#define ElementType int
#define MAX 20 // length of the array

typedef struct BinNode
{
	ElementType Element;
	struct BinNode *Left;
	struct BinNode *Next;
}*Position, *BinTree;

typedef struct collection
{
	int Size;
	BinTree Tree[MAX];
}*BinQueue;

BinTree CombineTrees(BinTree T1, BinTree T2);
BinQueue Merge(BinQueue H1, BinQueue H2);
ElementType DeleteMin(BinQueue H);
BinQueue Insert(ElementType X, BinQueue H);
BinQueue CreateQueue();
void Travel(BinTree T);
void TravelSiblings(BinTree T, queue<BinTree> &Q);

int main()
{
	BinQueue H = CreateQueue();
	char foo[100] = { '\0' }, *bar;
	int N;

	fgets(foo, 100, stdin);
	bar = strtok(foo, ",");
	while (bar && *bar != '\n')
	{
		H = Insert(atoi(bar), H);
		bar = strtok(NULL, ",");
	}

	scanf("%d", &N);

	if (H->Tree[N] == NULL)
		printf("0,");
	else
		Travel(H->Tree[N]);
}

BinTree CombineTrees(BinTree T1, BinTree T2) //T1's element < T2's element
{
	if (T1->Element > T2->Element)
		return CombineTrees(T2, T1);

	T2->Next = T1->Left;
	T1->Left = T2;
	return T1;
}

BinQueue Merge(BinQueue H1, BinQueue H2)
{
	BinTree T1, T2, Carry = NULL;
	int i, j;

	if (H1->Size + H2->Size > (1 << MAX) - 1)
	{
		printf("Exceed Capacity");
		return H1;
	}

	H1->Size += H2->Size;
	for (i = 0, j = 1; j <= H1->Size; i++, j *= 2)
	{
		T1 = H1->Tree[i];
		T2 = H2->Tree[i];

		switch (!!T1 + 2 * !!T2 + 4 * !!Carry) //Carry is the result of combining two Tree[i], and it should be inserted at Tree[i+1]
		{
		case 0: // No Trees
		case 1: // Only H1
			break;
		case 2: // Only H2
			H1->Tree[i] = T2;
			H2->Tree[i] = NULL;
			break;
		case 4: // Only Carry
			H1->Tree[i] = Carry;
			Carry = NULL;
			break;
		case 3: // H1 & H2
			Carry = CombineTrees(T1, T2);
			H1->Tree[i] = H2->Tree[i] = NULL;
			break;
		case 5: // H1 & Carry
			Carry = CombineTrees(T1, Carry);
			H1->Tree[i] = NULL;
			break;
		case 6: // H2 & Carry
			Carry = CombineTrees(T2, Carry);
			H2->Tree[i] = NULL;
			break;
		case 7: // All
			H1->Tree[i] = Carry;
			Carry = CombineTrees(T1, T2);
			H2->Tree[i] = NULL;
			break;
		}
	}

	return H1;
}

ElementType DeleteMin(BinQueue H)
{
	int i, j;
	int MinTree;
	ElementType MinItem;

	MinItem = 32767;
	for (i = 0; i < MAX; i++) // Find the tree whose root is minimun element
	{
		if (H->Tree[i] && H->Tree[i]->Element < MinItem)
		{
			MinItem = H->Tree[i]->Element;
			MinTree = i;
		}
	}

	BinQueue DeletedQueue;
	Position DeletedTree, OldRoot;

	DeletedTree = H->Tree[MinTree]; // Remove the tree
	H->Tree[MinTree] = NULL;
	OldRoot = DeletedTree; // Free the root and make its left child be the new root
	DeletedTree = DeletedTree->Left;
	free(OldRoot);

	DeletedQueue = CreateQueue(); // Creat a new queue to store the removed tree
	DeletedQueue->Size = (1 << MinTree) - 1;
	for (j = MinTree - 1; j >= 0; j--) // Split the tree
	{
		DeletedQueue->Tree[j] = DeletedTree;
		DeletedTree = DeletedTree->Next;
		DeletedQueue->Tree[j]->Next = NULL;
	}

	H->Tree[MinTree] = NULL;
	H->Size -= DeletedQueue->Size + 1;

	Merge(H, DeletedQueue);
	return MinItem;
}

BinQueue Insert(ElementType X, BinQueue H)
{
	BinQueue H0;
	H0 = CreateQueue();

	H0->Size = 1;
	H0->Tree[0] = (BinTree)malloc(sizeof(struct BinNode));
	if (H0->Tree[0] == NULL)
	{
		printf("Out of Space");
		exit(-1);
	}

	H0->Tree[0]->Element = X;
	H0->Tree[0]->Left = H0->Tree[0]->Next = NULL;

	return Merge(H, H0);
}

BinQueue CreateQueue()
{
	BinQueue H;
	H = (BinQueue)malloc(sizeof(struct collection));
	if (H == NULL)
	{
		printf("Out of Space");
		exit(-1);
	}

	H->Size = 0;
	for (int i = 0; i < MAX; i++)
		H->Tree[i] = NULL;

	return H;
}

void Traverse(BinTree T)
{
	queue<BinTree> Q;
	BinTree tmp;
	Q.push(T);
	while (!Q.empty())
	{
		tmp = Q.front();
		printf("%d,", tmp->Element);
		Q.pop();
		TravelSiblings(tmp->Left, Q);
	}
}

void TraverseSiblings(BinTree T, queue<BinTree> &Q)
{
	if (T)
	{
		TravelSiblings(T->Next, Q);
		Q.push(T);
	}
}