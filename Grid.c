#include "Grid.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

Point** makeGrid(int x_dim, int y_dim, int seed){
    srand(seed);
    int i=0;
    int j=0;
    Point** g = (Point**) malloc(x_dim * sizeof(Point*));

    for(i=0 ; i<y_dim ; i++){
        g[i] =  (Point*) malloc(y_dim * sizeof(Point)) ;
    }

    for(i=0 ; i<x_dim ; i++){

        for(j=0 ; j<y_dim ; j++){
            Point p;
            int num = rand() % 100;

            if(num < 20){
                setPoint(&p, i, j, 1, 0);
            }

            else{
                setPoint(&p, i, j, 0, 0);
            }

            setPoint(&g[i][j], p.x, p.y, p.wall, p.goal);
        }

    }

    setAsGoal(&g[x_dim-1][y_dim-1]);
    g[0][0].start = true;

    return g;
}



Point* get_Grid_Point(Grid_Container *grid, int x, int y){

    Point *p = (Point *) malloc(sizeof(Point));
	int x_d = grid->x_dimension;
	int y_d = grid->y_dimension;
	
 	if ((x < x_d && x >= 0) && (y < y_d && y >= 0))
	{
		*p = grid->grid[x][y];
		return p;
	}
	
	return NULL;

}