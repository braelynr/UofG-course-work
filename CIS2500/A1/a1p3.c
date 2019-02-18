/* a1p3.c
   evaluates moves
   Braelyn Rotman
   brotman@uoguelph.ca
   ID: 1006740
*/

#include "tictactoe.h"
#include <stdio.h>

int main(int argc, char *argv[]){

  struct strategy_struct record;
  int i;
  char b3[10];
  char moveInput;
  char moveSearch;
  char won;
  FILE *fp;

  moveInput = atoi(argv[1])+'0'; /* input from command line */

  for (i=0 ; i<=19682 ; i++) /* all possible boards */
  {
    b3fromus(b3, i);
    moveSearch = get_move(b3);
    won = winner(i);
    if (moveInput == moveSearch) /* move inputted is the current move on board */
    {
      if (won == ' ') /* game is not won or tied */
      {
      printf("%d,", i);
      evaluate_move(i, &record); /* evaluate possible moves */
      }
      else /* game is won */
      {
          record.best_move = -1;
          record.winner = won;
          printf("[%d],", i);
          fp = fopen("strategyfile", "rb+");
          set_record(fp, i, &record);
          fclose(fp);
      }
    }
  }

  printf("\n");

  return 0;
}
