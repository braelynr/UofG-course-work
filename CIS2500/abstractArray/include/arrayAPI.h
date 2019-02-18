/**
@author J.M. & J.F.
@date May 2017
@file array.h
@brief  Small array ADT to demonstrate project organization, use of doxygen, cppcheck, and makefiles
*/

/*
Edited May 2017 by Judi McCuaig to make 
a better example for project structure and coding style
for CIS*2520DE
 Author: James Fraser
 Date: June 10th 
 Purpose: Simple Structure for testing. 
 
 University of Guelph, 2016.
 CIS*2520 (DE) S16
*/

#ifndef SIMPLE_TEST_STRUCTURE_    //these are include guards.  Learn to use them.
#define SIMPLE_TEST_STRUCTURE_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/* Simple structure simpilar to that of an array */
/**
 Array is a simple test structure to provide an example for testing purpose.
   int* arr => contains the data in the array.
   int size => indicates the size of the array.
*/
typedef struct genArray
{
	void * *arr; //array of void * type
	int size;
    void (*printData)(void *toBePrinted);
    void (*deleteData)(void *toBeDeleted);

} Array;

/**
 Creates an array of the size given in the parameter.  Validates parameter to ensure size is appropriate.
 @pre: None
 @post: Array is created if size is valid.
 @param integer value indicated the desired size of array
@return  NULL if size is not valid, returns integer array of appropriate size otherwise.
*/
Array* createArray(int arraySize, void (*print)(void *), void (*del)(void *));



/**
 Checks to see if a position falls within the boundaries of an array.
 @pre Array exists
 @post none
 @param an initialized Array
 @param integer representing the position to check (starting with 0 as the starting point)
 @return  true if the position is valid for the given array, false if the position is outside array boundaries
*/
int positionExists(Array * array, int position);


/**
Returns the integer value at the start of the array  @pre Array exists
 @pre Array is not null
 @post none
 @param Initialized array
 @return  Returns -1 if invalid array size else value at first position of array.
*/
void * getFirstValue(Array * array); 

/**
 Modifies a value at a specific position in the array, if it exists.
 @pre Array exists, position given is valid
 @post Array at given position has changed value
 @param an initialized Array
 @param integer representing the position to check (starting with 0 as the starting point)
 @param integer value to store in the array
*/
void modifyValue(Array * array, int position, void * newValue );



/**
Returns the length or size of the array 
 @pre Array is not null
 @post none
 @param Initialized array
 @return  0 or the length of the array is provided
*/
int getLength( Array * arr );


/**
Prints the integer array 
 @pre Array is not null
 @post Array has been printed to the console. 
 @param Initialized array
*/
void printArray( Array * array );



/**
Destroys the array and frees the memory.
 @pre Array is not null
 @post Array has been destroyed and any memory used has been deallocated. 
 @param Initialized array
*/
Array * destroyArray( Array* array);

#endif // End the Simple Structure

