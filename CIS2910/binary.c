/* Braelyn Rotman
   October 11, 2018
   CIS 2910
   Assignment 2 Question 9 */

#include <stdio.h>
#include <stdbool.h>

int main(void){
  int n = 0; /* length of binary strings */
  bool end = false; /* false until all binary strings are printed */

  while (n <= 5) /* n must be > 5 */
  {
    printf("Enter Binary String Length: ");
    scanf("%d", &n);
    printf("n = %d\n",n);
  }

  int binary[n]; // array represents a binary number of length n;

  for (int i = 0 ; i < n ; i++) /* initialize array */
  {
    binary[i] = 0;
  }

  while (end == false) /* until all binary #'s are printed */
  {

    for (int p = n - 1 ; p >= 0 ; p--) /* print binary # */
    {
      printf("%d", binary[p]);
    }
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

  return 0;
}
