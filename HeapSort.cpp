#include <stdio.h>
#include <stdlib.h>

#define LeftChild(i) (2 * (i) + 1)
#define MAX 100

void PercDown(int *A, int i, int N);
void HeapSort(int *A, int N);

int main()
{
	int A[MAX] = { 0 }, N = 0, i, j = 0;
	char foo[MAX] = { '\0' }, bar[10] = { '\0' };
	fgets(foo, MAX, stdin);
	for (i = 0; foo[i] != '\0' && foo[i] != '\n'; i++)
	{
		if (foo[i] >= '0' && foo[i] <= '9')
			bar[j++] = foo[i];
		else
		{
			A[N++] = atoi(bar);
			for (j = 0; j < 10; j++)
				bar[j] = '\0';
			j = 0;
		}
	}
	if (bar[0] != '\0')
		A[N++] = atoi(bar);

	scanf("%d", &count);

	HeapSort(A, N);
	for (int k = 0; k < N; k++)
		printf("%d,", A[k]);
	printf("\n");
}

void PercDown(int *A, int i, int N)
{
	int Child;
	int tmp;

	for (tmp = A[i]; LeftChild(i) < N; i = Child)
	{
		Child = LeftChild(i);
		if (Child != N - 1 && A[Child + 1] > A[Child])
			Child++;
		if (tmp < A[Child])
			A[i] = A[Child];
		else
			break;
	}
	A[i] = tmp;
}

void HeapSort(int *A, int N)
{
	int i;
	for (i = N / 2; i >= 0; i--)
	{
		PercDown(A, i, N);
	}
	for (i = N - 1; i > 0; i--)
	{
		int tmp; tmp = A[0]; A[0] = A[i]; A[i] = tmp;
		PercDown(A, 0, i);
	}
}