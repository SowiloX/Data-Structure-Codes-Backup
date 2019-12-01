#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ElementType int

enum KindOfEntry { Legitimate, Empty, Deleted };

typedef struct HashEntry
{
	ElementType element;
	enum KindOfEntry Info;
}Cell;

typedef struct HashTbl
{
	int TableSize;
	Cell *TheCells;
}*HashTable;

HashTable InitializeTable();
int Hash(ElementType Key);
int Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);

int main()
{
	HashTable H = InitializeTable();
	int N[7] = { 4371, 1323, 6173, 4199, 4344, 9679, 1989 };
	int i;
	for (i = 0; i < 7; i++)
		Insert(N[i], H);

	printf("| ");
	for (int i = 0; i < 10; i++)
	{
		if (H->TheCells[i].Info == Empty)
			printf("Empty | ");
		else
			printf("%d | ", H->TheCells[i].element);
	}

}

HashTable InitializeTable()
{
	HashTable H;
	int i;

	H = (HashTable)malloc(sizeof(struct HashTbl));
	if (H == NULL)
	{
		printf("Out of space!");
		exit(0);
	}

	H->TableSize = 10;

	H->TheCells = (Cell*)malloc(sizeof(Cell) * H->TableSize);
	if (H->TheCells == NULL)
	{
		printf("Out of space!");
		exit(0);
	}

	for (i = 0; i < H->TableSize; i++)
		H->TheCells[i].Info = Empty;

	return H;
}

int Hash(ElementType Key)
{
	return Key % 10;
}

int Find(ElementType Key, HashTable H)
{
	int CurrentPos;
	int CollisionNum;

	CollisionNum = 0;
	CurrentPos = Hash(Key);
	while (H->TheCells[CurrentPos].Info != Empty && H->TheCells[CurrentPos].element != Key)
	{
		CurrentPos += 2 * ++CollisionNum - 1;
		if (CurrentPos >= H->TableSize)
			CurrentPos -= H->TableSize;

	}

	return CurrentPos;
}

void Insert(ElementType Key, HashTable H)
{
	int Pos;

	Pos = Find(Key, H);
	if (H->TheCells[Pos].Info != Legitimate)
	{
		H->TheCells[Pos].Info = Legitimate;
		H->TheCells[Pos].element = Key;
	}
}
