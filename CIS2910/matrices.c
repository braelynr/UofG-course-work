#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printResult(int[],int[], int);
int compare(const void *a, const void *b)
{
  return ( *(int*)a - *(int*)b );
}

int main()
{
  char buf[50];
  int line = 0; // line #
  int vert = 100; // # of vertices
  int graph = 2; // graph #1 or 2
  int g1[20];
  int g2[20];
  char *token;
  FILE *fp = fopen("input-graphs.txt", "r");

  for (int j = 0 ; j < 20 ; j++) //array reset
  {
    g1[j] = 0;
    g2[j] = 0;
  }

  if (fp == NULL)
  {
    return -1;
  }

  while (fgets(buf,50,fp)) // until end of file
  {
    if(line == 0) // line with # of vertices
    {
      vert = atoi(buf);
      if (graph == 1)
      {
        graph = 2;
      }
      else
      {
          graph = 1;
          for (int j = 0 ; j < 20 ; j++) //array reset
          {
            g1[j] = 0;
            g2[j] = 0;
          }
      }
    }
    else {
      token = strtok(buf, " ");
      int i = 0;
      while (token != NULL)
      {
        if (graph == 1)
        {
          if (atoi(token) == 1)
          {
            g1[i]++;
          }
        }
        else
        {
          if (atoi(token) == 1)
          {
            g2[i]++;
          }
        }
        token = strtok(NULL," ");
        i++;
      }
    }
    line++;
    if ((line == vert + 1))
    {
      qsort(g1, vert, sizeof(int), compare);//SORT ARRAYS
      qsort(g2, vert, sizeof(int), compare);
      if (graph == 2)
      {
        printResult(g1, g2, vert);
      }
      line = 0;
      vert = 0;
    }
  }

  fclose(fp);
  return 0;
}

void printResult(int g1[], int g2[], int vert)
{
  printf("\nDegree seq for G1: ");
  for (int i = 0 ; i < vert ; i++)
  {
    printf("%d ",g1[i]);
  }
  printf("\nDegree seq for G2: ");
  for (int i = 0 ; i < vert ; i++)
  {
    printf("%d ",g2[i]);
  }

  for (int i = 0 ; i < vert ; i++)
  {
    if (g1[i] != g2[i])
    {
      printf("\nThe graphs do NOT have the same degree sequence.");
      return;
    }
  }
  printf("\nThe graphs DO have the same degree sequence.");
}
