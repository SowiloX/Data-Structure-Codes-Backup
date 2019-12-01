#include<stdio.h>
#include<stdlib.h>
#define Swap(a, b) ((a) = (a) + (b), (b) = (a) - (b), (a) = (a) - (b))

int main()
{
	int n = 0, i, j, temp;
	int *ptr;
	scanf("%d", &n);
	ptr = (int *)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		scanf("%d,", &ptr[i]);

	for (i = 1; i < n; i++)
	{
		for (j = 0; j < n - i; j++)
		{
			if (ptr[j] > ptr[j + 1])
				Swap(ptr[j], ptr[j + 1]);
		}

		for (int k = 0; k < n; k++)
			printf("%d ", ptr[k]);
		printf("\n");
	}

	free(ptr);

	return 0;
}