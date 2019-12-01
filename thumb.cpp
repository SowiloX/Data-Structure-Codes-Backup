#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5
#define VertexType int

typedef struct arcbox
{
	int tailvex, headvex;
	struct arcbox *hlink, *tlink;
	int info;
}ArcBox;

typedef struct vexnode
{
	VertexType data;
	ArcBox *firstin, *firstout;
}VexNode;

typedef struct olgraph
{
	VexNode xlist[MAX];
	int vexnum, arcnum;
}OLGraph;

void CreatDG(OLGraph &G);
void thumbup(ArcBox *p);
void sort(int *A, int n);
ArcBox *BubbleSort(ArcBox *head);

int main()
{
	OLGraph G;
	CreatDG(G); //0,1,0,2,0,3,1,4,2,1,2,3,3,2,4,0,4,1,4,3,     4,3,4,1,4,0,2,3,2,1,1,4,0,3,0,2,0,1,

	int n, i, buf[10];
	for (i = 0; i < 10; i++)
		buf[i] = -1;
	scanf("%d", &n);
	ArcBox *current;
	current = G.xlist[n].firstin;
	i = 0;
	while (current != NULL)
	{
		if (current->info == 1)
			buf[i++] = current->tailvex;
		current = current->hlink;
	}

	if (buf[0] == -1)
		printf("-1");
	else
	{
		sort(buf, i);
		for (i = 0; buf[i] != -1; i++)
			printf("%d,", buf[i]);
	}
}

void CreatDG(OLGraph &G)
{
	//scanf("%d%d", &G.arcnum, &G.vexnum);
	G.vexnum = 5;
	char str[50] = { '\0' }, buf[50] = { '\0' };
	fgets(str, 50, stdin);
	int i, j = 0;
	for (i = 0; str[i] != '\0' && str[i] != '\n'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			buf[j] = str[i];
			j++;
		}
	}

	for (i = 0; i < G.vexnum; i++)
	{
		G.xlist[i].data = 0;
		G.xlist[i].firstin = NULL;
		G.xlist[i].firstout = NULL;
	}
	int k;
	for (k = 0; k < strlen(buf); k += 2)
	{
		i = buf[k] - 48;
		j = buf[k + 1] - 48;
		ArcBox *p;
		p = (ArcBox*)malloc(sizeof(ArcBox));
		if (p == NULL)
		{
			printf("Out of Space!");
			exit(-1);
		}
		p->tailvex = i;
		p->headvex = j;
		p->hlink = G.xlist[j].firstin;
		p->tlink = G.xlist[i].firstout;

		G.xlist[j].firstin = G.xlist[i].firstout = p;
	}

	for (i = 0; i < G.vexnum; i++)
		G.xlist[i].firstout = BubbleSort(G.xlist[i].firstout);
	for (i = 0; i < G.vexnum; i++)
		thumbup(G.xlist[i].firstout);
}

void thumbup(ArcBox *p)
{
	ArcBox *current;
	current = p;
	int count = 1;
	while (current != NULL)
	{
		if (count % 2 == 0)
			current->info = 0;
		else
			current->info = 1;
		count++;
		current = current->tlink;
	}

}

void sort(int *A, int n)
{
	int i, j, temp;
	for (i = 1; i < n; i++)
		for (j = 0; j < n - i; j++)
		{
			if (A[j] > A[j + 1])
			{
				temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
			}
		}
}

ArcBox *BubbleSort(ArcBox *head)
{
	ArcBox *current, *tail, *temp, *prev;

	tail = NULL;
	prev = NULL;
	current = head;
	while (current != tail)                     //tail is the last structure in the list. If current=tail, bubble sort is completed.
	{
		while (current->tlink != tail)
		{
			if (current->headvex > current->tlink->headvex)
			{
				if (current == head)
				{
					temp = head->tlink;
					head->tlink = head->tlink->tlink;     //Regard head->next as a new node.

					temp->tlink = head;                 //Insert the new node before head node.
					head = temp;
					current = head;
				}
				else
				{
					temp = current;
					prev->tlink = current->tlink;        //Regard current as a new node.

					current = prev->tlink;              //Insert the new node.
					temp->tlink = current->tlink;
					current->tlink = temp;
				}
			}
			prev = current;
			current = current->tlink;   //Move current to next structure.
		}
		tail = current;      //Make tail move forward.
		current = head;      //Start the loop again from first structure.
	}
	return head;
}