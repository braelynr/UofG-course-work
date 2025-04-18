
#include <stdlib.h>
#include <stdio.h>


/*#include "bow.h"*/


int mymalloc_ctr = 0;


void *mymalloc( size_t size )
{
  void *ptr;

  ptr = malloc(size );
  printf( "%p [%05d]: +%lu bytes\n", ptr, mymalloc_ctr, size );
  mymalloc_ctr++;

  return ptr;
}

void *myrealloc( void *ptr, size_t size )
{
  void *new_ptr;

  new_ptr = realloc( ptr, size );
  if (ptr!=NULL)
  {
    printf( "%p [%05d]: freed (realloc)\n", ptr, mymalloc_ctr  );
    mymalloc_ctr++;
  }

  printf( "%p [%05d]: +%lu bytes (realloc)\n", new_ptr, mymalloc_ctr, size );
  mymalloc_ctr++;

  return new_ptr;
}


void myfree( void *ptr )
{
  printf( "%p [%05d]: freed\n", ptr, mymalloc_ctr );
  mymalloc_ctr++;

  free( ptr );
}
