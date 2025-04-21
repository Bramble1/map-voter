#include "votelib.h"

void vote(MAP *maps,int *max,int *min)
{
	srand(time(NULL));
	int users = 10;
	do
	{
		maps[rand()%(*max+1-*min)+*min].votes += 1;
	}while(--users!=0);
}

void sort_votes(QUEUE *map_selection)
{
	//insertion sort because array will always be small
	//and avoiding the overhead of merge sort which is overkill
	//O(n^2) and O(1) space.
	
	int j;
	MAP key;
	for(int i=1;i<=map_selection->rear;i++)
	{
		key = map_selection->maps[i];
		j = i-1;

		while(j>=0 && map_selection->maps[j].votes > key.votes)
		{
			map_selection->maps[j+1] = map_selection->maps[j];
			j--;
		}
		map_selection->maps[j+1] = key;
	}
}

void print_votes(QUEUE *map_selection)
{
	printf("\t__VOTES__\n");
	for(int i=map_selection->front;i<=map_selection->rear;i++)
		printf("[%d]Map votes = %d\n",i,map_selection->maps[i].votes);
}

void dequeue(int *front,int *rear)
{
	if(*front<=*rear)
		*front = *front + 1;
}

 
