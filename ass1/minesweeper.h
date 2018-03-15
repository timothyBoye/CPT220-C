/****************************************************************************
* COSC2138/CPT 220 - Programming Principles 2A
* Study Period 2  2015 Assignment #1 - minesweeper program
* Full Name        : Timothy David Boye
* Student Number   : s3482043
* Course Code      : CPT220
* Start up code provided by the CTeach Team
****************************************************************************/

/* Header files. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Constants. */
#define MINE_DENSITY 0.16
#define MIN_GRID 2
#define MAX_GRID 16
#define FLAG 'F'
#define MINE 'M'
#define BAD_MINE 'X'
#define UNKNOWN '?'
#define BLANK ' '
#define FLAG_SQUARE 'f'
#define UNCOVER_SQUARE 'u'
#define SWEEP_SQUARE 's'

/* Function prototypes. */
void init(char minefield[MAX_GRID][MAX_GRID], 
          char displayGrid[MAX_GRID][MAX_GRID]);
unsigned getSize();
void placeMines(char minefield[MAX_GRID][MAX_GRID], unsigned size);
void displayMinefield(char displayGrid[MAX_GRID][MAX_GRID], unsigned size);
char guessType();
void guessSquare(char* row, unsigned* col, unsigned size);
int processGuess(char minefield[MAX_GRID][MAX_GRID], 
                 char displayGrid[MAX_GRID][MAX_GRID],
                 unsigned size, char type, char row, unsigned col);
void readRestOfLine();

/*  STUDENT DEFINED FUNCTIONS */
int flag(char displayGrid[MAX_GRID][MAX_GRID],
         char minefield[MAX_GRID][MAX_GRID],
         unsigned row, unsigned col, unsigned size);
int sweep(char minefield[MAX_GRID][MAX_GRID], 
          char displayGrid[MAX_GRID][MAX_GRID],
          unsigned size, unsigned row, unsigned col);
int uncover(char minefield[MAX_GRID][MAX_GRID], 
            char displayGrid[MAX_GRID][MAX_GRID],
            unsigned size, unsigned row, unsigned col);
int numofmines(unsigned size);
void subarray(unsigned* rowstart, unsigned* colstart, 
              unsigned* rowend, unsigned* colend, unsigned size);
void calculateFinalField(char minefield[MAX_GRID][MAX_GRID], 
                         char displayGrid[MAX_GRID][MAX_GRID], 
                         unsigned size);
void uncoverBlanks(char minefield[MAX_GRID][MAX_GRID], 
                   char displayGrid[MAX_GRID][MAX_GRID],
                   unsigned size, unsigned row, unsigned col);
