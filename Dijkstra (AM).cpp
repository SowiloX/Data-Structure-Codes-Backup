#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int vex[8][8] = { 0 };
int know[8];
int path[8];
int dist[8];

void dijkstra(int start);
int find();
void print(int end);

int main()
{
	int buf[36] = { 1,2,2,1,4,1,2,4,3,2,5,10,3,1,4,3,6,5,4,3,2,4,6,8,4,7,4,4,5,2,5,7,6,7,6,1 };
	for (int i = 0; i < 36; i += 3)
	{
		vex[buf[i]][buf[i + 1]] = buf[i + 2];
	}
	int a, b, c;
	scanf("%d,%d,%d", &a, &b, &c);
	vex[a][b] = c;
	dijkstra(1);
	print(6);
}

void dijkstra(int start)
{
	for (int i = 1; i <= 8; i++)
	{
		know[i] = 0;
		path[i] = -1;
		dist[i] = 32767;
	}
	dist[start] = 0;
	int v, w;
	while (1)
	{
		v = find();
		if (v == -1)
			break;
		know[v] = 1;
		for (int i = 1; i <= 8; i++)
		{
			if (vex[v][i] != 0)
			{
				w = i;
				if (vex[v][w] + dist[v] < dist[w] && know[w] == 0)
				{
					dist[w] = vex[v][w] + dist[v];
					path[w] = v;
				}
			}
		}
	}
}

int find()
{
	int min = 32767, v = -1;
	for (int i = 1; i <= 8; i++)
	{
		if (know[i] == 0 && dist[i] < min)
		{
			min = dist[i];
			v = i;
		}
	}
	return v;
}

void print(int end)
{
	if (path[end] != -1)
	{
		print(path[end]);
		printf(",");
	}
	printf("%d", end);
}