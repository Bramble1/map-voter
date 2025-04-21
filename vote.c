#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>

#define MAP_LIMIT 3

typedef struct
{
	char Map[100];
	int votes;
}MAP;

typedef struct
{
	MAP *maps;
	int front;
	int rear;
}QUEUE; 

void vote(MAP *maps,int *max,int *min)
{
	srand(time(NULL));
	int users = 10;
	do{
		maps[rand() % (*max+1-*min)+*min].votes += 1;
	}while(--users!=0);
	
}

void sort_votes(QUEUE *map_selection)
{
	//insertion sort,because map array will always be small,thus minimize the overhead
	//for sorting such as merge sort, which is overkill for a small array
	//O(n^2) and space O(1)
	int j;
	MAP key;	
	for(int i=1;i<=map_selection->rear;i++)
	{
		key = map_selection->maps[i];
		j = i-1;

		while(j>=0 && map_selection->maps[j].votes >key.votes)
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
	{
		printf("[%d]Map votes = %d\n",i,map_selection->maps[i].votes);
	}
}

void dequeue(int *front,int *rear)
{
	if(*front<=*rear){
		*front = *front + 1;
	}
}

int main()
{
	//assume we already have a list of maps read from file
	//and assume it's a random selection to choose from
	QUEUE map_selection;
	map_selection.maps = malloc(sizeof(MAP)*MAP_LIMIT);
	map_selection.front = 0;
	map_selection.rear = MAP_LIMIT;
	int once = 0;
	int loop_number = 0;
	do{
		for(int i=map_selection.front;i<=map_selection.rear;i++)
			map_selection.maps[i].votes = 0;

		//int map_number = map_selection.rear - map_selection.front;
		int map_number = map_selection.rear;
		vote(map_selection.maps,&map_number,&map_selection.front);
		print_votes(&map_selection);

		printf("sorted:\n\n");
		sort_votes(&map_selection);
		
	//	if(once++ == 0){ map_selection.maps[1].votes = map_selection.maps[2].votes = map_selection.maps[3].votes;} 
		sort_votes(&map_selection);	
		print_votes(&map_selection);
		printf("\n");
		
		while(map_selection.maps[map_selection.front].votes < map_selection.maps[map_selection.rear].votes)
		{
			dequeue(&map_selection.front,&map_selection.rear);
		}
	}while(map_selection.front!=map_selection.rear);

	printf("\nNext map with votes:%d\n",map_selection.maps[map_selection.front].votes);

	free(map_selection.maps);
	return 0;
}
