#include "Node.h"

#ifndef GRID_H
#define GRID_H

typedef struct {
        int x_dimension;
        int y_dimension;
        Point **grid;
        Point *goal;
} Grid_Container;

Point** makeGrid(int x_dim, int y_dim, int seed);
Point* get_Grid_Point(Grid_Container *grid, int x, int y);

#endif
