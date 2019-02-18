/**
 * @file PasswordVault.h
 * @author Braelyn Rotman
 * @date June 2018
 * @brief File containing the function definitions for a password vault
 */

#ifndef _PASSWORDVAULT_H_
#define _PASSWORDVAULT_H_

#include "HashTableAPI.h"
#include <stdio.h>
#include <stdlib.h>

/**Function to hash the data using the hash by division method
*@return index to insert data at
*@param tableSize int that holds the size of the table
*@param key string that holds the password key
**/
int hashFunction (size_t tableSize, char *key);

/**Function to clear and free data
*@param data to destroy
**/
void destroyData (void *data);

/**Function to print data - unused
*@param data to be printed
**/
void printData (void *toBePrinted);

/**Function to get password data from user and insert into table
*@param vault hashtable with data
**/
void enterPassword (HTable *vault);

/**Function to find existing passwords
*@return password found in hash table
*@param vault hashtable with data
**/
void *retrievePassword (HTable *vault);

/**Function to change an existing password
*@param vault hashtable with data
**/
void changePassword (HTable *vault);

/**Function remove a password from the table
*@param vault hashtable with data
**/
void deletePassword (HTable *vault);

/**Function to delete all existing passwords
*@param vault hashtable with data
**/
void deleteAll (HTable *vault);

/**Function to set the program password
*@return new program password
**/
char *setPassword();

/**Function to change the program password
*@return new program password
*@param progPass current program password
**/
char *changeProgPass(char *progPass);

#endif
