/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* SP2 2015 Assignment #2 - word link program
* Full Name        : Timothy D Boye
* Student Number   : s3482043
* 
* Start up code provided by the C Teaching Team
****************************************************************************/

#ifndef WORDLINK_H
#define WORDLINK_H

/* System-wide header files. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* System-wide constants. */
#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0
#define ALPHABET_LEN 26
#define MAX_WORD_LENGTH 25

/* Structure definitions. */
typedef struct wordLinkStruct* WordLinkTypePtr;

typedef struct wordLinkStruct
{
   char* word;
   unsigned usedFlag;
   WordLinkTypePtr nextWord;
} WordLinkType;

typedef struct dictionaryStruct
{
   WordLinkTypePtr headWords[ALPHABET_LEN];
   unsigned listCounts[ALPHABET_LEN];
   unsigned totalWords;
} DictionaryType;

int menu();

#endif
