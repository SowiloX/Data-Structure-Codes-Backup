#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElementType int

typedef struct AvlNode
{
	ElementType Element;
	struct AvlNode *Left;
	struct AvlNode *Right;
	int Height;
}*Position, *AvlTree;

AvlTree MakeEmpty(AvlTree T);
//Position Find(ElementType X, AvlTree T);
//Position FindMax(AvlTree T);
//Position FindMin(AvlTree T);
AvlTree Insert(ElementType X, AvlTree T);
static Position SingleRotateWithLeft(Position K2);
static Position SingleRotateWithRight(Position K1);
static Position DoubleRotateWithLeft(Position K3);
static Position DoubleRotateWithRight(Position K3);
static int GetHeight(Position P);
int Max(int A, int B);
void Preorder(AvlTree T);

int main()
{
	AvlTree T = NULL;

	char str[500] = { '\0' }, *buf;
	fgets(str, 500, stdin);
	buf = strtok(str, ",");
	while (buf && *buf != '\n')
	{
		T = Insert(atoi(buf), T);
		buf = strtok(NULL, ",");
	}

	Preorder(T);

	MakeEmpty(T);
}

AvlTree MakeEmpty(AvlTree T)
{
	if (T != NULL)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}

	return T;
}

AvlTree Insert(ElementType X, AvlTree T)
{
	if (T == NULL)
	{
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		if (T == NULL)
		{
			printf("Out of Space\n");
			exit(-1);
		}
		else
		{
			T->Element = X;
			T->Height = 0;
			T->Left = T->Right = NULL;
		}
	}
	else if (X < T->Element)
	{
		T->Left = Insert(X, T->Left);
		if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
		{
			if (X < T->Left->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
		}
	}
	else if (X > T->Element)
	{
		T->Right = Insert(X, T->Right);
		if (GetHeight(T->Right) - GetHeight(T->Left) == 2)
		{
			if (X > T->Right->Element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
		}
	}

	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;

	return T;
}

static Position SingleRotateWithLeft(Position K2)
{
	Position K1;

	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = Max(GetHeight(K2->Left), GetHeight(K2->Right)) + 1;
	K1->Height = Max(GetHeight(K1->Left), K2->Height) + 1;

	return K1;
}

static Position SingleRotateWithRight(Position K1)
{
	Position K2;

	K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;

	K1->Height = Max(GetHeight(K1->Left), GetHeight(K1->Right)) + 1;
	K2->Height = Max(K1->Height, GetHeight(K2->Right)) + 1;

	return K2;
}

static Position DoubleRotateWithLeft(Position K3)
{
	K3->Left = SingleRotateWithRight(K3->Left);
	K3 = SingleRotateWithLeft(K3);

	return K3;
}

static Position DoubleRotateWithRight(Position K3)
{
	K3->Right = SingleRotateWithLeft(K3->Right);
	K3 = SingleRotateWithRight(K3);

	return K3;
}

static int GetHeight(Position P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}

int Max(int A, int B)
{
	if (A > B)
		return A;
	else
		return B;
}

void Preorder(AvlTree T)
{
	if (T)
	{
		printf("%d,", T->Element);
		Preorder(T->Left);
		Preorder(T->Right);
	}
}
