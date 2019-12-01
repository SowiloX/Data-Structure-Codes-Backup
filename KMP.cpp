#include <stdio.h>

#define SIZE 256 //字符串最大长度255，多一个存长度

int Index_KMP(char *S, char *T, int pos);
void Get_next(char *T, int *next);
int Improved_Index_KMP(char *S, char *T, int pos);
void Get_nextval(char *T, int *nextval);
void Get_String(char *str);

int main()
{
	char S[SIZE] = { '\0' }, T[SIZE] = { '\0' };
	int pos = 1;
	Get_String(S);
	Get_String(T);
	printf("%d\n", Index_KMP(S, T, pos));
	printf("%d\n", Improved_Index_KMP(S, T, pos));

}

int Index_KMP(char *S, char *T, int pos)
{
	int i = pos, j = 1;
	int next[SIZE] = { 0 };
	Get_next(T, next);
	while (i <= S[0] && j <= T[0])
	{
		if (j == 0 || S[i] == T[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];
	}
	if (j > T[0])
		return i - T[0];
	else
		return 0;
}

void Get_next(char *T, int *next)
{
	int j = 1, k = 0;
	next[1] = 0;
	while (j < T[0])
	{
		if (k == 0 || T[j] == T[k])
		{
			++j;
			++k;
			next[j] = k;
		}
		else
			k = next[k];
	}
}


int Improved_Index_KMP(char *S, char *T, int pos)
{
	int i = pos, j = 1;
	int nextval[SIZE] = { 0 };
	Get_nextval(T, nextval);
	while (i <= S[0] && j <= T[0])
	{
		if (j == 0 || S[i] == T[j])
		{
			++i;
			++j;
		}
		else
			j = nextval[j];
	}
	if (j > T[0])
		return i - T[0];
	else
		return 0;
}

void Get_nextval(char *T, int *nextval)
{
	int j = 1, k = 0;
	nextval[1] = 0;
	while (j < T[0])
	{
		if (k == 0 || T[j] == T[k])
		{
			++j;
			++k;
			if (T[j] != T[k])
				nextval[j] = k;
			else
				nextval[j] = nextval[k];
		}
		else
			k = nextval[k];
	}
}

void Get_String(char *str)
{
	fgets(str, SIZE, stdin);
	int i, length;
	for (i = 0; i < SIZE; i++)
	{
		if (str[i] == '\n' || str[i] == '\0')
		{
			str[i] = '\0';
			break;
		}
	}
	length = i;
	while (i >= 0)
	{
		str[i + 1] = str[i];
		i--;
	}
	str[0] = length;
}