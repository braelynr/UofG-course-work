/* Braelyn Rotman
   September 25th, 2018
   Fibber Sequence Term Finder */

#include <stdio.h>

int count; /* current term */
unsigned long current; /* int is too small to handle higher terms */

unsigned long fibber (int n)
{
    current = current * 2; /* get new term */
    count++; 

    if (count == n) /* if nth term is reached */
    {
      return current; /* return current term */
    }
    else
    {
        return fibber(n); /* recursive call */
    }
}

int main()
{
    int n = 0;
    unsigned long a1 = 1;
    unsigned long a2 = 1;
    current = a1 + a2;
    count = 3;

    printf("Enter N'th term: "); /* Enter desired term */
    scanf("%d", &n);

    /* if n <= 2 we already have the term */
    if (n == 1)
    {
      printf("Term %d is %lu\n", n, a1);
    }
    else if (n == 2)
    {
      printf("Term %d is %lu\n", n, a2);
    }
    else if (n == 3)
    {
      printf("Term %d is %lu\n",n, current);
    }
    else
    {
      printf("Term %d is %lu\n", n, fibber(n));
    }

    return 0;
}
