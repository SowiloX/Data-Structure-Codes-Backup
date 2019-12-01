#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

using namespace std;

#define MAX 11

typedef struct graph
{
	int arcs[MAX][MAX];
	int vexnum, arcnm;
}Graph;

int Indegree[MAX] = { 0 };

void Topsort(Graph G);
int FirstAdjVex(Graph G, int v);
int NextAdjVex(Graph G, int v, int w);
void Print(int v);

int main()
{
	Graph G = { { 0 }, 0, 0 };
	G.vexnum = MAX;
	int buf[42] = { 0,1,0,4,0,7,1,2,1,5,2,3,3,10,4,1,4,5,5,6,5,3,5,9,6,3,6,10,7,4,7,5,7,8,8,5,8,9,9,6,9,10 }; //0,1,0,4,0,7,1,2,1,5,2,3,3,10,4,1,4,5,5,6,5,3,5,9,6,3,6,10,7,4,7,5,7,8,8,5,8,9,9,6,9,10
	int i;
	for (i = 0; i < 42; i += 2)
	{
		G.arcs[buf[i]][buf[i + 1]] = 1;
		Indegree[buf[i + 1]]++;
	}

	char foo, bar;
	scanf("%c,%c", &foo, &bar);
	if (foo == 'S')
		i = 0;
	else if (foo == 'T')
		i = 10;
	else
		i = foo - 64;

	int j;
	if (bar == 'S')
		j = 0;
	else if (bar == 'T')
		j = 10;
	else
		j = bar - 64;

	if (G.arcs[i][j] != 0)
	{
		G.arcs[i][j] = 0;
		Indegree[j]--;
	}

	Topsort(G);
}

void Topsort(Graph G)
{
	queue<int> Q;
	int counter = 0;
	int v, w;

	for (v = 0; v < MAX; v++)
	{
		if (Indegree[v] == 0)
			Q.push(v);
	}

	while (!Q.empty())
	{
		v = Q.front();
		Q.pop();
		Print(v);
		counter++;

		int w;
		for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
		{
			if (--Indegree[w] == 0)
				Q.push(w);
		}
	}
	if (counter != MAX)
		printf("ERROR");
}

int FirstAdjVex(Graph G, int v)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
	{
		if (G.arcs[v][i] == 1)
			return i;
	}
	return -1;
}

int NextAdjVex(Graph G, int v, int w)
{
	int i;
	for (i = w + 1; i < G.vexnum; i++)
	{
		if (G.arcs[v][i] == 1)
			return i;
	}
	return -1;
}

void Print(int v)
{
	if (v == 0)
		printf("S,");
	else if (v == 10)
		printf("T,");
	else
		printf("%c,", v + 64);
}