/*归并排序，修改后*/

#include<stdio.h>
#define SIZE 100000
void MergeSort(int B[], int iBegin, int iEnd, int A[]);
void Merge(int A[], int iBegin, int iMiddle, int iEnd, int B[]);

int main()
{
	int A[SIZE];
	int B[SIZE];
	int N, i;
	scanf("%d", &N);
	for (i = 0; i < N; i++)
		scanf("%d,", &A[i]);

	MergeSort(A, 0, N - 1, B);

	for (i = 0; i < N; i++)
		printf("%d ", A[i]);
	printf("\n");

	return 0;
}


// Sort the given run of array A[] using array B[] as a source.
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void MergeSort(int A[], int iBegin, int iEnd, int B[])
{
	int iMiddle;
	if (iEnd > iBegin)                       // if run size == 1
	{                                            //   consider it sorted
		// split the run longer than 1 item into halves
		iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
		// recursively sort both runs from array A[] into B[]
		MergeSort(A, iBegin, iMiddle, B);  // sort the left  run
		MergeSort(A, iMiddle + 1, iEnd, B);  // sort the right run

		Merge(A, iBegin, iMiddle, iEnd, B);
	}
}

void Merge(int A[], int iBegin, int iMiddle, int iEnd, int B[])
{
	int i, j, k = 0; //分别为A左部分下标，A右部分下标，B下标
	i = iBegin;
	j = iMiddle + 1;

	while (i <= iMiddle && j <= iEnd)
	{
		if (A[i] <= A[j])
			B[k++] = A[i++];
		else
			B[k++] = A[j++];
	}

	while (i <= iMiddle)
		B[k++] = A[i++];

	while (j <= iEnd)
		B[k++] = A[j++];

	for (i = 0; i < k; i++)
		A[iBegin + i] = B[i];
}
