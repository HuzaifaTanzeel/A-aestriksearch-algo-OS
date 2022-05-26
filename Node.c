#include<stdio.h>
#include "Node.h"


int setPoint(Point *p, int x_value, int y_value, bool wall_value, bool goal_value){

    p->x = x_value;
    p->y = y_value;
    p->height = -1;		
	p->wall = wall_value;		
	p->goal = goal_value;	
	p->start = false;	
	p->parent_x = -1;
	p->parent_y = -1;

    return 1;
}

bool isWall(Point p) 
{
	return p.wall;
}

bool isGoal(Point p)
{
	return p.goal;
}

int setAsGoal(Point *p)
{
	if (isWall(*p)) {
		p->wall = false;	
	}
	p->goal = true;
	return 1;
}


bool equals(Point p1, Point p2) 
{
	if (p1.x == p2.x && p1.y == p2.y)
	{
		return true;
	} 
	else
	{
		return false;
	}
}

bool diagonal(Point p1, Point p2)
{
	if (equals(p1, p2))
	{
		return false;
	} 
	else if (p1.x == p2.x)
	{
		return false;
	}
	else if (p1.y == p2.y)
	{
		return false;
	}
	return true;
}

/* 
*      if p1.value > p2.value : return 1;
*      if p1.value < p2.value : return -1;
*      if p1.value = p2.value : return 0; 
*/

int compare(Point p1, Point p2)
{
        if (p1.f_score > p2.f_score)
        {
                return 1;
        }
        else if (p1.f_score < p2.f_score)
        {
                return -1;
        }
        else
        {
                return 0;
        }
}

int swap(Point *p1, Point *p2)
{

        Point temp = *p2;
        *p2 = *p1;
        *p1 = temp;
        return 1;
}

void printPoint(Point p)
{
	printf("Point[%d][%d]: f_score = %d | isWall = %d | isGoal = %d | parent[%d][%d]\n", p.x, p.y, p.f_score, isWall(p), isGoal(p), p.parent_x, p.parent_y);
}
