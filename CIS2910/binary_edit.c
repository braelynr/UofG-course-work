/* Braelyn Rotman
   October 11, 2018
   CIS 2910
   Assignment 2 Question 9 */

#include <stdio.h>
#include <stdbool.h>

int main(void){
  int n = 0; /* length of binary strings */
  bool end = false; /* false until all binary strings are printed */
  int c = 1;
  int num0 = 0;
  int ones = 2;
  int count = 0;

  printf("Enter Binary String Length: ");
  scanf("%d", &n);

  int binary[n]; // array represents a binary number of length n;

  for (int i = 0 ; i < n ; i++) /* initialize array */
  {
    binary[i] = 0;
  }

  while (end == false) /* until all binary #'s are printed */
  {
  /*  c =1;*/
    ones = 2;
    for (int p = n - 1 ; p >= 0 ; p--) /* print binary # */
    {
      printf("%d", binary[p]);
      if (binary[n-1] == 1 && binary[n-2] == 1 && p < n-2)
      {
        if (binary[p] == 1)
        {
          ones++;
        }
      }
      if (p>0 && binary[p] == binary[p-1])
      {
        c++;
        if (c == 5)
        {
          count++;
        }
      }
      else
      {
        c = 1;
      }
     /*if (binary[p] == 0)
      {
        num0++;
      }*/
    }
    if (ones == 5)
    {
    /*  count++;*/
    }
  /*  if (num0 >= 4)
    {
      count++;
    }
    num0 = 0;*/

    printf("\n");

    binary[0]++;
    for (int j = 0 ; j < n ; j++)
    {
      if (binary[j] == 2)
      {
        binary[j] = 0; /* set back to 0 */
        if (j + 1 != n) /* keeps in array bounds */
        {
          binary[j+1]++; /* carry the 1 */
        }
        else
        {
          end = true;
          break; /* highest binary # reached */
        }
      }
    }
  }
  printf("thing %d\n", count);
  return 0;
}
