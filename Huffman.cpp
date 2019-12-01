#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 500

typedef struct node
{
	int weight;
	int parent, Left, Right;
	char Element;
}*HuffmanTree;

void HuffmanCoding(HuffmanTree &T, int *W, int N); //哈夫曼树T，权重W，字符数N
void Decoding(char* Code, HuffmanTree T, int Root); //编码Code，哈夫曼树T，树根下标Root
void Select(HuffmanTree T, int MAX, int &S1, int &S2); //在树T中1至MAX中选出权重最小的两项，下标分为别S1,S2

int main()
{
	HuffmanTree T;
	char Code[200] = { '\0' };
	int W[SIZE] = { 7,19,2,6,32,3,21,10 };
	int N = 8;

	HuffmanCoding(T, W, N);
	fgets(Code, 100, stdin); //10111010100001000110011110110100

	free(T);
}

void HuffmanCoding(HuffmanTree &T, int *W, int N)
{
	if (N <= 1)
		return;
	int m = 2 * N - 1;
	T = (HuffmanTree)malloc((m + 1) * sizeof(struct node));
	if (T == NULL)
	{
		printf("OUT OF SPACE");
		exit(-1);
	}

	int i; HuffmanTree p;
	for (p = T, i = 1; i <= N; i++)
	{
		p[i].weight = W[i - 1]; //数组0号位置空置
		p[i].Left = p[i].Right = p[i].parent = 0;
		p[i].Element = i + 96;
	}
	while (i <= m)
	{
		p[i].Left = p[i].Right = p[i].parent = p[i].weight = 0;
		p[i].Element = 0;
		i++;
	}
	for (i = N + 1; i <= m; i++)
	{
		int S1, S2;
		Select(T, i - 1, S1, S2);
		T[S1].parent = i;
		T[S2].parent = i;
		T[i].Left = S1;
		T[i].Right = S2;
		T[i].weight = T[S1].weight + T[S2].weight;
	}


}

void Decoding(char* Code, HuffmanTree T, int Root)
{
	int i, j = Root;
	for (i = 0; Code[i] != '\0' && Code[i] != '\n'; i++)
	{
		if (Code[i] == '0')
			j = T[j].Left;
		else if (Code[i] == '1')
			j = T[j].Right;

		if (T[j].Element != 0)
		{
			printf("%c", T[j].Element);
			j = Root;
		}
	}

}

void Select(HuffmanTree T, int MAX, int &S1, int &S2)
{
	int i;
	int Min1 = 100, Min2 = 100;
	for (i = 1; i <= MAX; i++)
	{
		if (T[i].weight < Min1 && T[i].parent == 0)
		{
			Min1 = T[i].weight;
			S1 = i;
		}
	}
	for (i = 1; i <= MAX; i++)
	{
		if (T[i].weight < Min2 && T[i].weight != Min1 && T[i].parent == 0)
		{
			Min2 = T[i].weight;
			S2 = i;
		}
	}
}