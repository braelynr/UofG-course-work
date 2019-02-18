/* bow.c
*string pointer is the string
**string pointer is the character
*/

#include "bow.h"


struct bag_struct *new_bag()
{
  struct bag_struct *bagstruct = malloc(sizeof(struct bag_struct));

  bagstruct->bag = NULL;
  bagstruct->bag_size = 0;
  bagstruct->total_words = 0;

  return bagstruct;

}

int bagsearch( struct bag_struct *bow, char *word )
{
  int middle = (bow->bag_size)/2;
    int cmp = 0;
    int numWordsR= 0; /*number of words to the right */
    int numWordsL= 0;
    struct bag_struct *ptNewbow = new_bag();
    int returnpos = 0 ;
  /*return(0);*/
  printf("test\n");
  if (bow->bag_size>0)
  {
    printf( "\nSearching bag starting at \"%s\" with %d elements\n", bow->bag[0].word, bow->bag_size );
  /* use bag_size because it is the number of stored words (no duplicates)*/
  /*printf("bag_size = %d\ntotal words=%d\n",bow->bag_size, bow->total_words);
  /*print_bag(bow);*/
  /*printf("middle=%d middle-word=%s add-word=%s\n", middle, bow->bag[middle].word, word);

  */
    printf("middle=%d\n",middle);
    printf( "bow->bag[middle].word= %s    word= %s\n", bow->bag[ middle ].word, word );
    cmp =strcmp(bow->bag[middle].word, word);
    printf("cmp = %d\n", cmp);
  }
  /* if we have only 1 word we know we have found the position - left or right or matching */
    if((bow->bag_size<=1) )/*|| (middle==0))*/
    {
      /*printf("exiting - bagsize=%d\n",bow->bag_size);
    */
      free_bag(ptNewbow);
      /*AT MOST 1 element, need to decide to return left or right */
      if (cmp>0) /* left side */
      {

        return 0;
      }
      else if (cmp<0)
      {
        return 1;
      }

    }

    if (cmp < 0) /* search second half of bag*/
    {
      printf("in cmp < 0\n");
      numWordsR = bow->bag_size -middle-1;

      if (numWordsR>=1)
      {

        ptNewbow->bag = malloc(sizeof(struct word_count_struct)*numWordsR);

      /*  printf("bag_size=%d numwordsR=%d middle=%d\n", bow->bag_size, numWordsR, middle);*/
        memcpy(&ptNewbow->bag[0], &bow->bag[middle+1], sizeof(struct word_count_struct)*numWordsR);

        ptNewbow->bag_size = numWordsR;

        /*print_bag(ptNewbow);*/
        /* adding to right side of middle,so add to right */
        returnpos = middle+1 + bagsearch(ptNewbow, word);
        printf("RIGHT returnpos = %d   middle = %d\n", returnpos, middle);
      }
      else
      {
        printf("RIGHT returnpos = %d   middle = %d\n", returnpos, middle);
        return 1+middle; /*no words to right, add this to right */
      }

    }
    else if (cmp > 0) /* search first half*/
    {
      printf("in cmp > 0\n");
      numWordsL = middle;
      ptNewbow->bag = malloc(sizeof(struct word_count_struct)*numWordsL);

    /*  printf("bag_size=%d numwordsL=%d middle=%d\n", bow->bag_size, numWordsL, middle);*/
      memcpy(&ptNewbow->bag, &bow->bag, sizeof(struct word_count_struct)*numWordsL);
      ptNewbow->bag_size = numWordsL;


      /*print_bag(ptNewbow);*/
      printf("word = %s\n", word);
      returnpos = bagsearch(ptNewbow, word);
  printf("LEFT returnpos = %d   middle = %d\n", returnpos, middle);
    }
    else
    {
      if (bow->bag_size>0)
      {
        printf("in cmp = 0\n");
      /* word is same*/
        free_bag(ptNewbow);
        returnpos =1;
      }
    }

  /*
  printf("WE EXITED\n");
  */

  printf("final return pos = %d\n", returnpos);
    return returnpos;
}

char *get_word( char **string_ptr )
{

  char *word;
  int index = 0;
  int i;

  word = malloc( 919 );
  strcpy( word, "bird" );

  while ((is_letter(**string_ptr)==0) && (**string_ptr!='\0')) /*not a letter */
  {
    *string_ptr += 1;

  }
  while ((is_letter(**string_ptr)!=0) && (**string_ptr!='\0')) /* is a letter */
  {
    word[index] = **string_ptr;
    index++;
    *string_ptr += 1;
    word[index] = '\0';
  }

  if (**string_ptr=='\0')
  {
    free(word);
    return NULL;
  }
  word = realloc(word, strlen(word)+1);

  /* CHANGE TO LOWERCASE */
  for (i = 0; i< strlen(word); i++)
  {
    word[i] = tolower(word[i]);
  }

  return word;
}

int is_letter( char character)
{
  if (isalpha(character)==0) /* not a letter */
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

struct word_count_struct *new_word_count( char *word )
{
  struct word_count_struct *stNewWord = malloc(sizeof(struct word_count_struct));
  stNewWord->word = word;
  stNewWord->count = 1;

  return stNewWord;

}

void free_word_count( struct word_count_struct *wordstruct)
{

  free(wordstruct);
}

void print_word_count(struct word_count_struct *word_count)
{
  printf("%s: %d\n", word_count->word, word_count->count);
}

void add_word( struct bag_struct *bow, char *word )
{
  struct word_count_struct *wordstruct = NULL;
  int pos = 0;

  if (word != '\0')
  {
    wordstruct = new_word_count(word);
    /*
    Search if the word is already in our bag, increment the counter
    otherwise: allocate another word_count_struct and add new word
    */

    /*if(bow->bag_size>0)
    {*/
  pos = bagsearch(bow, word);
  printf("bagsearch = %d\n", pos);
  /*}*/
  /*printf("pos = %d bagsize = %d\n", pos, bow->bag_size);
  */
  if (bow->bag_size == 0) /* first word - empty bag */
  {
    bow->bag_size = bow->bag_size + 1;
    bow->bag = realloc(bow->bag, ((sizeof(struct word_count_struct) )*( bow->bag_size)));
      memcpy(&bow->bag[pos], wordstruct, sizeof (struct word_count_struct)); /* adds the new word */
  }
  else /* not first word */
  {
    if (pos>=bow->bag_size) /* adding new word at right end */
    {
      bow->bag_size = bow->bag_size + 1;
      bow->bag = realloc(bow->bag, ((sizeof(struct word_count_struct) )*( bow->bag_size)));

      memcpy(&bow->bag[pos], wordstruct, sizeof (struct word_count_struct)); /* adds the new word */
    }
    else
    {
      if (strcmp(bow->bag[pos].word, word) != 0) /* word is new */
      {
        bow->bag_size = bow->bag_size + 1;
        bow->bag = realloc(bow->bag, ((sizeof(struct word_count_struct) )*( bow->bag_size)));

          if (bow->bag_size  > pos+1)
          {

          /*  memcpy(&bow->bag[bow->bag_size-1], wordstruct, sizeof (struct word_count_struct));*/
            memcpy(&bow->bag[pos + 1], &bow->bag[pos], (sizeof (struct word_count_struct))*(bow->bag_size-(pos+1) )); /* copies existing words "right" to make space*/
          }

            memcpy(&bow->bag[pos], wordstruct, sizeof (struct word_count_struct)); /* adds the new word */
        }
        else /* word is duplicate */
        {
          bow->bag[pos].count++;
        }
      }
    }
    bow->total_words++;
    free(wordstruct);
  }
  print_bag(bow);
}

void print_bag ( struct bag_struct *bow)
{
  int i;

  for (i = 0 ; i < bow->bag_size; i++)
  {
    printf("%d ", i);
    print_word_count(&bow->bag[i]);
  }
  printf("Total words: %d\n", bow->total_words);
}  
void free_bag( struct bag_struct *bow)
{
  int i;

  for (i = 0 ; i < bow->bag_size ; i++)
  {
    free(bow->bag[i].word);
  }
  free(bow);
}

void add_text( struct bag_struct *bow, char *line )
{
  char *word;  /* pointer to a word */
  struct word_count_struct *wordstruct;

  while (*line)  /* while sentence doesn't point to the '\0' character at the end of the string */
  {
    word = get_word( &line );  /* this will allocate memory for a word */

    if (word!=NULL) /*not the "last" word */
    {
      wordstruct = new_word_count(word);
      /*printf( "word = \"%s\"; sentence = \"%s\"\n", wordstruct->word, sentence );  /* print out to see what's happening */
    /*  print_word_count(wordstruct);
    */

      add_word(bow, word);

    }
  }
}


void read_sms_data( struct bag_struct *bow, char *label )
{
  FILE *fp;
  char line[924];

  fp = fopen("SMSSpamCollection" , "r");
  while ( !feof( fp ) )
  {
    fgets(line, 924, fp );
    printf("LINE:\n%s\n", line);

    if (strncmp (line, label, strlen(label)) == 0)
    {
      add_text(bow, line+strlen(label));
    }

  }
  fclose(fp);
}

void differences( struct bag_struct *ham, struct bag_struct *spam )
{

}
