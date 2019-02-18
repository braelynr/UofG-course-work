#include <stdio.h>
#include <stdbool.h>
const int n = 8; /* order n */
int numDerangements = 0;

void printPerm(int perm[]) /* print permutation */
{
  for (int i = 0 ; i < n ; i++)
  {
    printf("%d,", perm[i]);
  }
  printf("\n");
}

bool checkEnd(int perm[]) /* check if final permutation */
{
  for (int i = 0 ; i < n ; i++)
  {
    if (perm[i] != n-i)
    {
      return false;
    }
  }
  return true;
}

void checkDerangement(int perm[])
{
  for (int i = 0 ; i < n ; i++)
  {
    if (perm[i] == i + 1)
    {
      return; /* not a derangement */
    }
  }
  numDerangements++;
  if (numDerangements == 100)
  {
    printf("Derangement 100 = ");
    printPerm(perm);
  }
}

void findPerms(int perm[])
{
  int i = 0;
  bool end = false;
  printPerm(perm);

  while (end == false)
  {
    for (i = n-2 ; i >= 0 ; i--) /* find lower on left */
    {
      if (perm[i] < perm[i+1]) /* swap and sort */
      {
        break;
      }
    }
    int highRight = i+1; /* this is the highest number on right side that is lower than the current */
    for(int j = i+2 ; j <= n-1 ; j++)
    {
      if (perm[j] > perm[i] && perm[j] < perm[highRight])
      {
        highRight = j;
      }
    }
    int temp = perm[i];
    perm[i] = perm[highRight];
    perm[highRight] = temp;

    if (i != n-2)
    {
      for (int j = i+1; j < n ; j++)
      {
        for (int k = j+1 ; k < n ; k++)
        {
          if (perm[j] > perm[k])
          {
            int temp = perm[j];
            perm[j] = perm[k];
            perm[k] = temp;
          }
        }
      }
    }
  checkDerangement(perm);
  /*printPerm(perm);*/
  end = checkEnd(perm);
  }
}

int main()
{
  int perm[n];
  for (int i = 1 ; i <= n ; i++) /* set first permutation */
  {
    perm[i-1] = i;
  }
  printf("All permutations of n = %d:\n", n);
  findPerms(perm);
  printf("Number of Derangements of n = %d: %d\n", n, numDerangements);

  return 0;
}
