/*
Assignment 2
CIS 2520
Braelyn Rotman
June 25th, 2018
PasswordVault.c
*/

#include "PasswordVault.h"
#include "HashTableAPI.h"

#include <string.h>
#include <stdlib.h>

int hashFunction (size_t tableSize, char *key){
  int i;
  int ikey = 0;

  for (i = 0 ; i < strlen(key) ; i++)
  {
    ikey = ikey + (int)(key[i]);
  }

  return ikey % tableSize;
}

void destroyData (void *data){

  data = NULL;

  free(data);
}

void printData (void *toBePrinted){

}

void enterPassword (HTable *vault){
  char *password = calloc(30, sizeof(char));
  char *key = calloc(100, sizeof(char));

  system("clear");

  printf("\t**********************\n\t**   NEW PASSWORD   **\n\t**********************\n\n");

  getchar(); /* clear input stream */
  printf("Enter Password Key: ");
  fgets(key, 100, stdin);
  if (key[strlen(key)-1] == '\n')
  {
    key[strlen(key)-1] = '\0';
  }
  printf("Enter a Password: ");
  scanf("%s", password);
  if (password[strlen(password)-1] == '\n')
  {
    password[strlen(password)-1] = '\0';
  }

  /* OVERFLOW SAFETY */

  insertData(vault, key, (void *)(password));

}

void *retrievePassword(HTable *vault)
{
  char *key = calloc(100, sizeof(char));
  void *password;

  system("clear");

  printf("\t***********************\n\t** RETRIEVE PASSWORD **\n\t***********************\n\n");

  /* CLEAR INPUT STREAM */
  getchar();
  printf("Enter Password Key: ");
  fgets(key, 100, stdin);
  if (key[strlen(key)-1] == '\n')
  {
    key[strlen(key)-1] = '\0';
  }

  password = lookupData(vault, key);
  vault->destroyData((void *)(key));

  return password;
}

void changePassword (HTable *vault){
  char *key = calloc(100, sizeof(char));
  void *password;
  char *newPassword = calloc(30, sizeof(char));

  system("clear");

  printf("\t***********************\n\t** CHANGE PASSWORD **\n\t***********************\n\n");

  /* CLEAR INPUT STREAM */
  getchar();
  printf("Enter Key For Password To Change: ");
  fgets(key, 100, stdin);
  if (key[strlen(key)-1] == '\n')
  {
    key[strlen(key)-1] = '\0';
  }

  password = lookupData(vault, key);
  if (password == NULL)
  {
    system("clear");
    printf("ERROR: Password Not Found\n\n");
    vault->destroyData((void *)(key));
    vault->destroyData((void *)(newPassword));
    return;
  }
  else
  {
    printf("Current Password: %s\n\n", (char *)(password));
    removeData(vault, key);
  /*  getchar(); clear input stream */
    printf("Enter New Password: ");
    fgets(newPassword, 30, stdin);
    if (newPassword[strlen(newPassword)-1] == '\n')
    {
      newPassword[strlen(newPassword)-1] = '\0';
    }
    insertData(vault, key, (void *)(newPassword));
    system("clear");
    printf("Password Has Been Changed\n\n");
  }
}

void deletePassword (HTable *vault){
  char *key = calloc(100, sizeof(char));
  void *password;
  char delete = ' ';

  system("clear");

  printf("\t*********************\n\t** DELETE PASSWORD **\n\t*********************\n\n");

  /* CLEAR INPUT STREAM */
  getchar();
  printf("Enter Key For Password To Delete: ");
  fgets(key, 100, stdin);
  if (key[strlen(key)-1] == '\n')
  {
    key[strlen(key)-1] = '\0';
  }

  password = lookupData(vault, key);
  if (password == NULL)
  {
    system("clear");
    printf("ERROR: Password Not Found\n\n");
    vault->destroyData((void *)(key));
    return;
  }
  else
  {
    printf("Password To Delete: %s\n\n", (char *)(password));
    while (delete != 'Y' && delete != 'y' && delete != 'N' && delete != 'n')
    {
      printf("Are You Sure You Want To Delete? (Y/N): ");
      delete = getchar();
      getchar(); /* clear input stream */
    }
    if (delete == 'Y' || delete == 'y')
    {
      removeData(vault, key);
      system("clear");
      printf("Password Has Been Deleted\n\n");
    }
    else
    {
      system("clear");
      printf("Password Was Not Deleted\n\n");
    }
  }
}

void deleteAll (HTable *vault){
  char delete = ' ';

  getchar(); /*clear input stream */
  while (delete != 'Y' && delete != 'y' && delete != 'N' && delete != 'n')
  {
    printf("Are You Sure You Want To Delete All Passwords? (Y/N): ");
    delete = getchar();
    getchar(); /* clear input stream */
    printf("DELETE = '%c'\n", delete);
  }
  if (delete == 'Y' || delete == 'y')
  {
    destroyTable(vault);
    vault = createTable(31, &hashFunction, &destroyData, &printData);
    system("clear");
    printf("Password Has Been Deleted\n\n");
  }
  else
  {
    system("clear");
    printf("No Passwords Were Deleted\n\n");
  }
}

char *setPassword(){
  char *progPass = calloc(30, sizeof(char));

  system("clear");

  printf("\t**************************\n\t** SET PROGRAM PASSWORD **\n\t**************************\n\n");

  getchar(); /* clear input stream */
  printf("Enter New Program Password: ");
  fgets(progPass, 30, stdin);
  if (progPass[strlen(progPass)-1] == '\n')
  {
    progPass[strlen(progPass)-1] = '\0';
  }

  system("clear");
  printf("Program Pass Set\n\n");

  return progPass;
}

char *changeProgPass(char *progPass){

  system("clear");

  printf("\t*****************************\n\t** CHANGE PROGRAM PASSWORD **\n\t*****************************\n\n");

  printf("Current Program Password: %s\n\n", progPass);

  getchar();
  printf("Enter New Program Password: ");
  fgets(progPass, 30, stdin);
  if (progPass[strlen(progPass)-1] == '\n')
  {
    progPass[strlen(progPass)-1] = '\0';
  }

  return progPass;
}
