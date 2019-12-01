/*µØ¾«ÅÅÐò*/

#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n = 0, i, temp;
	int *ptr;
	scanf("%d", &n);
	ptr = malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		scanf("%d", &ptr[i]);

	i = 0;
	while (i < n)
	{
		if (i == 0 || ptr[i - 1] <= ptr[i])
			i++;
		else
		{
			temp = ptr[i - 1];
			ptr[i - 1] = ptr[i];
			ptr[i] = temp;
			i--;
		}
	}

	for (i = 0; i < n; i++)
		printf("%d ", ptr[i]);
	printf("\n");

	free(ptr);

	return 0;
}