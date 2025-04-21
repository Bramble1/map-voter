#include "votelib.h"
#include<malloc.h>

#define MAP_LIMIT 3
#define SIM_USERS 10

int main()
{
	//assume we already have a list of maps read from file
	//and assume it's a random selection to choose from
	QUEUE map_selection;
	map_selection.maps = malloc(sizeof(MAP)*MAP_LIMIT);
	map_selection.front = 0;
	map_selection.rear = MAP_LIMIT;
	do{
		//set to 0 votes
		for(int i=map_selection.front;i<=map_selection.rear;i++)
			map_selection.maps[i].votes = 0;

		//perform vote
		vote(map_selection.maps,&map_selection.rear,&map_selection.front);
		print_votes(&map_selection);

		//output sorted votes
		printf("\tSorted:\n");
		sort_votes(&map_selection);
		
		sort_votes(&map_selection);	
		print_votes(&map_selection);
		printf("\n");
		
		//if duplicates occur, maps have equal number of votes then
		//process of elimination and vote again		
		while(map_selection.maps[map_selection.front].votes < map_selection.maps[map_selection.rear].votes)
		{
			dequeue(&map_selection.front,&map_selection.rear);
		}
	}while(map_selection.front!=map_selection.rear);

	printf("\nNext map with votes:%d\n",map_selection.maps[map_selection.front].votes);

	free(map_selection.maps);
	return 0;
}
