/****************************************************************************
* COSC2138/CPT 220 - Programming Principles 2A
* Study Period 2  2015 Assignment #1 - hangman program
* Full Name        : Timothy David Boye
* Student Number   : s3482043
* Course Code      : CPT220
* Start up code provided by the CTeach Team
****************************************************************************/


/* Header files. */
#include <stdio.h>
#include <stdlib.h>
/* Student added header files */
#include <string.h>
#include <time.h>
#include <ctype.h>

/* Constants. */
#define NUM_WORDS 50
#define ALPHABET_SIZE 26
#define GOOD_GUESS 0
#define BAD_GUESS 1
#define GAME_OVER 1
#define GAME_CONTINUE 0
#define MAX_GUESS 10
#define MAX_WORD_LEN 10

/* Function prototypes. */
void init(char* word);
void displayWord(char* word, int* guessedLetters);
int guessLetter(char* word, int* guessedLetters);
void displayHangman(unsigned wrongGuesses);
int isGameOver(char* word, int* guessedLetters, unsigned wrongGuesses);
void readRestOfLine();

/* Student added function prototypes */
void displayGame(char* word, int* guessedLetters, unsigned wrongGuesses);
int guessedLetter(char letter, int* guessedLetters);

