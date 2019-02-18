/**
 * @file hospital.h
 * @author Braelyn Rotman
 * @date July 2018
 * @brief File containing the extra function for Assignment 3
 */

#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "QueueADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
*client structure
**/
typedef struct client{
    char * ID; ///< client ID string
    int priority; ///< client priority (1-5)
    char * code; ///< client symptom code
} client;

/**Function to print the final report to report.txt
*@param treated queue of clients treated in order of treatment start time
*@param timer1 simulation time with no specialist doctors
*@param timer2 simulation time with specialist doctors
**/
void printReport(Queue *treated, int timer1, float timer2);

/** Function to clear and free data
*@param data data to be cleared and then freed
**/
void destroyData(void *data);

/** Function to compare client priorities
*@param first first client to compare
*@param second second client to compare
**/
int compare(const void *first, const void *second);

/** Function to print a queue list
*@param queue queue containing list to print
**/
void printList (Queue *queue);

#endif
