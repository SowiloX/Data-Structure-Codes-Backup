/*
* Hash Table
*  Separate Chaining
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElementType int

typedef struct ListNode
{
	ElementType Element;
	struct ListNode *next;
}*Position, *List;

typedef struct HashTbl
{
	int TableSize;
	List *TheLists;
}*HashTable;

HashTable IniTable();
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
int Hash(ElementType Key, int TableSize);

int main()
{
	HashTable H;
	H = IniTable();

	int N[7] = { 4371, 1323, 6173, 4199, 4344, 9679, 1989 };
	int i;
	for (i = 0; i < 7; i++)
		Insert(N[i], H);

	for (int i = 0; i < 10; i++)
	{
		printf("Box %d: ", i);
		Position current = H->TheLists[i]->next;
		if (current == NULL)
			printf("Empty\n");
		else
		{
			while (current != NULL)
			{
				if (current->next == NULL)
					printf("%d\n", current->Element);
				else
					printf("%d -> ", current->Element);
				current = current->next;
			}
		}
	}

	DestroyTable(H);
}

HashTable IniTable()
{
	HashTable H;
	int i;

	H = (HashTable)malloc(sizeof(struct HashTbl));
	if (H == NULL)
	{
		printf("Out of Space!");
		exit(-1);
	}

	H->TableSize = 100;

	H->TheLists = (List*)malloc(H->TableSize * sizeof(List)); //a dynamic array, the element type is linked list (a pointer of ListNode)
	if (H->TheLists == NULL)
	{
		printf("Out of Space!");
		exit(-1);
	}

	for (i = 0; i < H->TableSize; i++)
	{
		H->TheLists[i] = (List)malloc(sizeof(struct ListNode)); //allocate the head of each linked list in the array
		if (H->TheLists[i] == NULL)
		{
			printf("Out of Space!");
			exit(-1);
		}
		else
			H->TheLists[i]->next = NULL;
	}

	return H;
}

Position Find(ElementType Key, HashTable H)
{
	Position P;
	List L;

	L = H->TheLists[Hash(Key, H->TableSize)];
	P = L->next;
	//while (P != NULL && strcmp(P->Element, Key) == 1)
	while (P != NULL && P->Element != Key)
		P = P->next;

	return P;
}

void Insert(ElementType Key, HashTable H)
{
	List L;
	Position Pos, NewCell;

	Pos = Find(Key, H);
	if (Pos == NULL)
	{
		NewCell = (List)malloc(sizeof(struct ListNode));
		if (NewCell == NULL)
		{
			printf("Out of Space!");
			exit(-1);
		}
		else
		{
			L = H->TheLists[Hash(Key, H->TableSize)];
			//strcpy(NewCell->Element, Key);
			NewCell->Element = Key;
			NewCell->next = L->next;
			L->next = NewCell;
		}
	}
}

void DestroyTable(HashTable H)
{
	List tmp, L;
	int i;
	for (i = 0; i < H->TableSize; i++)
	{
		L = H->TheLists[i];
		while (L->next != NULL)
		{
			tmp = L->next;
			L->next = tmp->next;
			free(tmp);
		}
	}
	free(H->TheLists);
	free(H);
}

int Hash(ElementType Key, int TableSize)
{
	/*unsigned int HashVal = 0;

	while (*Key != '\0')
		HashVal = (HashVal << 5) + *Key++;

	return HashVal % TableSize;*/

	return Key % 10;
}