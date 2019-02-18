/* a1p4.c
   runs debug 2
   Braelyn Rotman
   brotman@uoguelph.ca
   ID: 1006740
*/

#include "tictactoe.h"

int main(int argc, char *argv[]){
  unsigned short us;

  us = atoi(argv[1]); /* input from command line */
  debug_2(us);

  return 0;
}
