/*
Assignment 2
CIS 2520
Braelyn Rotman
June 25th, 2018
main.c
*/

#include "HashTableAPI.h"
#include "PasswordVault.h"

#include <stdbool.h>
#include <string.h>

int main(void){
  char option = '0';
  char *progPass = calloc(30, sizeof(char));
  char *inputPassword;
  HTable *vault;
  bool fileExists;
  FILE *fp;
  int i;
  Node *current;
  char *password;
  void *retrieved;
  char *key;
  int line = 0;

  vault = createTable(31, &hashFunction, &destroyData, &printData);
  fp = fopen("passwordFile.txt", "r");
  if (fp == NULL)
  {
    fileExists = false;
  }
  else
  {
    fileExists = true;

    while(!feof(fp))
    {
      if (line == 0)
      {
        fgets(progPass, 30, fp);
        if (progPass[strlen(progPass)-1] == '\n')
        {
          progPass[strlen(progPass)-1] = '\0';
        }
        line = 1;
      }
      else if(line == 1)
      {
        key = calloc(100, sizeof(char));
        fgets(key, 100, fp);
        if (key[strlen(key)-1] == '\n')
        {
          key[strlen(key)-1] = '\0';
        }
        line = 2;
      }
      else
      {
        password = calloc(30, sizeof(char));
        fgets(password, 30, fp);
        if (password[strlen(password)-1] == '\n')
        {
          password[strlen(password)-1] = '\0';
        }
        line = 1;
        insertData(vault, key, (void *)(password));
      }
    }

    fclose(fp);
  }
/*
  if (strcmp(progPass, "") == 0)
  {
    memset(progPass, '\n', sizeof(char));
  }*/
  system("clear");

  if(strcmp(progPass, "") != 0)
  {
    inputPassword = calloc(30, sizeof(char));
    printf("\t**********************\n\t**  PASSWORD VAULT  **\n\t**********************\n\n");
    printf("Enter Program Password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputPassword, progPass) == 0)
    {
      system("clear");
    }
    else
    {
      printf("\nIncorrect Password\n\n");
      exit(-1);
    }
  }



  while (option != '9')
  {
    printf("\t**********************\n\t**  PASSWORD VAULT  **\n\t**********************\n\n");

    printf("Options:\n\n");
    printf("\t1. Create A New Password File\n");
    printf("\t2. Enter A New Password\n");
    printf("\t3. Retrieve An Existing Password\n");
    printf("\t4. Change An Existing Password\n");
    printf("\t5. Delete An Existing Password\n");
    printf("\t6. Set Program Password\n");
    printf("\t7. Change Program Password\n");
    printf("\t8. Delete All Existing Passwords\n");
    printf("\t9. Save Changes and Quit\n\n");

    printf("Enter Option Number: ");
    scanf(" %c", &option);

    if (option == '1')
    {
      if (fileExists == false)
      {
        fp = fopen("passwordFile.txt", "w");
        fclose(fp);
        fileExists = true;

        system("clear");
        printf("New Password File Created\n\n");
      }
      else
      {
        system("clear");
        printf("Password File Already Created\n\n");
      }
    }
    else if (option == '2')
    {
      if (fileExists == false)
      {
        system("clear");
        printf("ERROR: No Password File Created\n\n");
      }
      else
      {
        enterPassword(vault);
        system("clear");
        printf("New Password Entered\n\n");
      }
    }
    else if (option == '3')
    {
      if (fileExists == false)
      {
        system("clear");
        printf("ERROR: No Password File Created\n\n");
      }
      else
      {
        retrieved = retrievePassword(vault);
        system("clear");
        if ((char *)(retrieved) != NULL)
        {
          printf("Your Password Is: %s\n\n", (char *)(retrieved));
        }
        else
        {
          printf("ERROR: Password Not Found\n\n");
        }
      }
    }
    else if (option == '4')
    {
      if (fileExists == false)
      {
        system("clear");
        printf("ERROR: No Password File Created\n\n");
      }
      else
      {
        changePassword(vault);
      }
    }
    else if (option == '5')
    {
      if (fileExists == false)
      {
        system("clear");
        printf("ERROR: No Password File Created\n\n");
      }
      else
      {
        deletePassword(vault);
      }
    }
    else if (option == '6')
    {
      if (fileExists == false)
      {
        system("clear");
        printf("ERROR: No Password File Created\n\n");
      }
      else if (strcmp(progPass, "") != 0)
      {
        system("clear");
        printf("ERROR: Program Password Already Set\n\n");
      }
      else
      {
        destroyData((void *)(progPass));
        progPass = setPassword();
      }

    }
    else if (option == '7')
    {
      if (fileExists == false)
      {
        system("clear");
        printf("ERROR: No Password File Created\n\n");
      }
      else if (strcmp(progPass, "\n") == 0)
      {
        system("clear");
        printf("ERROR: Program Password Never Set\n\n");
      }
      else
      {
        progPass = changeProgPass(progPass);
        system("clear");
        printf("Program Password Has Been Changed\n\n");
      }
    }
    else if (option == '8')
    {
      if (fileExists == false)
      {
        system("clear");
        printf("ERROR: No Password File Created\n\n");
      }
      else
      {
        deleteAll(vault);
      }
    }
    else if (option != '9')/* INVALID OPTION */
    {
      system("clear");
      printf("INVALID OPTION NUMBER\n\n");
      option = '0';

    }
  }

  /* WRITE TO FILE BEFORE QUITTING */
  fp = fopen("passwordFile.txt", "w+");

  fprintf(fp, "%s", progPass);
  fprintf(fp, "\n");

  for (i = 0 ; i < vault->size ; i++)
  {
    current = vault->table[i];
    while (current != NULL)
    {
    /*  fwrite(*current->data, sizeof(void), 1, fp);
      fwrite(current->key, sizeof(char)*100, 1, fp); */
    /*  printf("%s\n%s\n", current->key, (char *)(current->data));
*/
      fprintf(fp, "%s\n%s\n", current->key, (char *)(current->data));

      current = current->next;
      if (current != NULL)
      {
        fprintf(fp, "\n");
      }
    }
  }

  fclose(fp);

  /* DELETE ALL DATA */
  destroyTable(vault);

  printf("\n\n");

  return 0;
}
