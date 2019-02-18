
/*
 Author: James Fraser
 Date: June 10th 
 Purpose: Demonstrate some basic testing concepts
 
 University of Guelph, 2016.
 CIS*2520 (DE) S16
*/

#include "arrayAPI.h"

//print function for string test data
void printme(void * data)
{
	printf("%s",(char *)data);
}

int main(int argc, char ** argv)
{
	// Don't really have a task here.
	// So add a couple of data elements,print, and leave.
	// This is not testing the array, it's using it.
	Array * arr = createArray(3, &printme, &free); //because my data is just a string I can send free as the cleanup function
	char * name = malloc(sizeof(char)*10);
	char * cat = malloc(sizeof(char)*10);
	char * dog = malloc(sizeof(char)*10);
	strcpy(name, "judi");
	strcpy(cat, "baldr");
	strcpy(dog, "branwen");
	
	modifyValue(arr,0, (void *) name);
	modifyValue(arr,2, (void *) cat);
	modifyValue(arr,1, (void *) dog);

	printf("Here is the array:\n");
	printArray( arr );
	printf("\n\n");
	
	arr = destroyArray( arr );

	printf("\nPrint array again to show it has been destroyed:\n");
	printArray(arr);
	printf("endprint\n");

	return 0;
}	
