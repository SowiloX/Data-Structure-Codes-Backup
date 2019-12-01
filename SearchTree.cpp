//Search Tree
#include <stdio.h>
#include <stdlib.h>

#define ElementType char

typedef struct TreeNode {
	ElementType data;
	struct TreeNode *Left, *Right;
}*Position, *SearchTree;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);
void Preorder(SearchTree T);
void Inorder(SearchTree T);
void Postorder(SearchTree T);

int main()
{
	SearchTree T = NULL;

	T = MakeEmpty(T);
}

SearchTree MakeEmpty(SearchTree T)
{
	if (T != NULL)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}

	return NULL;
}

Position Find(ElementType X, SearchTree T)
{
	if (T == NULL)
		return NULL;

	if (X < T->data)
		return Find(X, T->Left);
	else if (X > T->data)
		return Find(X, T->Right);
	else
		return T;
}

Position FindMin(SearchTree T)
{
	if (T == NULL)
		return T;
	else if (T->Left == NULL)
		return T;
	else
		return FindMin(T->Left);
}

Position FindMax(SearchTree T)
{
	if (T == NULL)
		return T;
	else if (T->Right == NULL)
		return T;
	else
		return FindMax(T->Right);
}

SearchTree Insert(ElementType X, SearchTree T)
{
	if (T == NULL)
	{
		T = (SearchTree)malloc(sizeof(struct TreeNode));
		if (T == NULL)
			exit(-1);
		else
		{
			T->data = X;
			T->Left = NULL;
			T->Right = NULL;
		}
	}
	else if (X < T->data)
		T->Left = Insert(X, T->Left);
	else if (X > T->data)
		T->Right = Insert(X, T->Right);

	return T;
}

SearchTree Delete(ElementType X, SearchTree T)
{
	Position TmpCell;

	if (T == NULL)
	{
		printf("NOT FOUND\n");
		return NULL;
	}
	else if (X < T->data)
		T->Left = Delete(X, T->Left);
	else if (X > T->data)
		T->Right = Delete(X, T->Right);
	else if (T->Left && T->Right)
	{
		TmpCell = FindMin(T->Right);
		T->data = TmpCell->data;
		T->Right = Delete(T->data, T->Right);
	}
	else
	{
		TmpCell = T;
		if (T->Left == NULL)
			T = T->Right;
		else if (T->Right == NULL)
			T = T->Left;

		free(TmpCell);
	}

	return T;
}

void Preorder(SearchTree T)
{
	if (T)
	{
		printf("%c ", T->data);
		Preorder(T->Left);
		Preorder(T->Right);
	}
}

void Inorder(SearchTree T)
{
	if (T)
	{
		Inorder(T->Left);
		printf("%c ", T->data);
		Inorder(T->Right);
	}
}

void Postorder(SearchTree T)
{
	if (T)
	{
		Postorder(T->Left);
		Postorder(T->Right);
		printf("%c ", T->data);
	}
}