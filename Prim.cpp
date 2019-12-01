#include <stdio.h>
#include <stdlib.h>

#define VEXNUM 10
#define ARCNUM 19
#define Infinite 32767

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
	int Know;
	int Dist;
	int Path;
	ArcBox *first;
}VexNode;

typedef struct amgraph
{
	VexNode list[VEXNUM + 1]; //0∫≈ø’÷√
	int vexnum, arcnum;
}AMGraph;

typedef ArcBox *HeapType;

void CreatGraph(AMGraph &G);
void Prim(AMGraph G);
int FindMinUnknown(AMGraph G);

int main()
{
	AMGraph G;
	CreatGraph(G);
	Prim(G);
}

void CreatGraph(AMGraph &G)
{
	G.vexnum = VEXNUM;
	int i;
	for (i = 1; i <= VEXNUM; i++)
		G.list[i].first = NULL;
	ArcBox *current;
	//int buf[ARCNUM * 3] = { 1,2,2,1,4,1,2,4,3,2,5,10,1,3,4,3,6,5,3,4,2,4,6,8,4,7,4,4,5,7,5,7,6,6,7,1 };
	int buf[ARCNUM * 3] = { 1,2,3,1,4,4,1,5,4,2,5,2,2,6,3,2,3,10,3,6,6,3,7,1,4,5,5,4,8,6,5,8,2,5,9,1,5,6,11,6,9,3,6,7,2,6,10,11,7,10,8,8,9,4,9,10,7 };
	//char v1, v2;
	//scanf("%c,%c", &v1, &v2);
	for (i = 0; i < ARCNUM * 3; i += 3)
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

void Prim(AMGraph G)
{
	int i;
	for (i = 1; i <= VEXNUM; i++)
	{
		G.list[i].Know = 0;
		G.list[i].Dist = Infinite;
		G.list[i].Path = -1;
	}

	int start = 1;
	G.list[start].Dist = 0;

	int v, w;
	while (1)
	{
		v = FindMinUnknown(G);
		if (v == -1)
			break;

		G.list[v].Know = 1;
		ArcBox *current = G.list[v].first;
		while (current != NULL)
		{
			if (v == current->ivex)
				w = current->jvex;
			else
				w = current->ivex;
			if (!G.list[w].Know)
				if (current->info < G.list[w].Dist)
				{
					G.list[w].Dist = current->info;
					G.list[w].Path = v;
				}

			if (v == current->ivex)
				current = current->ilink;
			else
				current = current->jlink;
		}
	}

	for (i = 1; i <= VEXNUM; i++)
		printf("%d ", G.list[i].Path);
}

int FindMinUnknown(AMGraph G)
{
	int min = Infinite, v = -1, i;
	for (i = 1; i <= VEXNUM; i++)
	{
		if (G.list[i].Dist < min && !G.list[i].Know)
		{
			v = i;
			min = G.list[i].Dist;
		}
	}

	return v;
}