#include "Node.h"
#include "P_Queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


PQ* makePQ()
{
	PQ *pq = NULL;
	pq = (PQ *) malloc(sizeof(PQ));
	pq->memorySize = sizeof(Point) * 10;
	pq->pointArray = (Point *) malloc(pq->memorySize);
	pq->size = 10;
	pq->numberOfElements = 0;
	
	return pq;	
}

int insert(PQ *pq, Point p) 
{
	// when array is full realloc
	if ( (getPQSize(pq) + 1) == pq->size )
	{
		Point *temp = NULL;
		int newMemory = 0;


		newMemory = sizeof(Point) * 10 + pq->memorySize;
		temp = (Point *) realloc( pq->pointArray, newMemory);

		if (temp == NULL)
		{
			return 0; // Failure to realloc
		}
		else 
		{
			pq->pointArray = temp; // realloc successful
			pq->size += 10; // update size of array
			pq->memorySize = newMemory; // update current allocated memory for PQ
		}
	}
	
	int i = 0;
	int max = getPQSize(pq) + 1; 
	pq->pointArray[max] = p; 
	
	for ( i = max; (compare(pq->pointArray[(i/2)], pq->pointArray[i]) == 1)
			 && (i/2 != 0); i = i/2) 
	{
		Point temp = pq->pointArray[(i/2)];
		pq->pointArray[(i/2)] = pq->pointArray[i];
		pq->pointArray[i] = temp;
	}
	
	pq->numberOfElements += 1;
	return 1;
}



int getPQSize(PQ *pq) 
{
	return pq->numberOfElements;
}



/* void printTree(PQ *pq) 
{
	printf("\nPQ array:\n");
	int i = 0;
	for (i = 0; i <= pq->numberOfElements; i++)
	{
		printf("Position[%d]: ", i);
		printPoint(pq->pointArray[i]);
	}
} */



Point pop(PQ *pq) 
{

	Point p;
	p = pq->pointArray[1];
	//p  = (Point *) malloc(sizeof(Point));

	if (getPQSize(pq) == 1)
	{
			
		pq->numberOfElements -= 1;
		return p;
	}
	
	pq->pointArray[1] = pq->pointArray[getPQSize(pq)];

	pq->numberOfElements -= 1;

	heapify(pq, 1);
	return p;
}




int heapify(PQ *pq, int index) 
{
	//printf("Entering Heapify Index: %d\n", index);
	Point* parent = getPoint(pq, index);
	
	if (parent == NULL)  
	{
		//printf("Parent is NULL\n");
		return 0;
	}	
	
	Point *leftChild = getPoint(pq, (index * 2));
	
	if (leftChild != NULL && compare(*parent, *leftChild) == 1)
	{
		//printf("Parent > leftChild\n");
		//printf("\tParent.height = %d\n", parent->height);
		//printf("\tleftChild.height = %d\n", leftChild->height);
		swap(parent, leftChild);
		heapify(pq, (index * 2));
		heapify(pq, index);
		return 1;
	}
	
	
	Point *rightChild = getPoint(pq, (index * 2 + 1));

	if (rightChild != NULL && compare(*parent, *rightChild) == 1)
	{
		//printf("Parent > rightChild\n");
		swap(parent, rightChild);
		heapify(pq, (index * 2 + 1));
		heapify(pq, index);
		return 1;
	}

	return 0; // No changes made.
}




bool isEmpty(PQ *pq) 
{
	if (getPQSize(pq) == 0)
	{
		return true;
	}

	return false;
}



bool containsPoint(PQ *pq, Point p)
{
	int i = 0;
	for (i = 0; i < pq->numberOfElements; i++)
	{
		if (equals(pq->pointArray[i], p))
		{
			return true;
		}
	}
	
	return false; // Point not contained within PQ
}


Point* getPoint(PQ *pq, int i) 
{
	if (i > pq->numberOfElements)
	{
		return NULL;
	}  
	
	return &pq->pointArray[i];
}



/*
 * frees the memory allocated for PQ
 */
void free_PQ(PQ *pq)
{
	if (pq!= NULL)
		free(pq->pointArray);
	free(pq);	
}
