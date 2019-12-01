#include <stdio.h>
#include <stdlib.h>

#define ElementType char

struct StackRecord
{
	ElementType *Array;
	int top;
	int Capacity;
};

typedef struct StackRecord *Stack;

int isEmpty(Stack S);
int isFull(Stack S);
Stack CreatStack(int Max);
void Push(ElementType element, Stack S);
void Pop(Stack S);
void DisposeStack(Stack S);

int main()
{
	Stack S;
	S = CreatStack(50);
	//
	DisposeStack(S);
	return 0;
}

int isEmpty(Stack S)
{
	if (S->top == -1)
		return 1;
	else
		return 0;
}

int isFull(Stack S)
{
	if (S->top == S->Capacity - 1)
		return 1;
	else
		return 0;
}

Stack CreatStack(int Max)
{
	Stack S;
	S = (Stack)malloc(sizeof(struct Stack));
	if (S == NULL)
		exit(-1);

	S->Array = (ElementType*)malloc(sizeof(ElementType) * Max);
	if (S->Array == NULL)
		exit(-1);

	S->top = -1;
	S->Capacity = Max;

	return S;
}

void Push(ElementType element, Stack S)
{
	if (isFull(S) == 0)
	{
		S->top += 1;
		S->Array[S->top] = element;
	}
	else
	{
		printf("Stack is full.\n");
	}
}

void Pop(Stack S)
{
	if (isEmpty(S) == 0)
	{
		S->Array[S->top] = '\0';
		S->top -= 1;
	}
	else
	{
		printf("Stack is empty.\n");
	}
}

void DisposeStack(Stack S)
{
	if (S != NULL) {
		free(S->Array);
		free(S);
	}
}