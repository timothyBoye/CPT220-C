/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* SP2 2015 Assignment #2 - word link program
* Full Name        : Timothy D Boye
* Student Number   : s3482043
* 
* Start up code provided by the C Teaching Team

****************************************************************************/

#ifndef WORDLINK_OPTIONS_H
#define WORDLINK_OPTIONS_H
#include <ctype.h>

/* Function prototypes. */
void onePlayerGame(DictionaryType* dictionary);
void twoPlayerGame(DictionaryType* dictionary);
void dictionarySummary(DictionaryType* dictionary);
void searchDictionary(DictionaryType* dictionary);
void addDictionaryWord(DictionaryType* dictionary);
int saveDictionary(DictionaryType* dictionary, char* filename);

#endif
