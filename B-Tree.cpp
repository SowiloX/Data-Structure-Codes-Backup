#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElementType int

typedef struct bnode
{
	ElementType *Key;
	struct bnode **Child;
	struct bnode *Parent;
	int Size;
}*BNode;

typedef struct btree
{
	int Max;
	int Min;
	int split;
	BNode Root;
}BTree;

void CreatBTree(BTree &T, int M);
void BTreeInsert(BTree &T, int X);
BNode CreatBNode(BTree T);
void SplitBTree(BTree &T, BNode Node);
void Travel(BNode Root);

int main()
{
	BTree T;
	CreatBTree(T, 5);
	int A[10] = { 1,2,3,4,5,6,7,8,9,10 };
	for (int i = 0; i < 10; i++)
		BTreeInsert(T, A[i]);

	Traverse(T.Root);
}

void CreatBTree(BTree &T, int M)
{
	T.Root = NULL;
	T.Max = M - 1;
	T.Min = M / 2;
	if (M % 2 != 0)
		T.Min++;
	T.Min--;
	T.split = M / 2;
}

void BTreeInsert(BTree &T, int X)
{
	if (T.Root == NULL)
	{
		T.Root = CreatBNode(T);
		T.Root->Size++;
		T.Root->Key[0] = X;
	}
	else
	{
		BNode current = T.Root;
		int i;
		while (current != NULL)
		{
			for (i = 0; i < current->Size; i++)
			{
				if (X < current->Key[i])
					break;
			}

			if (current->Child[i] != NULL)
				current = current->Child[i];
			else
				break;
		}

		for (int j = current->Size; j > i; j--)
			current->Key[j] = current->Key[j - 1];
		current->Key[i] = X;
		current->Size++;

		if (current->Size > T.Max)
			SplitBTree(T, current);
	}
}

BNode CreatBNode(BTree T)
{
	BNode Node = NULL;
	Node = (BNode)malloc(sizeof(struct bnode));
	if (Node == NULL)
	{
		printf("Out of Space!");
		exit(-1);
	}

	Node->Size = 0;
	Node->Parent = NULL;
	Node->Key = (ElementType*)malloc((T.Max + 1) * sizeof(ElementType)); //�����һ��λ�÷����ƶ�
	if (Node->Key == NULL)
	{
		printf("Out of Space!");
		exit(-1);
	}

	Node->Child = (BNode*)malloc((T.Max + 2) * sizeof(struct bnode *));
	if (Node->Child == NULL)
	{
		printf("Out of Space!");
		exit(-1);
	}
	for (int i = 0; i <= T.Max + 1; i++)
		Node->Child[i] = NULL;

	return Node;
}

void SplitBTree(BTree &T, BNode Node)
{
	while (Node->Size > T.Max)
	{
		int total = Node->Size;
		BNode NewNode = NULL;

		NewNode = CreatBNode(T);
		memcpy(NewNode->Key, Node->Key + T.split + 1, sizeof(ElementType) * (total - T.split - 1));
		memcpy(NewNode->Child, Node->Child + T.split + 1, sizeof(BNode) * (total - T.split));
		NewNode->Parent = Node->Parent;
		NewNode->Size = total - T.split - 1;
		Node->Size = T.split;

		BNode parent = Node->Parent;
		if (parent == NULL)
		{
			parent = CreatBNode(T);
			T.Root = parent;
			parent->Child[0] = Node;
			parent->Child[1] = NewNode;
			Node->Parent = parent;
			NewNode->Parent = parent;
			parent->Key[0] = Node->Key[T.split];
			parent->Size++;
		}
		else
		{
			int i;
			for (i = parent->Size; i > 0; i--)
			{
				if (Node->Key[T.split] < parent->Key[i - 1])
				{
					parent->Key[i] = parent->Key[i - 1];
					parent->Child[i + 1] = parent->Child[i];
				}
				else
					break;
			}
			parent->Key[i] = Node->Key[T.split];
			parent->Child[i + 1] = NewNode;
			NewNode->Parent = parent;
			parent->Size++;
		}

		for (int i = T.split; i < T.Max; i++)
		{
			Node->Key[i] = 0;
			Node->Child[i + 1] = NULL;
		}

		for (int i = 0; i <= NewNode->Size; i++)
		{
			if (NewNode->Child[i] != NULL)
				NewNode->Child[i]->Parent = NewNode;
		}

		Node = parent;
	}
}

void Traverse(BNode Root)
{
	if (Root)
	{
		BNode current = Root;
		for (int i = 0; i < current->Size; i++)
			printf("%d ", current->Key[i]);
		printf("\n");
		for (int i = 0; i <= current->Size; i++)
			Traverse(current->Child[i]);
	}
}