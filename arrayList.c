#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "Node.h"
#include "P_Queue.h"
#include "Grid.h"
#include "arrayList.h"


ArrayList* makeArrayList() 
{
	ArrayList* arr = NULL;
	
	arr = (ArrayList *) malloc(sizeof(ArrayList));
	
	arr->pointArray 	= NULL;
	arr->sizeOfArray 	= 10;
	arr->numberOfElements 	= 0;
	arr->memoryAllocated 	= sizeof(Point) * 10;

	arr->pointArray = (Point *) malloc(arr->memoryAllocated);
	
	return arr;
}



int add(ArrayList *arr, Point p)
{
	
	if (arr->numberOfElements  == arr->sizeOfArray)
	{
		Point *temp = NULL;
		int newMemory = 0;
	
		newMemory = sizeof(Point) * 10 + arr->memoryAllocated;
		temp = (Point *) realloc(arr->pointArray, newMemory);
		
		if (temp == NULL)
		{
			return 0;
		}
		else 
		{
			arr->pointArray = temp;
			arr->sizeOfArray += 10;
			arr->memoryAllocated = newMemory;
		}
	}

	arr->pointArray[arr->numberOfElements] = p;
	arr->numberOfElements += 1;
	return 1;
}



bool contains(ArrayList *arr, Point p)
{
	int i = 0;
	for (i = 0; i < getSize(arr) ; i++)
	{
		if (equals(get(arr, i), p))
		{
			return true;
		}
	}

	return false;
}



Point get(ArrayList *arr, int index)
{
	return arr->pointArray[index];
}


int getSize(ArrayList *arr)
{
	return arr->numberOfElements;
}


void free_ArrayList(ArrayList *arr)
{
	if (arr != NULL)
		free(arr->pointArray);
	free(arr);
}

/* void printArrayList(ArrayList *arr)
{
	int i = 0;
	for ( i = 0; i < getSize(arr); i++)
	{
		Point p = get(arr, i);
		printPoint(p);
	}
} */



Point* get_By_Points(ArrayList *arr, int x, int y)
{
	if ( x < 0 || y < 0)
	{
		return NULL;
	}

	Point p;
	Point *rtrnPoint = NULL;
	rtrnPoint = (Point *) malloc(sizeof(Point));
	setPoint( &p, x, y, 0, 0);
	int i = 0;
	
	for ( i = 0; i < getSize(arr); i++)
	{
		*rtrnPoint = get(arr, i);
		if ( equals( *rtrnPoint, p))
		{
			return rtrnPoint;
		}
	}
		
	return NULL;
}


void printArrayList(ArrayList *arr)
{
	int i = 0;
	for ( i = 0; i < getSize(arr); i++)
	{
		Point p = get(arr, i);
		printPoint(p);
	}
}
