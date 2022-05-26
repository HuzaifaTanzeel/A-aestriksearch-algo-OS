#include "Node.h"
#include "Grid.h"
#include "arrayList.h"
#include "algorithm.h"
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void paint(ArrayList *path, Grid_Container g, bool only);
int findn( int num);

int main(int argc, char* argv[]) {
    int seed = time(NULL);

	long x_dimension = 10;
	long y_dimension = 15;

	Grid_Container g;
	g.grid = makeGrid(x_dimension, y_dimension, seed);
	g.x_dimension = x_dimension;
	g.y_dimension = y_dimension;


	struct timespec begin, end; 
	clock_gettime(CLOCK_REALTIME, &begin);

	ArrayList *path = aStar( &g, g.grid[0][0], g.grid[x_dimension -1][y_dimension -1]);

	clock_gettime(CLOCK_REALTIME, &end);
	long seconds = end.tv_sec - begin.tv_sec;
	long nanoseconds = end.tv_nsec - begin.tv_nsec;
	double elapsed = seconds + nanoseconds*1e-9;

	printf("Maze: \n\n");
	paint(path, g, false);
	if (path != NULL)
	{
		printf("\nShortest Path from start to end: \n\n");
		paint(path, g, true);
		printf("\nTracing Path: \n\n");
		printArrayList(path);
		printf("\nTime taken %.9fs: \n\n", elapsed);
	}
	else 
	{
		printf("\tNo path. Cannot reach goal.\n");
	}
	
	free_ArrayList(path);
	
	return 1;
	
	
} 



void paint(ArrayList* path, Grid_Container g, bool only) 
{
	int i = 0;
	int j = 0;
	
	for (i = 0; i < g.x_dimension; i++) 
	{
		for (j = 0; j < g.y_dimension; j++)
		{
			Point p = g.grid[i][j];

            if(contains(path, p) && only){
                printf("\033[36;1m S\033[0m ");
            }
			else if (p.start == true)
			{
				printf("\033[36;1m S\033[0m ");
			}
			else if (isWall(p)) 
			{
				printf("\e[31m W\033[0m ");
			}
			else if (isGoal(p))
			{
				printf("\033[36;1m G\033[0m ");
			}else {
                printf("\e[32m P\033[0m ");
            }

		}

		printf("\n");
	}
}
