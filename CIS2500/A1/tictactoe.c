/* tictactoe.c
   Functions File
   Braelyn Rotman
   brotman@uoguelph.ca
   ID: 1006740
*/

#include "tictactoe.h"
#include <stdio.h>

/* convert b3 format to unsigned short */
unsigned short b3tous( char b3[10] )
{
  unsigned short us=0;
  int i=0;
  int num;
  int value=1;

  for (i=8; i>=0; i--) /* each position in b3 */
  {
    num=b3[i]-'0';
    us= us+(num*value);
    value=value*3;
  }

  return us;
}

/* convert unsigned short to b3 format */
void b3fromus( char b3[10], unsigned short us )
{
  int i = 0;
  b3[9] = '\0';
  for (i = 8; i>=0; i--)
  {
    /*printf("%d\n", us%3);*/
    b3[i] = '0'+ (us%3);
    us=us/3;
  }
}
 /* debug function for a1p1 */
void debug(unsigned short us)
{
  char b3[10];
  char board[60];
  char movenum;
  char turn;
  char win;
  int i;

  b3fromus(b3, us);

  printf("Board number: %5d\n", us);
  printf("Board pic: %9s\n", b3);

  us=b3tous(b3);
  /*printf("us = %5d\n", us);*/

  boardfromb3(board, b3);
  printf("%s\n", board);

  b3fromboard(board, b3);
  /*printf("b3 = %9s\n", b3);*/

  movenum = get_move(b3);
  printf("Move: %c\n", movenum);
  turn = get_turn(b3);
  printf("Turn: %c\n", turn);

  win = winner(us);
  printf("Winner: %c\n", win);

  for (i=0 ; i<=8 ; i++) /* each position on board */
  {

    printf("%d -> %5d\n", i, next(us, i+'0'));

  }

  printf("\n");
}

/* debug function for a1p4 - a1p5 */
void debug_2(unsigned short us){
  struct strategy_struct record;
  char b3[10];
  char board[60];
  char movenum;
  char turn;
  char win;
  int i;
  FILE *fp;

  b3fromus(b3, us);
  printf("Board number: %5d\n", us);
  printf("Board pic:\n");
  /* printf("Board pic: %9s\n", b3); */

  us=b3tous(b3);
  /*printf("us = %5d\n", us);*/

  boardfromb3(board, b3);
  printf("%s\n", board);

  b3fromboard(board, b3);
  /*printf("b3 = %9s\n", b3);*/

  movenum = get_move(b3);
  printf("Move: %c\n", movenum);
  turn = get_turn(b3);
  printf("Turn: %c\n", turn);

  win = winner(us);
  if (us == 0)
  {
    win = '0';
  }
  printf("Winner: %c\n", win);

  fp = fopen("strategyfile", "rb");
  get_record(fp, us, &record); /* get record for current board */
  printf("best_move=%d, winner=%c\n", record.best_move, record.winner);
  fclose(fp);

  for (i=0 ; i<=8 ; i++) /* positions on board */
  {

    printf("%d -> %5d\n", i, next(us, i+'0'));

  }

  printf("\n");
}

/* gets the board string from b3 format */
void boardfromb3( char board[60], char b3[10] )
{
  int p = 0;
  char move = '0';
  strcpy( board, "   |   |   \n---+---+---\n   |   |   \n---+---+---\n   |   |   ");

  for (p = 8 ; p >= 0 ; p--) /* positions in b3 */
  {
    move = b3[p];
    switch(move)
    {
      case '0': /* no piece */
        board[(4*p+1)+((p/3)*12)]=' ';
        break;
      case '1': /* O */
        board[(4*p+1)+((p/3)*12)]='O';
        break;
      case '2': /* X */
        board[(4*p+1)+((p/3)*12)]='X';
        break;
      default:
        fprintf( stderr, "Error: bad value in b3\n");
        exit(-1);
        break;
    }
  }
}

/* gets b3 format from the board string */
void b3fromboard (char board[60], char b3[10])
{
  int p = 0;
  char move = ' ';

  for (p = 8 ; p >= 0 ; p--) /* positions on board */
  {
    move = board[(4*p+1)+((p/3)*12)];
    switch(move)
    {
      case ' ': /* no piece */
        b3[p]='0';
        break;
      case 'O':
        b3[p]='1';
        break;
      case 'X':
        b3[p]='2';
        break;
      default:
        fprintf( stderr, "Error: bad value in board\n");
        exit(-1);
        break;
    }
  }
}

/* gets the current move number */
char get_move (char b3[10])
{
  int p;
  int moveNumber;
  int counter = 0;
  for (p = 8 ; p >= 0 ; p--) /* positions in b3 */
  {
    if (b3[p]=='0') /* counts blank spaces on board */
    {
      counter++;
    }
  }
  moveNumber= 9 - counter + '0'; /* calculates how many peices are on board */

  return moveNumber;
}

/* get the turn number */
char get_turn(char b3[10])
{
  int i;
  int moveCount = 0;
  for (i = 0 ; i <= 8 ; i++) /* positions in b3 */
  {
    if (b3[i] == '1' || b3[i] == '2')
    {
      moveCount++; /* number of pieces on board */
    }
  }

  if (moveCount % 2 == 0)
  {
    return '2'; /* x's turn now */
  }
  else
  {
    return '1';/* o's turn now */
  }
}

/* finds the winner */
char winner(unsigned short us)
{
  char b3[10];
  int i;
  int pieces = 0;
  b3fromus(b3, us);

  /* if O has won */
  if (b3[0] == '1' && b3[1] == '1' && b3[2] == '1')
  {
    return '1';
  }
  else if(b3[3] == '1' && b3[4] == '1' && b3[5] == '1')
  {
    return '1';
  }
  else if(b3[6] == '1' && b3[7] == '1' && b3[8] == '1')
  {
    return '1';
  }
  else if(b3[0] == '1' && b3[3] == '1' && b3[6] == '1')
  {
    return '1';
  }
  else if(b3[1] == '1' && b3[4] == '1' && b3[7] == '1')
  {
    return '1';
  }
  else if(b3[2] == '1' && b3[5] == '1' && b3[8] == '1')
  {
    return '1';
  }
  else if(b3[0] == '1' && b3[4] == '1' && b3[8] == '1')
  {
    return '1';
  }
  else if(b3[2] == '1' && b3[4] == '1' && b3[6] == '1')
  {
    return '1';
  }
  /* if x has won */
  else if (b3[0] == '2' && b3[1] == '2' && b3[2] == '2')
  {
    return '2';
  }
  else if(b3[3] == '2' && b3[4] == '2' && b3[5] == '2')
  {
    return '2';
  }
  else if(b3[6] == '2' && b3[7] == '2' && b3[8] == '2')
  {
    return '2';
  }
  else if(b3[0] == '2' && b3[3] == '2' && b3[6] == '2')
  {
    return '2';
  }
  else if(b3[1] == '2' && b3[4] == '2' && b3[7] == '2')
  {
    return '2';
  }
  else if(b3[2] == '2' && b3[5] == '2' && b3[8] == '2')
  {
    return '2';
  }
  else if(b3[0] == '2' && b3[4] == '2' && b3[8] == '2')
  {
    return '2';
  }
  else if(b3[2] == '2' && b3[4] == '2' && b3[6] == '2')
  {
    return '2';
  }
  else /* neither has won */
  {
    for (i = 0 ; i <=8 ; i++) /* positions in b3 */
    {
      if (b3[i] == '1' || b3[i] == '2')
      {
        pieces++; /* count pieces on board */
      }
    }
    if (pieces == 9) /* board is full */
    {
      return '0'; /* the game is a tie */
    }
  }

  return ' '; /* no winner or tie */
}

/* looks at next move */
unsigned short next (unsigned short us, char pos)
{
  char b3[10];
  char turn;

  b3fromus(b3, us);
  if (b3[pos-'0'] != '0') /* position is already taken */
  {
    return 0;
  }
  turn = get_turn(b3); /* get turn number */

  if (turn == '2') /* X's turn */
  {
    b3[pos-'0']='2';
  }
  else /* O's turn */
  {
    b3[pos-'0']='1';
  }

  us=b3tous(b3); /*new unsigned short */

  return us;
}

/* gets a record from the strategy file */
void get_record(FILE *fp, unsigned short us, struct strategy_struct *record)
{

  fseek(fp, us*sizeof(struct strategy_struct), SEEK_SET);
  fread(record, sizeof(struct strategy_struct), 1, fp);

}

/* writes a record in the strategy file */
void set_record(FILE *fp, unsigned short us, struct strategy_struct *pRecord)
{
  fseek(fp, us*sizeof(struct strategy_struct), SEEK_SET);
  fwrite(pRecord, sizeof(struct strategy_struct), 1, fp);
}

/* evaluates all possible next moves */
void evaluate_move(unsigned short us, struct strategy_struct *record )
{
  int p;
  FILE * fp;
  struct strategy_struct tempr;
  char turn;
  char b3[10];
  int tiePos;
  int found_tie=0;
  int legal_move =0;
  unsigned short newus;

  b3fromus(b3,us);
  turn = get_turn(b3);

  for (p=0 ; p<=8 ; p++) /* positions on board */
  {
    newus = next(us, p+'0'); /* get next possible board */
    if (newus != 0) /* not invalid board */
    {
      fp = fopen("strategyfile", "rb");
      get_record(fp, newus, &tempr); /* gets current record */
      fclose(fp);
      /*printf("\n\n TempR.Winner=%c Turn=%c\n\n", tempr.winner, turn);
      */
      if (tempr.winner == turn)
      /* if the winner is whos turn it is
      if(tempr.winner == turn)*/
      {
        record->winner = tempr.winner;
        record->best_move = p;
      /*  printf("!!!!winner=%c, bestmove=%d\n", record->winner, record->best_move); */
        fp = fopen("strategyfile", "rb+");
        /* Found the best move, record for the current board */
        set_record(fp, us, record);
        fclose(fp);
        return;
      }
      else if (tempr.winner == '0' ) /* game is a tie */
      {
        tiePos=p;
        found_tie=1;
        /*printf("FOUND TIE:tiePos=%d found tie= %d, winner=%c, bestmove=%d\n", tiePos, found_tie, record->winner, record->best_move);*/
      }
      else /* a legal move that does not win or tie */
      {
        legal_move=p;
      }
    }
  }
  if (found_tie == 1) /* if the move will tie */
  {
    record->best_move = tiePos;
    record->winner = '0';
    /*printf("TIE: winner=%c, bestmove=%d\n", record->winner, record->best_move);*/
    fp = fopen("strategyfile", "rb+");
    set_record(fp, us, record);
    fclose(fp);
  }
  else if (found_tie == 0) /* the move won't win or tie */
  {
    printf(" ");
    record->best_move = legal_move;
    if (turn == '1')
    {
      record->winner = '2'; /*value of opponent*/
    }
    else{
      record->winner ='1';
    }

    /*printf("winner=%c, bestmove=%d\n", pRecord->winner, pRecord->best_move);*/
    fp = fopen("strategyfile", "rb+");
    set_record(fp, us, record);
    fclose(fp);
  }

}
