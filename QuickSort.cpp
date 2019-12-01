#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define Cutoff 3
#define Swap(a, b) ((a) = (a) + (b), (b) = (a) - (b), (a) = (a) - (b))

void QuickSort(int *A, int N);
void Qsort(int *A, int Left, int Right, int N);
int Median(int *A, int Left, int Right);
void InsertionSort(int *A, int Num, int N);

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

	QuickSort(A, N);
}

void QuickSort(int *A, int N)
{
	Qsort(A, 0, N - 1, N);
}

void Qsort(int *A, int Left, int Right, int N)
{
	int i, j, Pivot;
	if (Left + Cutoff <= Right)
	{
		Pivot = Median(A, Left, Right);
		i = Left;
		j = Right - 1;
		while (1)
		{
			while (A[++i] < Pivot) {}
			while (A[--j] > Pivot) {}
			if (i < j)
				Swap(A[i], A[j]);
			else
				break;
		}
		Swap(A[i], A[Right - 1]);
		for (int k = 0; k < N; k++)
			printf("%d,", A[k]);
		printf("\n");

		Qsort(A, Left, i - 1, N);
		Qsort(A, i + 1, Right, N);
	}
	else
	{
		InsertionSort(A + Left, Right - Left + 1, N);
		for (int k = 0; k < N; k++)
			printf("%d ", A[k]);
		printf("\n");
	}
}

int Median(int *A, int Left, int Right)
{
	int Center = (Left + Right) / 2;
	if (A[Left] > A[Center])
		Swap(A[Left], A[Center]);
	if (A[Left] > A[Right])
		Swap(A[Left], A[Right]);
	if (A[Center] > A[Right])
		Swap(A[Center], A[Right]);

	Swap(A[Center], A[Right - 1]);
	return A[Right - 1];
}

void InsertionSort(int *A, int Num, int N)
{
	int j, P, tmp;
	for (P = 1; P < Num; P++)
	{
		tmp = A[P];
		for (j = P; j > 0 && A[j - 1] > tmp; j--)
			A[j] = A[j - 1];
		A[j] = tmp;
	}
}