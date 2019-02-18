#include <stdio.h>
#include "tictactoe.h"

int main(void){

  unsigned short us;
  int i = 0;
  int j = 0;


  for (i = 0 ; i <= 9 ; i++)
  {
    us = i;
    debug(us);
  }
  for (j = 19673 ; j <= 19682 ; j++)
  {
    us = j;
    debug(us);
  }

  return 0;
}
