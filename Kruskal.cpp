#include <stdio.h>
#include <stdlib.h>

#define VEXNUM 10
#define Set_Num 100

typedef int Info;
typedef int DataType;
typedef struct arcbox
{
	int ivex, jvex;
	struct arcbox *ilink, *jlink;
	Info info;
}ArcBox;

typedef struct vexnode
{
	int data;
	ArcBox *first;
}VexNode;

typedef struct amgraph
{
	VexNode list[VEXNUM + 1]; //0号空置
	int vexnum, arcnum;
}AMGraph;

typedef ArcBox *HeapType;

typedef struct heap
{
	int Capacity;
	int Size;
	HeapType *Element;
}*Heap;

typedef int SetType;
typedef int DisjSet[Set_Num + 1];

Heap CreatHeap(int Max);
void Insert(HeapType X, Heap H);
HeapType DeleteMin(Heap H);
void CreatGraph(AMGraph &G);
SetType Find(int X, DisjSet S);
void SetUnion(DisjSet S, SetType Root1, SetType Root2);
void Kruskal(AMGraph G);

int main()
{
	AMGraph G;
	CreatGraph(G);
	Kruskal(G);
}

void CreatGraph(AMGraph &G)
{
	G.vexnum = VEXNUM;
	int i;
	for (i = 1; i <= VEXNUM; i++)
		G.list[i].first = NULL;
	ArcBox *current;
	int buf[57] = { 1,2,3,1,4,4,1,5,4,2,5,2,2,6,3,2,3,10,3,6,6,3,7,1,4,5,5,4,8,6,5,8,2,5,9,1,5,6,11,6,9,3,6,7,2,6,10,11,7,10,8,8,9,4,9,10,7 };
	//char v1, v2;
	//scanf("%c,%c", &v1, &v2);
	for (i = 0; i < 57; i += 3)
	{
		//if ((buf[i] == v1 - 64 && buf[i + 1] == v2 - 64) || (buf[i] == v2 - 64 && buf[i + 1] == v1 - 64))
		//	continue;
		current = (ArcBox *)malloc(sizeof(ArcBox));
		current->ivex = buf[i];
		current->jvex = buf[i + 1];
		current->info = buf[i + 2];
		current->ilink = G.list[buf[i]].first;
		current->jlink = G.list[buf[i + 1]].first;
		G.list[buf[i]].first = current;
		G.list[buf[i + 1]].first = current;
	}
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

	int i;
	for (i = 0; i < Max; i++)
		H->Element[i] = (ArcBox *)malloc(sizeof(ArcBox));
	H->Element[0]->info = -32767; //哑值

	return H;
}

void Insert(HeapType X, Heap H)
{
	if (H->Size == H->Capacity)
		printf("Heap is full!");
	else
	{
		int i;
		for (i = ++H->Size; H->Element[i / 2]->info > X->info; i /= 2)
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
			if (Child != H->Size && H->Element[Child + 1]->info < H->Element[Child]->info)
				Child++;
			if (Last->info > H->Element[Child]->info)
				H->Element[i] = H->Element[Child];
			else
				break;
		}
		H->Element[i] = Last;
		return Min;
	}
}

SetType Find(int X, DisjSet S)
{
	if (S[X] <= 0)
		return X;
	else
		return Find(S[X], S);
}

void SetUnion(DisjSet S, SetType Root1, SetType Root2)
{
	if (S[Root2] < S[Root1])
		S[Root1] = Root2;
	else
	{
		if (S[Root1] == S[Root2])
			S[Root1]--;
		S[Root2] = Root1;
	}
}

void Kruskal(AMGraph G)
{
	int EdgesAcccepted, i;
	ArcBox *current;
	DisjSet S;
	Heap H;
	SetType Uset, Vset;

	for (i = Set_Num; i > 0; i--) //初始化集合（树）S
		S[i] = 0;

	H = CreatHeap(100);
	for (i = 1; i <= VEXNUM; i++) //将弧节点放入堆
		for (current = G.list[i].first; current != NULL && current->ivex == i; current = current->ilink)
			Insert(current, H);

	EdgesAcccepted = 0;
	while (EdgesAcccepted < VEXNUM - 1) //N个节点的生成树为N-1条边，当EdgesAccepted达到N-1停止循环
	{
		current = DeleteMin(H);
		Uset = Find(current->ivex, S);
		Vset = Find(current->jvex, S);
		if (Uset != Vset)
		{
			EdgesAcccepted++;
			SetUnion(S, Uset, Vset);
			printf("%d,%d   ", current->ivex, current->jvex); //打印接受的边
			for (i = 1; i <= VEXNUM; i++) //打印此时的集合S
				printf("%d ", S[i]);
			printf("\n");
			//printf("%d,", current->info);
		}
	}
}