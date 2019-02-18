/* main.c */
#include <stdio.h>
#include "bow.h"


int main()
{

  char *sentence = "#The quick brown fox jumped over 23&%^24 the lazy dogs.\0"; /* test sentence */


  struct bag_struct *bagstruct; 

  bagstruct = new_bag();
/*  printf("Total words (0) = \"%d\"\n", bagstruct->total_words);

  printf( "sentence = \"%s\"\n", sentence );  /* show the sentence */

  add_text(bagstruct, sentence);
/*  printf("word in struct = %s word in bag = %s\n", wordstruct->word, bagstruct->bag->word);
*/
  /*  printf("EXIT CHARACTER = \"%c\"\n", *sentence);*/

  free(bagstruct);


  return 0;
}

/*
int main()
{

  char *sentence = "#The quick brown fox jumped over 23&%^24 the lazy dogs.\0"; /* test sentence
  struct bag_struct *bow;

  bow = new_bag();
/*  printf("Total words (0) = \"%d\"\n", bagstruct->total_words);

  printf( "sentence = \"%s\"\n", sentence );  /* show the sentence
  read_sms_data(bow, "ham" );
/*  printf("word in struct = %s word in bag = %s\n", wordstruct->word, bagstruct->bag->word);
*/
  /*  printf("EXIT CHARACTER = \"%c\"\n", *sentence);

  free(bow);


  return 0;
}
*/
