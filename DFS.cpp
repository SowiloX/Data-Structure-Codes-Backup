#include <stdlib.h>
#include <iostream>

using namespace std;

#define MAX 8

typedef struct graph
{
	int arcs[MAX][MAX];
	int vexnum, arcnm;
}Graph;

void DFS(Graph G, int v);

int visited[8] = { 0 };

int main()
{
	Graph G = { {0}, 0, 0 };
	G.vexnum = MAX;
	G.arcs[0][1] = G.arcs[0][2] = 1;
	G.arcs[1][3] = G.arcs[1][4] = G.arcs[1][0] = 1;
	G.arcs[2][0] = G.arcs[2][5] = G.arcs[2][6] = 1;
	G.arcs[3][1] = G.arcs[3][7] = 1;
	G.arcs[4][1] = G.arcs[4][7] = 1;
	G.arcs[5][2] = G.arcs[5][7] = 1;
	G.arcs[6][2] = G.arcs[6][7] = 1;
	G.arcs[7][3] = G.arcs[7][4] = G.arcs[7][5] = G.arcs[7][6] = 1;

	int start;
	cin >> start;
	DFS(G, start);
}

void DFS(Graph G, int v)
{
	visited[v] = 1;
	cout << v << " ";

	for (int w = 0; w < G.vexnum; w++)
	{
		if (!visited[w] && G.arcs[v][w])
			DFS(G, w);
	}
}