/****************************************************************************
 COSC2138/CPT220 - Programming Principles 2A
* SP2 2015 Assignment #2 - word link program
* Full Name        : Timothy D Boye
* Student Number   : s3482043
*****************************************************************************/


#ifndef WORDLINK_LIST_H
#define WORDLINK_LIST_H
#include <time.h>

/* Function prototypes. */

void freeList(WordLinkTypePtr list);
unsigned getListSize(DictionaryType* dic, char letter);
int addtodic(DictionaryType* dic, char* source);
void displayList(DictionaryType* dictionary, char letter);
WordLinkTypePtr searchDic(DictionaryType* dic, char* target);
WordLinkTypePtr searchList(WordLinkTypePtr list, char* target);
int addtodicRnd(DictionaryType* dic, char* source);

#endif
