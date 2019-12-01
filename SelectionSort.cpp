#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define Swap(a, b) ((a) = (a) + (b), (b) = (a) - (b), (a) = (a) - (b))

void SelectionSort(int *A, int N);

int main()
{
	int A[MAX] = { 0 }, N = 0, i, j = 0;
	scanf("%d\n", &N);
	for (i = 0; i < N; i++)
		scanf("%d,", &A[i]);
	/*char foo[MAX] = { '\0' }, bar[10] = { '\0' };
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
		A[N++] = atoi(bar);*/

	SelectionSort(A, N);
}

void SelectionSort(int *A, int N)
{
	int i, j, k; //k为最小值下标
	for (i = 0; i < N; i++)
	{
		for (k = i, j = i + 1; j < N; j++)
			if (A[j] < A[k]) k = j;

		if (k != i) Swap(A[i], A[k]);

		for (k = 0; k < N; k++)
			printf("%d ", A[k]);
		printf("\n");
	}
}