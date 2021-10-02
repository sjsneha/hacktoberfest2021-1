#include <stdio.h>
#include <stdlib.h>
int processes[100][3], NP, quantum, scheduler[1000], WT[100];
unsigned int time = 0;
typedef struct el
{
	unsigned int p;
	struct el *next;
} Q;
Q *qeue = NULL;
void getSystem()
{
	int i;
	printf("\nEnter the number of process: \n");
	scanf("%d", &NP);
	printf("Enter the arrival time:\n");

	for (i = 0; i < NP; i++)
	{
		scanf("%d", &processes[i][0]);
	}
	printf("Enter the burst time:\n");

	for (i = 0; i < NP; i++)
	{
		scanf("%d", &processes[i][1]);
		processes[i][2] = processes[i][1];
	}

	printf("\nEnter the Quantum time: ");
	scanf("%d", &quantum);
}

unsigned int executionRemained()
{
	int i;
	unsigned int x = 0;
	for (i = 0; i < NP; i++)
	{
		if (processes[i][2] > 0)
		{
			x = 1;
		}
	}
	return x;
}
void addToQeue(int i)
{
	Q *n, *n1;
	n = (Q *)malloc(sizeof(Q));
	n->next = NULL;
	n->p = i;
	if (qeue == NULL)
	{

		qeue = n;
	}
	else
	{
		for (n1 = qeue; n1->next != NULL; n1 = n1->next)
			;
		n1->next = n;
	}
}
void addArrivedProcessesToQeue()
{
	int i;
	for (i = 0; i < NP; i++)
	{
		if (processes[i][0] == time)
		{
			addToQeue(i);
		}
	}
}
unsigned int getNextProcess()
{
	Q *n;
	int x;
	if (qeue == NULL)
	{
		return -1;
	}
	else
	{
		x = qeue->p;
		n = qeue;
		qeue = qeue->next;
		free(n);
		return x;
	}
}
void schedule()
{
	unsigned int np, toRun, q, i;
	q = 0;
	addArrivedProcessesToQeue();
	while (executionRemained())
	{
		np = getNextProcess();
		if (np == -1)
		{

			scheduler[time] = -1;
			time++;
			addArrivedProcessesToQeue();
		}
		else
		{
			q = quantum;
			if (processes[np][2] < q)
			{
				q = processes[np][2];
			}
			for (i = q; i > 0; i--)
			{
				scheduler[time] = np;
				time++;
				processes[np][2]--;
				addArrivedProcessesToQeue();
			}
			if (processes[np][2] > 0)
			{
				addToQeue(np);
			}
		}

		int x;
	}
}
void printScheduling()
{
	int i;
	for (i = 0; i < NP; i++)
	{
		printf("Waiting  time of process%d is %d\n", i + 1, WT[i]);
	}
	//counting Average Waiting Time...
	float AWT = 0.0;
	for (i = 0; i < NP; i++)
	{
		AWT = AWT + WT[i];
	}
	AWT = AWT / NP;
	printf("\nAverage Waiting Time: %f\n", AWT);
	int TAT[100];
	for (i = 0; i < NP; i++)
	{
		TAT[i] = WT[i] + processes[i][1];
	}
	float ATAT = 0.0;
	for (i = 0; i < NP; i++)
	{
		ATAT = ATAT + TAT[i];
	}
	ATAT /= NP;
	for (i = 0; i < NP; i++)
	{
		printf("Turn around time of process%d is %d\n", i + 1, TAT[i]);
	}
	printf("\nAverage Turn around time is :%f\n", ATAT);
}
void WatingTime()
{
	int i;
	unsigned int releaseTime, t;
	for (i = 0; i < NP; i++)
	{

		for (t = time - 1; scheduler[t] != i; t--)
			;
		releaseTime = t + 1;
		WT[i] = releaseTime - processes[i][0] - processes[i][1];
	}
}

int main()
{
	getSystem();
	schedule();
	WatingTime();
	printScheduling();
}
