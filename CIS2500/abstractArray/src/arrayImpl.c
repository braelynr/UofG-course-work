/*
 Author: James Fraser
 Date: June 10th 
 Purpose: Demonstrate some basic testing concepts
 
 University of Guelph, 2016.
 CIS*2520 (DE) S16
*/

#include "arrayAPI.h"

/****************************** Dummy Structure to show testing ******************************/
/********
This is an example ADT for an Array.  The test harness should test
each of the functions in the array.

*/
Array* createArray(int arraySize, void (*print)(void *), void (*del)(void *))
{
	Array* temp = NULL;

	temp = (Array*)malloc(sizeof(Array));
	if(temp == NULL)
		return NULL;

	temp->arr = NULL;
	temp->size = -1;

	if(arraySize >= 0)
	{
		temp->arr = (void**)malloc(sizeof(void *)*arraySize);
		for(int j=0; j<arraySize; j++)
		{
			temp->arr[j] = NULL;  //initialize array values to NULL;
		}

		temp->size = arraySize;
	}
	temp->printData = print;
	temp->deleteData = del;

	return temp;
}

int positionExists(Array * array, int position)
{
	return (array && array->arr && array->size >= position && position >= 0 );
}

void * getFirstValue(Array * array) 
{
	if(positionExists(array,1))
		return array->arr[0];

	return NULL; //didn't find a value in the first position
}

void modifyValue(Array * array, int position, void * newValue )
{
	if( positionExists(array,position) )
	{
		if(array->arr[position] !=NULL)
			array->deleteData(array->arr[position]);
		array->arr[position] = newValue;
	}
}

int getLength( Array * arr )
{
	if(arr != NULL)
	{
		return arr->size;
	}
	else
		return 0;
}

void printArray( Array * array )
{
	// Handle bad cases where array is not printable.
	if(array == NULL || array->size < 0)
	{
		printf("Array cannot be printed.\n");
		return ;
	}
	// Prints the array.
	for( int i = 0; i<array->size; i++)
	{
		array->printData(array->arr[i]);
		printf("\n");
	}
}

Array * destroyArray(Array * array)
{
	// These checks avoid double free errors.
	// Notice we reset variables to 0 and NULL
	if( (array != NULL) )
	{
		if(array->size >= 0)	
		{
			for(int i=0; i<array->size; i++)
			{
				array->deleteData(array->arr[i]);
			}
			free (array->arr);
			array->arr = NULL;
		}

		array->size = 0;

		free(array);
		return NULL;
	}
	return NULL;

}

