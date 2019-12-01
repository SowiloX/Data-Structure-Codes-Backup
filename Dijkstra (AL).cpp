/*赋权，无负值*/
#include <stdio.h>
#include <stdlib.h>

#define VEXNUM 7
#define Info int
#define DataType int
#define Infinite 32767
typedef struct arcbox
{
	int adjvex;
	struct arcbox *next;
	Info info;
}ArcBox;

typedef struct vexnode
{
	int Know;
	int Path;
	int Dist;
	ArcBox *first;
}VexNode;

typedef struct algraph
{
	VexNode list[VEXNUM];
	int vexnum, arcnum;
}ALGraph;

void CreateGraph(ALGraph &G);
void Dijkstra(int start, ALGraph &G);
int FindMinUnknown(ALGraph G);
void PrintPath(int v, ALGraph G, int count);

int main()
{
	ALGraph G;
	CreateGraph(G);
	int start, end;
	scanf("%d,%d", &start, &end);
	Dijkstra(start - 1, G);

	static int count = 0;
	PrintPath(end - 1, G, count);
}

void CreateGraph(ALGraph &G)
{
	G.vexnum = VEXNUM;
	int i;
	for (i = 0; i < VEXNUM; i++)
		G.list[i].first = NULL;
	ArcBox *current;
	int buf[36] = { 0,1,2,0,3,1,1,3,3,1,4,10,2,0,4,2,5,5,3,2,2,3,5,8,3,6,4,3,4,2,4,6,6,6,5,1 }; //三个一组，起始点，中止点，权重
	for (i = 0; i < 36; i += 3)
	{
		current = (ArcBox *)malloc(sizeof(ArcBox));
		current->adjvex = buf[i + 1];
		current->info = buf[i + 2];
		current->next = G.list[buf[i]].first;
		G.list[buf[i]].first = current;
	}
}

void Dijkstra(int start, ALGraph &G)
{
	int i;
	for (i = 0; i < VEXNUM; i++)
	{
		G.list[i].Know = 0;
		G.list[i].Dist = Infinite;
		G.list[i].Path = -1;
	}

	G.list[start].Dist = 0;

	int v, w;
	while (1)
	{
		v = FindMinUnknown(G);
		if (v == -1)
			break;

		G.list[v].Know = 1;
		ArcBox *current;
		for (current = G.list[v].first; current != NULL; current = current->next)
		{
			w = current->adjvex;
			if (!G.list[w].Know)
				if (G.list[v].Dist + current->info < G.list[w].Dist)
				{
					G.list[w].Dist = G.list[v].Dist + current->info;
					G.list[w].Path = v;
				}
		}
	}
}

int FindMinUnknown(ALGraph G)
{
	int min = Infinite, v = -1, i;
	for (i = 0; i < VEXNUM; i++)
	{
		if (G.list[i].Dist < min && !G.list[i].Know)
		{
			v = i;
			min = G.list[i].Dist;
		}
	}

	return v;
}

void PrintPath(int v, ALGraph G, int count)
{
	if (G.list[v].Path != -1)
	{
		count++;
		PrintPath(G.list[v].Path, G, count);
	}
	if (count == 0)
		printf("-1");
	else
		printf("%d,", v + 1);
}