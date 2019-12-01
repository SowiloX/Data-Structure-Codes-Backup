#include <stdio.h>
#include <stdlib.h>

int BinarySearch(int *A, int key, int L, int R);
int compare(const void *a, const void *b);

int main()
{
	int A[10] = { 56,34,23,456,54,73,55,23,89,1 };
	qsort(A, 10, sizeof(int), compare);
	printf("%d", BinarySearch(A, 2, 0, 9));
}

int BinarySearch(int *A, int key, int L, int R)
{
	int M = (L + R) / 2;

	if (L > R)
		return -1;
	else
	{
		if (A[M] > key)
			return BinarySearch(A, key, L, M - 1);
		else if (A[M] < key)
			return BinarySearch(A, key, M + 1, R);
		else if (A[M] == key)
			return M;
	}
}

int compare(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}