/* a1p2.c
   creates strategy file
   Braelyn Rotman
   brotman@uoguelph.ca
   ID: 1006740
*/

#include "tictactoe.h"

int main (){
  FILE * fp;
  struct strategy_struct record;
  int i;

  /* set default record settings */
  record.best_move = -1;
  record.winner = ' ';

  fp = fopen("strategyfile", "wb"); /* creates strategy file */

  for (i = 0 ; i <19683 ; i++) /* all possible boards */
  {
    fwrite(&record, sizeof(struct strategy_struct), 1, fp);
  }
  fclose(fp);

  return 0;
}
