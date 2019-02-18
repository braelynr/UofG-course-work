/* a1p5.c
   Tic Tac Toe game
   Braelyn Rotman
   brotman@uoguelph.ca
   ID: 1006740
*/

#include "tictactoe.h"

int main(void){

  struct strategy_struct record;
  char name[50];
  char player;
  unsigned short us;
  char b3[10];
  char board[60];
  char turn;
  int move = -1;
  char won = ' ';
  FILE * fp;

  b3[9]='\0';

  printf("SHALL WE PLAY A GAME?\n\n");
  printf("PLEASE ENTER YOUR NAME:  ");
  fgets(name, 50, stdin); /* gets player name */
  printf("GREETINGS %s\n", name);
  while (player != 'O' && player != 'X') /* check for valid input */
  {
    printf("Which side would you like to play (X/O)? ");
    scanf("%c", &player); /* player chooses piece */
    printf("\n");

    if (player == 'O')
    {
      printf("Ok, you will be O; I will be X.\n");
    }
    else if (player == 'X')
    {
      printf("Ok, you will be X; I will be O.\n");
    }
  }
  us=0; /* empty board */
  b3fromus(b3, us);
  while (won==' ') /* game is not yet finished */
  {
    turn = get_turn(b3); /* get turn */
    boardfromb3(board, b3);
    printf("\n%s\n\n", board); /* print current board */
    /* if computers turn to play */
    if ((turn == '2' && player == 'O') || (turn == '1' && player == 'X'))
    {
      fp = fopen("strategyfile", "rb");
      get_record(fp, us, &record); /* get record for board */
      fclose(fp);
      printf("My turn; my move is %d\n", record.best_move);
      move = record.best_move; /* play best move */
    }
    else /* players turn */
    {
        printf("Your turn; chose a move [0-8]: ");
        scanf("%d", &move); /* get move from player */
        printf("\n");
    }
    b3[move] = turn; /* set move in b3 */
    us = b3tous(b3);
    won = winner(us); /* check if game is finished */
  }

  boardfromb3(board, b3); /* show final board */
  printf("\n%s\n\n", board);
  /* if computer wins */
  if ((won == '2' && player == 'O') || (won == '1' && player == 'X'))
  {
    printf("I won!\n\n");
    printf("A STRANGE GAME.\nTHE ONLY WINNING MOVE IS\nNOT TO PLAY.\n");
  }
  else if (won == '0') /* the game is a tie */
  {
    printf("The game is a tie.\n");
  }
  else /* player wins */
  {
    printf("You won!\n\n");
  }

  return 0;
}
