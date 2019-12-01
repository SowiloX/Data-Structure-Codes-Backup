#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

void InsertionSort(int *A, int N);

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

	InsertionSort(A, N);
}

void InsertionSort(int *A, int N)
{
	int j, P, tmp;
	for (P = 1; P < N; P++)
	{
		tmp = A[P];
		for (j = P; j > 0 && A[j - 1] > tmp; j--)
			A[j] = A[j - 1];
		A[j] = tmp;
		/*for (int i = 0; i < N; i++)
			printf("%d ", A[i]);
		printf("\n");*/
	}
}