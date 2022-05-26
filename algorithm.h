#ifndef ALGO_H
#define ALGO_H

#include "Node.h"
#include "P_Queue.h"
#include "Grid.h"
#include "arrayList.h"
#include <stdlib.h>
#include <stdio.h>


int heuristic_estimate(Point start, Point goal);
int calculate_g_score(Point current, Point neighbor);
ArrayList* aStar(Grid_Container *grid, Point start, Point goal);
ArrayList* getNeighborPoints(Point p, Grid_Container *g);
ArrayList* reconstruct_Path(ArrayList *map, Point goal);

#endif
