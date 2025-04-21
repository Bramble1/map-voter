#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAP_LIMIT 3

typedef struct
{
	int votes;
}MAP;

typedef struct
{
	MAP *maps;
	int front;
	int rear;
}QUEUE;

void vote(MAP *maps,int *max,int *min);
void sort_votes(QUEUE *map_selection);
void print_votes(QUEUE *map_selection);
void dequeue(int *front,int *rear);
