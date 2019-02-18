#ifndef BOW_H
#define BOW_H

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

struct word_count_struct {
    char *word;
    int count;
};


struct bag_struct {
    struct word_count_struct *bag;
    int bag_size;
    int total_words;
};

struct bag_struct *new_bag();
int bagsearch( struct bag_struct *bow, char *word );
char *get_word( char **string_ptr );
int is_letter( char character);
struct word_count_struct *new_word_count( char *word );
void free_word_count( struct word_count_struct *word_count );
void print_word_count(struct word_count_struct *word_count);
void add_word( struct bag_struct *bow, char *word );
void print_bag ( struct bag_struct *bow);
void free_bag( struct bag_struct *bow);
void add_text( struct bag_struct *bow, char *line );
void read_sms_data( struct bag_struct *bow, char *label );
void differences( struct bag_struct *ham, struct bag_struct *spam );

#endif
