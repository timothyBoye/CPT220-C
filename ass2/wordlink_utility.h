/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* SP2 2015 Assignment #2 - word link program
* Full Name        : Timothy D Boye
* Student Number   : s3482043
* 
* Start up code provided by the C Teaching Team
****************************************************************************/

#ifndef WORDLINK_UTILITY_H
#define WORDLINK_UTILITY_H

/* Function prototypes. */
void readRestOfLine();
void systemInit(DictionaryType* dictionary);
int loadData(DictionaryType* dictionary, char* filename);
void systemFree(DictionaryType* dictionary);
int saveData(DictionaryType* dictionary, char* filename);
WordLinkTypePtr searchviauserinput(DictionaryType* dictionary);

#endif
