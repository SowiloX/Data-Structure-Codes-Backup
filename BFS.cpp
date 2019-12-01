#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

#define MAX 10

typedef struct graph
{
	int arcs[MAX][MAX];
	int vexnum, arcnm;
}Graph;

void BFSTraverse(Graph G);
int FirstAdjVex(Graph G, int v);
int NextAdjVex(Graph G, int v, int w);

int visited[8] = { 0 };

int main()
{
	Graph G;
	G.vexnum = MAX;
	G.arcs[0][1] = G.arcs[0][2] = 1;
	G.arcs[1][3] = G.arcs[1][4] = G.arcs[1][0] = 1;
	G.arcs[2][0] = G.arcs[2][5] = G.arcs[2][6] = 1;
	G.arcs[3][1] = G.arcs[3][7] = 1;
	G.arcs[4][1] = G.arcs[4][7] = 1;
	G.arcs[5][2] = G.arcs[5][7] = 1;
	G.arcs[6][2] = G.arcs[6][7] = 1;
	G.arcs[7][3] = G.arcs[7][4] = G.arcs[7][5] = G.arcs[7][6] = 1;

	BFSTraverse(G);
}

void BFSTraverse(Graph G)
{
	int v, w, u;
	queue<int> q;
	for (v = 0; v < G.vexnum; v++)
	{
		if (!visited[v])
		{
			visited[v] = 1;
			printf("%d,", v + 1);
			q.push(v);
			while (!q.empty())
			{
				u = q.front();
				q.pop();
				for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
				{
					if (!visited[w])
					{
						visited[w] = 1;
						printf("%d,", w + 1);
						q.push(w);
					}
				}
			}
		}
	}
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