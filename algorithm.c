#include "Node.h"

#include "P_Queue.h"

#include "Grid.h"

#include "arrayList.h"

#include "algorithm.h"

#include <stdlib.h>

#include <stdio.h>

#include <omp.h>







ArrayList* aStar(Grid_Container *grid, Point start, Point goal){



    PQ *open = makePQ();

    ArrayList *closed = makeArrayList();

    ArrayList *map = makeArrayList();



    start.g_score = 0; 

    start.f_score = start.g_score + heuristic_estimate(start, goal);



    insert(open, start);



    while(!isEmpty(open)){



        Point p = pop(open);



        if(isGoal(p)){

            free_PQ(open);

            free_ArrayList(closed);



            ArrayList *rtn = NULL;

            rtn = makeArrayList();



            rtn = reconstruct_Path(map, p);



            free_ArrayList(map);



            return rtn;

        }



        add(closed, p);



        ArrayList *neighbours = NULL;

        neighbours = makeArrayList();

        neighbours = getNeighborPoints(p, grid);
	int temp_gscore[8];



        /*#pragma omp parallel for
		for(int j=0 ; j<getSize(neighbours) ; j++){
			Point n = get(neighbours, j);
			temp_gscore[j] = calculate_g_score(p, n);
		}*/

	Point neighbour;
	bool contain_open;
	bool contain_closed;

        int i=0;
	#pragma omp parallel for private(neighbour, contain_open, contain_closed) shared(open, closed)
        for(i=0 ; i<getSize(neighbours) ; i++){
            neighbour = get(neighbours, i);

	    temp_gscore[i] = calculate_g_score(p, neighbour);

	    #pragma omp critical
			{
				contain_open = containsPoint(open, neighbour);
				contain_closed = contains(closed, neighbour);
			}

            if(!contain_open){

                if(!contain_closed || temp_gscore[i] < neighbour.g_score){

                    neighbour.parent_x = p.x;
                    neighbour.parent_y = p.y;
                    neighbour.g_score = temp_gscore[i];
                    add(map, p);

                    if(!isGoal(neighbour)){
                        neighbour.f_score = neighbour.g_score + heuristic_estimate(p, neighbour);
                    }

                    else{
                        neighbour.f_score = 0;
                    }

                    if(!containsPoint(open, neighbour)){
			#pragma omp critical
                        {
				insert(open, neighbour);
			}
                    }

                }

            }
        }



        free_ArrayList(neighbours);

    }



    return NULL;

}







int heuristic_estimate(Point currentPosition, Point goal)

{

	int xDistance = abs(currentPosition.x - goal.x);

	int yDistance = abs(currentPosition.y - goal.y);

	

	if (xDistance > yDistance)

	{

		return 14 * yDistance + 10*(xDistance - yDistance);

	}

	else 

	{

		return 14 * xDistance + 10*(yDistance - xDistance);

	}

	

}







int calculate_g_score(Point current, Point target)

{

	if (equals(current, target))

	{

		return 0;

	}

	else if (diagonal(current, target))

	{

		return 14 + current.g_score;

	}

	else 

	{

		return 10 + current.g_score;

	}

}







ArrayList* getNeighborPoints(Point p, Grid_Container *g)

{

	int i = 0;

	int x_Values[8]; 

	int y_Values[8];

	

	x_Values[0] = p.x - 1;

	y_Values[0] = p.y - 1;

	

	x_Values[1] = p.x - 1;

	y_Values[1] = p.y;

	

	x_Values[2] = p.x - 1;

	y_Values[2] = p.y + 1;

	

	x_Values[3] = p.x;

	y_Values[3] = p.y - 1;

	

	x_Values[4] = p.x;

	y_Values[4] = p.y + 1;



	x_Values[5] = p.x + 1;

	y_Values[5] = p.y - 1;

	

	x_Values[6] = p.x + 1;

	y_Values[6] = p.y;

		

	x_Values[7] = p.x + 1;

	y_Values[7] = p.y + 1;



	ArrayList *temp = NULL;

	temp = makeArrayList();

	

	for ( i = 0; i < 8; i++)

	{

		Point *neighbor = NULL;

		neighbor =  get_Grid_Point(g, x_Values[i], y_Values[i]);

		//printf("Neighbor Point: x = %d y = %d\n", neighbor->x, neighbor->y);

		if (neighbor != NULL && !isWall(*neighbor))

		{

			add(temp, *neighbor);

		}

		free(neighbor);

	}

	return temp;

		

}







ArrayList* reconstruct_Path(ArrayList *map, Point goal)

{

	int x = 0;

	int y = 0;

	ArrayList* path = NULL;

	Point *p 	= NULL;

	

	path 	= makeArrayList(); 

	

	add( path, goal);

	p = get_By_Points( map, goal.parent_x, goal.parent_y);

	

	while ( p != NULL )

	{

		add( path, *p);

		x = p->parent_x;

		y = p->parent_y;

		

		free(p);



		p = get_By_Points( map, x, y);

	}

	

	free(p);

	return path;

}
