/****************************************************************************
 COSC2138/CPT220 - Programming Principles 2A
 * SP2 2015 Assignment #2 - word link program
 * Full Name        : Timothy D Boye
 * Student Number   : s3482043
 *****************************************************************************/

#ifndef WORDLINK_GAME
#define WORDLINK_GAME

void
resetflags(DictionaryType* dic);
WordLinkTypePtr computerguess(DictionaryType* dictionary, char previous, int player);
WordLinkTypePtr userguess(DictionaryType* dictionary, char previous, int player);
void gamecontroller(DictionaryType* dictionary,
               WordLinkTypePtr (*player1)(DictionaryType*, char, int),
               WordLinkTypePtr (*player2)(DictionaryType*, char, int));

#endif
