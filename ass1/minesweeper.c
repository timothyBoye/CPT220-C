/****************************************************************************
* COSC2138/CPT 220 - Programming Principles 2A
* Study Period 2  2015 Assignment #1 - minesweeper program
* Full Name        : Timothy David Boye
* Student Number   : s3482043
* Course Code      : CPT220
* Start up code provided by the CTeach Team
****************************************************************************/

#include "minesweeper.h"

/****************************************************************************
* Function main() is the entry point for the program.
****************************************************************************/
int main(void)
{
   /* Stores all hidden data about the minefield. */
   char minefield[MAX_GRID][MAX_GRID];
   /* A version of the minefield that only stores known information. */
   char displayGrid[MAX_GRID][MAX_GRID];
   /* Number of cells in each row and column used. */
   unsigned size = 0;
   /* user choice selections */
   char type;
   char *row = malloc(sizeof(char));
   unsigned *col = malloc(sizeof(int));
   
   /* create the game arrays */
   init(minefield, displayGrid);
   /* get the size of the game from the user */
   size = getSize();
   /* place the requisite number of mines on the field */
   placeMines(minefield, size);
   /*debug*/
   /* displayMinefield(minefield, size); */
   
   /* Start the game proper, loop until game ending condition */
   do
   {
      /* display game, ask what the user whats to do, ask where */
      displayMinefield(displayGrid, size);
      type = guessType();
      guessSquare(row, col, size);
      
   /* check game state and edit the board */
   } while(processGuess(minefield, displayGrid, size, type, *row, *col)
          == 1);
   
   /* GAME OVER */
   calculateFinalField(minefield, displayGrid, size);
   displayMinefield(displayGrid, size);
   return EXIT_SUCCESS;
}

/*************
 * numofmines() get the number of mines the board SHOULD have
 *************/
int numofmines(unsigned size)
{
   /* Calculate num of mines (add one if there are decimal places)*/
   int numofmines = (size*size)*MINE_DENSITY;
   if ((MINE_DENSITY*(size*size)) > (float)numofmines)
      numofmines++;
   
   return numofmines;
}

/****************************************************************************
* Function init() initialises the "minefield" array with BLANK characters,
* and the "displayGrid" array with UNKNOWN characters. These constants (and
* others) are obtained from the header file.
****************************************************************************/
void init(char minefield[MAX_GRID][MAX_GRID], 
          char displayGrid[MAX_GRID][MAX_GRID])
{
   /* Self explanatory, loops through the arrays, makes all default chars */
   int i, j;
   for (i = 0; i < MAX_GRID; i++)
   {
      for (j = 0; j < MAX_GRID; j++)
      {
         minefield[i][j] = BLANK;
         displayGrid[i][j] = UNKNOWN;
      }
   }
}


/****************************************************************************
* Function getSize() prompts the user for the size of the minefield in the
* range MIN_GRID to MAX_GRID. Example:
* ------------------------------------------------------
* Enter minefield size (2-16): 6
* You have chosen a minefield with 6 rows and 6 columns.
* ------------------------------------------------------
****************************************************************************/
unsigned getSize()
{
   int num;
   char str[10] = "";
   char* strtolError;
   
   /* ask for a number and keep asking until the user 
      succumbs to the pressure
     */
   do
   {
      printf("\n------------------------------------------"
             "\nEnter minefield size (2-16): ");
      /* Get input */
      fgets(str, 10, stdin);
      /* check for new line and clear cache if need be */
      if (strchr(str, '\n') == NULL)
         readRestOfLine();
      /* Convert to number */
      num = strtol(str, &strtolError, 10);
      
   /* validate */
   } while (str[0] == '\n' ||
          num < 2 ||
          num > 16 ||
          !(*strtolError == '\n' || *strtolError == '\0' ));
   printf("\nYou have chosen a minefield with %d rows and %d columns."
          "\n------------------------------------------\n\n", num, num);

   return (unsigned)num;
}


/****************************************************************************
* Function placeMines() places a number of mines in the minefield. The 
* number of mines placed is equal to the number of squares in the minefield
* multiplied by the MINE_DENSITY constant.
* For example, a grid with size 6 has 36 squares.
* 36 x 0.16 = 5.76 or approximately 6 mines. (Result is always rounded up.)
* The mines are placed at random positions and each mine must be in a 
* different square. Use the MINE constant to mark mine squares. Use numbers
* from 1-8 to mark other squares that have that number of mines adjacent to
* them. Squares that don't have adjacent mines are marked as BLANK.
* Here's an example:
* ---------------------------
*     1   2   3   4   5   6
*   +---+---+---+---+---+---+ [ EXAMPLE 1]
* a | M | M | 1 |   |   |   |
*   +---+---+---+---+---+---+
* b | 2 | 2 | 1 |   |   |   |
*   +---+---+---+---+---+---+
* c |   |   | 1 | 1 | 1 |   |
*   +---+---+---+---+---+---+
* d |   |   | 2 | M | 2 |   |
*   +---+---+---+---+---+---+
* e |   |   | 3 | M | 4 | 1 |
*   +---+---+---+---+---+---+
* f |   |   | 2 | M | M | 1 |
*   +---+---+---+---+---+---+
* ---------------------------
****************************************************************************/
void placeMines(char minefield[MAX_GRID][MAX_GRID], unsigned size)
{
   /* loop variables */
   int i, j, a, b, tryagain;
   unsigned* rowstart = malloc(sizeof(int));
   unsigned* colstart = malloc(sizeof(int));
   unsigned* rowend = malloc(sizeof(int));
   unsigned* colend = malloc(sizeof(int));
   /* mine position variables */
   int x, y;
   /* counting variable for no of mines around a point */
   int count;
   
   /* Calculate num of mines */
   int mines = numofmines(size);
   
   /* seed the random gen */
   srand(time(NULL));
    
    /* for each mine randomly choose a coord 
       check it is empty than place the mine
       or find a new coord if it isn't empty
       */
   for (i = 0; i < mines; i++)
   {
      do
      {
         x = rand() % size;
         y = rand() % size;
         if (minefield[x][y] == MINE)
         {
            tryagain = 0;
         }
         else
         {
            minefield[x][y] = MINE;
            tryagain = 1;
         }
      } while (tryagain != 1);
   }   
   
   /* for each position in the array that is blank
      count the number of mines around it and place
      that number in that blank position 
      */
   for (i = 0;i < size;i++)
   {
      for(j = 0;j < size;j++)
      {
         /* If the current pos is blank count all
            the mines in the 3x3 area around it and
            place that number in this position */
         if (minefield[i][j] == BLANK)
         {
            count = 0;
            /* The sub array we're checking would be positions
            i and j -1 through to i and j +1 */
            *rowstart = i;
            *colstart = j;
            subarray(rowstart, colstart, rowend, colend, size);
            
            for(a = *rowstart;a <= *rowend;a++)
            {
               for(b = *colstart;b <= *colend;b++)
               {
                  if (minefield[a][b] == MINE)
                     count++;
               }
            }
            if (count > 0)
               minefield[i][j] = count + '0';
         }
      }
   }
   
}



/****************************************************************************
* Function displayMinefield() shows the user an ascii-art drawing of the
* minefield with only known information displayed. Initially, nothing is
* known about the minefield, so all squares are hidden. Example:
* ---------------------------
*     1   2   3   4   5   6
*   +---+---+---+---+---+---+ [ EXAMPLE 2]
* a | ? | ? | ? | ? | ? | ? |
*   +---+---+---+---+---+---+
* b | ? | ? | ? | ? | ? | ? |
*   +---+---+---+---+---+---+
* c | ? | ? | ? | ? | ? | ? |
*   +---+---+---+---+---+---+
* d | ? | ? | ? | ? | ? | ? |
*   +---+---+---+---+---+---+
* e | ? | ? | ? | ? | ? | ? |
*   +---+---+---+---+---+---+
* f | ? | ? | ? | ? | ? | ? |
*   +---+---+---+---+---+---+
* You have flagged 0/6 mines.
* ---------------------------
****************************************************************************/
void displayMinefield(char displayGrid[MAX_GRID][MAX_GRID], unsigned size)
{
   int i,j;
   int flagged = 0;
   
   printf("------------------------------------------\n ");
   
   /* create the header line of the grid */
   for(i = 1; i <= size; i++)
   {
      if (i < 10)
         printf("   %d", i);
      else
         printf("  %d", i);
   }
   printf("\n");
   
   /* Fancy top border, side letters and the grid itself */
   for(i = 0; i < size; i++)
   {
      /* fancy border tops */
      printf("  +");
      for(j = 0; j < size; j++)
         printf("---+");
      printf("\n");
      /* Grid reference letter */
      printf("%c |", ('a'+i));
      /* actual grid cells */
      for(j = 0; j < size; j++)
      {
         printf(" %c |", displayGrid[i][j]);
         if (displayGrid[i][j] == FLAG)
            flagged++;
      }
      printf("\n");
   }
   
   /* fancy border bottom */
   printf("  +");
   for(j = 0; j < size; j++)
      printf("---+");
   printf("\n");
   
   printf("You have flagged %d/%d mines.\n", flagged, numofmines(size));
   printf("------------------------------------------\n");
}


/****************************************************************************
* Function guessType() prompts the user for a single character representing
* one of three options. These options are used in the processGuess() 
* function. Example:
* --------------------------------------------------
* Enter guess type ((f)lag, (u)ncover or (s)weep): u
* You have selected "uncover".
* --------------------------------------------------
****************************************************************************/
char guessType()
{
   char type;
   char str[10];
   
   /* Ask the user what type of move they'd like to make and keeps
   asking until the user succumbs */
   do
   {
      printf("\n------------------------------------------\n"
             "Enter guess type ((f)lag, (u)ncover or (s)weep): ");
      /* Read input */
      fgets(str, 10, stdin);
      /* check for end of line and purge */
      if (strchr(str, '\n') == NULL)
         readRestOfLine();
      /* set move type */
      type = str[0];
   /* check is a valid input/move type */
   } while (str[0] == '\n'   ||
          strlen(str) != 2 || 
          (type != FLAG_SQUARE    &&
           type != UNCOVER_SQUARE &&
           type != SWEEP_SQUARE)
            );
   
   /* Tell the user what they chose because end users are silly */
   printf("\nYou have selected \"");
   switch(type)
   {
      case FLAG_SQUARE: printf("flag");
              break;
      case UNCOVER_SQUARE: printf("uncover");
              break;
      case SWEEP_SQUARE: printf("sweep");
              break;
   }
   printf("\".\n"
          "------------------------------------------\n");
   
   /* return the move type */
   return type;
}


/****************************************************************************
* Function guessSquare() prompts the user for the reference of a square 
* in the minefield. The row and column components are extracted and made
* available to the calling function separately. Example:
* ------------------------------------------
* Enter square (a1-f6): f1
* Your have selected row "f" and column "1".
* ------------------------------------------
****************************************************************************/
void guessSquare(char* row, unsigned* col, unsigned size)
{
   char str[10];
   char* strtolError;
   char sizechar = size + 96;
   
   /* Ask the user what square they'd like to make a move on 
   and keep asking until the user succumbs */
   do
   {
      printf("\n------------------------------------------\n"
             "Enter square (a1-%c%d): ", sizechar, size);
      /* get input */
      fgets(str, 10, stdin);
      /* check for end of line and purge */
      if (strchr(str, '\n') == NULL)
         readRestOfLine();
      /* set the row choice */
      *row = str[0];
      /* '0' the row so it isn't in the way */
      str[0] = '0';
      /* set the col number */
      *col = (unsigned)strtol(str, &strtolError, 10);
   /* Check the input was valid */
   } while (str[0] == '\n'       ||
          *col > size            || *col < 1   || 
          *row > sizechar        || *row < 'a' ||
          !(*strtolError == '\n' || *strtolError == '\0' ));
   printf("\nYour have selected row \"%c\" and column \"%d\".", *row, *col);
   printf("\n------------------------------------------\n");
}

/****************************************************************************
* Function processGuess() manipulates the displayGrid variable and determines
* if the Minesweeper game is over or not. It processes the three types of
* actions called "(f)lag square", "(u)ncover square", and "(s)weep square".
* Examples:
*
* Consider the following minefield ("minefield" variable):
* ---------------------------
*     1   2   3   4   5   6
*   +---+---+---+---+---+---+ [ EXAMPLE 3]
* a | M | M | 1 |   |   |   |
*   +---+---+---+---+---+---+
* b | 2 | 2 | 1 |   |   |   |
*   +---+---+---+---+---+---+
* c |   |   | 1 | 1 | 1 |   |
*   +---+---+---+---+---+---+
* d |   |   | 2 | M | 2 |   |
*   +---+---+---+---+---+---+
* e |   |   | 3 | M | 4 | 1 |
*   +---+---+---+---+---+---+
* f |   |   | 2 | M | M | 1 |
*   +---+---+---+---+---+---+
* ---------------------------
* Initially, the minefield is entirely hidden ("displayGrid" variable):
* ---------------------------
*     1   2   3   4   5   6
*   +---+---+---+---+---+---+ [ EXAMPLE 4]
* a | ? | ? | ? | ? | ? | ? |
*   +---+---+---+---+---+---+
* b | ? | ? | ? | ? | ? | ? |
*   +---+---+---+---+---+---+
* c | ? | ? | ? | ? | ? | ? |
*   +---+---+---+---+---+---+
* d | ? | ? | ? | ? | ? | ? |
*   +---+---+---+---+---+---+
* e | ? | ? | ? | ? | ? | ? |
*   +---+---+---+---+---+---+
* f | ? | ? | ? | ? | ? | ? |
*   +---+---+---+---+---+---+
* ---------------------------
* If the user decides to "uncover square f1", the following can happen:
* - If a mine is accidentally uncovered, the game is lost.
* - If a numbered square is uncovered, this is marked in the "displayGrid"
*   variable.
* - If a blank square is uncovered, this is marked in the "displayGrid" 
*   variable and all adjacent blank squares above, below, left, or right
*   are also marked.
* In this example, square f1 is blank, so the "displayGrid" variable is
* updated to look like this:
* ---------------------------
*     1   2   3   4   5   6
*   +---+---+---+---+---+---+ [ EXAMPLE 5]
* a | ? | ? | ? | ? | ? | ? |
*   +---+---+---+---+---+---+
* b | 2 | 2 | 1 | ? | ? | ? |
*   +---+---+---+---+---+---+
* c |   |   | 1 | ? | ? | ? |
*   +---+---+---+---+---+---+
* d |   |   | 2 | ? | ? | ? |
*   +---+---+---+---+---+---+
* e |   |   | 3 | ? | ? | ? |
*   +---+---+---+---+---+---+
* f |   |   | 2 | ? | ? | ? |
*   +---+---+---+---+---+---+
* ---------------------------
* From the above information, the user can already deduce where five of the
* six mines are located. They are in squares a1, a2, d4, e4, and f4. So, the
* user would next want to "flag square a1" and the other four squares. 
* The user can only flag squares on unknown squares. So, our "displayGrid"
* variable now looks like this:
* ---------------------------
*     1   2   3   4   5   6
*   +---+---+---+---+---+---+ [ EXAMPLE 6]
* a | F | F | ? | ? | ? | ? |
*   +---+---+---+---+---+---+
* b | 2 | 2 | 1 | ? | ? | ? |
*   +---+---+---+---+---+---+
* c |   |   | 1 | ? | ? | ? |
*   +---+---+---+---+---+---+
* d |   |   | 2 | F | ? | ? |
*   +---+---+---+---+---+---+
* e |   |   | 3 | F | ? | ? |
*   +---+---+---+---+---+---+
* f |   |   | 2 | F | ? | ? |
*   +---+---+---+---+---+---+
* ---------------------------
* The user can now deduce that there are no mines in squares a3, a4, b4, and
* c4. The user can now uncover these squares one at a time if he or she
* wishes. However, this is somewhat inefficient. Alternatively, the user may
* want to "sweep" around a numbered square that is considered safe because 
* the adjacent mines have been (hopefully) correctly flagged.
* So the user can "sweep square b3". This effectively executes the "uncover"
* command on the surrounding 8 squares (but only the ones that are marked as
* UNKNOWN). After performing the "sweep square b3" command, the "displayGrid"
* variable looks like this:
* ---------------------------
*     1   2   3   4   5   6
*   +---+---+---+---+---+---+ [ EXAMPLE 7]
* a | F | F | 1 |   |   |   |
*   +---+---+---+---+---+---+
* b | 2 | 2 | 1 |   |   |   |
*   +---+---+---+---+---+---+
* c |   |   | 1 | 1 | 1 |   |
*   +---+---+---+---+---+---+
* d |   |   | 2 | F | 2 |   |
*   +---+---+---+---+---+---+
* e |   |   | 3 | F | 4 | 1 |
*   +---+---+---+---+---+---+
* f |   |   | 2 | F | ? | ? |
*   +---+---+---+---+---+---+
* ---------------------------
* The user will need to guess whether the final mine is in square f5 or f6
* and flag the square. When six squares are flagged, the user guesses are 
* verified. If any guess is incorrect, then the user loses and the game is
* over. Otherwise the user wins the game and the game is over. The 
* displayMinefield() function is called one last time with bad guesses marked
* as BAD_MINE.
*
* This function is a large one, and it is recommended that you further
* modularise it. Leave this one until you have implemented the other six
* major functions. Additionally, you should implement the three commands in
* this order: flag, uncover, sweep.
****************************************************************************/
int processGuess(char minefield[MAX_GRID][MAX_GRID], 
                 char displayGrid[MAX_GRID][MAX_GRID],
                 unsigned size, char type, char row, unsigned col)
{
   /* get the row number back (letters are useless for indexes) */
   unsigned rownum = row-'a';
   /* get the col index from 0 */
   unsigned colnum = col-1;
   /* stores win/lose/keep playing state */
   int gamestate;
   
   /* Switch on the move chosen by the player */
   switch(type)
   {
      case FLAG_SQUARE:    gamestate = 
                           flag(displayGrid, minefield, rownum, colnum, size);
                           break;
      case UNCOVER_SQUARE: gamestate = 
                           uncover(minefield, displayGrid, size, rownum, colnum);
                           break;
      case SWEEP_SQUARE:   gamestate = 
                           sweep(minefield, displayGrid, size, rownum, colnum);
                           break;
   }
   
   /* return the gamestate */
   return gamestate;
}

/*************
 * flag() handles the functionality where the user wants
 to flag a particular square
 *************/
int flag(char displayGrid[MAX_GRID][MAX_GRID],
         char minefield[MAX_GRID][MAX_GRID],
         unsigned row, unsigned col, unsigned size)
{
   int i,j;
   int flags = 0;
   int flagsCorrect = 0;
   
   /* Flag the square if the square is unknown
   this is not arbitrary it doesn't just prevent
   bothering to reflag a flagged square it also
   prevents flagging any uncovered square like blanks
   or numbered squares */
   if (displayGrid[row][col] == UNKNOWN)
      displayGrid[row][col] = FLAG;
      
   /* Count the number of flags the user has placed
   and the number that are right (there is a mine under them)*/
   for (i = 0; i<size ;i++)
   {
      for (j = 0; j<size ;j++)
      {
         if (displayGrid[i][j] == FLAG)
         {
            flags++;
            if (minefield[i][j] == MINE)
            {
               flagsCorrect++;
            }
         }
      }
   }
   /* if the number of flags is equal to the number of mines
   the game is over, check if the user was right or wrong */
   if (flags == numofmines(size))
   {
      if (flags == flagsCorrect)
      {
         printf("CONGRATULATIONS, you found all the mines.\n");
         return 0;
      }
      else
      {
         printf("OH NO! Some of your flags were wrong, game over\n");
         return -1;
      }
   }
   
   /* Game still continuing */         
   return 1;
}

/*************
 * sweep() handles the functionality where the user wants
 to sweep around a particular square
 *************/
int sweep(char minefield[MAX_GRID][MAX_GRID], 
          char displayGrid[MAX_GRID][MAX_GRID],
          unsigned size, unsigned row, unsigned col)
{
   int i,j;
   int gamestate = 1;
   /* Reserve space for some pointers we'll 
   use later for a subarray() call*/
   unsigned* rowstart = malloc(sizeof(int));
   unsigned* colstart = malloc(sizeof(int));
   unsigned* rowend = malloc(sizeof(int));
   unsigned* colend = malloc(sizeof(int));
   
   /* Get array coords for a 3x3 around the chosen position */
   *colstart = col;
   *rowstart = row;
   subarray(rowstart, colstart, rowend, colend, size);
   
   /* Step through the returned array and call uncover on 
   each in turn, if any square's uncovering returns a game 
   end state return immediately as the game is over and the 
   next uncover will write over that info */
   for (i = *rowstart; i <= *rowend;i++)
   {
      for (j = *colstart; j <= *colend;j++)
      {
         if (displayGrid[i][j] == UNKNOWN)
            gamestate = uncover(minefield, displayGrid, size, i, j);
         if (gamestate < 1)
            return gamestate;
      }
   }
   
   return gamestate;
}

/*************
 * uncover() handles the functionality where the user wants
 to uncover a particular square
 *************/
int uncover(char minefield[MAX_GRID][MAX_GRID], 
            char displayGrid[MAX_GRID][MAX_GRID],
            unsigned size, unsigned row, unsigned col)
{
   /* Step through all the possible square types and uncover 
   the square */
   /* The square was previously flagged, unflag it */
   if (displayGrid[row][col] == FLAG)
   {
      printf("This square was flagged, it will now be unflagged\n");
      displayGrid[row][col] = UNKNOWN;
      return 1;
   }
   /* If the square isn't unknown it must have already been uncovered */
   if (displayGrid[row][col] != UNKNOWN)
   {
      printf("This square has already been uncovered\n");
      return 1;
   }
   /* if the square underneath is a number uncover it */
   else if (minefield[row][col] > '0' && minefield[row][col] < '9')
   {
      displayGrid[row][col] = minefield[row][col];
      return 1;
   }
   /* if the square underneath is a mine GAME OVER */
   else if (minefield[row][col] == MINE)
   {
      printf("OH NO! That was a mine, game over.\n");
      displayGrid[row][col] = BAD_MINE;
      return -1;
   }
   /* Square must be a blank, uncover all the blanks connected to it */
   else
   {
      uncoverBlanks(minefield, displayGrid, size, row, col);
      return 1;
   }
}


/*************
 * uncoverBlanks() is a recursive function that uncovers all the connected 
 * non mine squares to the coord given (stopping where it hits numbered 
 * squares).
 *************/
void uncoverBlanks(char minefield[MAX_GRID][MAX_GRID], 
                   char displayGrid[MAX_GRID][MAX_GRID],
                   unsigned size, unsigned row, unsigned col)
{
   int i,j;
   /* reserve space for the subarray pointers */
   unsigned* rowstart = malloc(sizeof(int));
   unsigned* colstart = malloc(sizeof(int));
   unsigned* rowend = malloc(sizeof(int));
   unsigned* colend = malloc(sizeof(int));

   /* get a subarray of the 3x3 around this position */
   *colstart = col;
   *rowstart = row;
   subarray(rowstart, colstart, rowend, colend, size);
      
   /* Step through this "new" array copying what's in the minefield
   to the displayfield, if each square in turn is also blank  call
   uncoverblanks() on that square as well (RECURSION!!!)*/
   for (i = *rowstart; i <= *rowend;i++)
   {
      for (j = *colstart; j <= *colend;j++)
      {
         /* if this square hasn't been uncovered and is blank 
         call uncover and make blank */
         if (displayGrid[i][j] != BLANK && minefield[i][j] == BLANK)
         {
            displayGrid[i][j] = BLANK;
            uncoverBlanks(minefield, displayGrid, size, i, j);
         }
         /* if the square is a numbered square uncover it */
         if (minefield[i][j] > '0' && minefield[i][j] < '9')
         {
            displayGrid[i][j] = minefield[i][j];
         }
      }
   }
}

/*************
 * subarray() takes pointer including a starting coord and 
 * and changes where they point to "create" a three by three
 * array around the inputed starting point (but also checks 
 * the game board boundaries to ensure we don't do array[-1])
 *************/
void subarray(unsigned* rowstart, unsigned* colstart, 
              unsigned* rowend, unsigned* colend, unsigned size)
{
   /* set the end coords to one more than the middle coord */
   *rowend = *rowstart+1;
   *colend = *colstart+1;
   
   /* if we're not at the edge move the start coords one back */
   if (*rowstart != 0)
      *rowstart = *rowstart - 1;
   if (*colstart != 0)
      *colstart = *colstart - 1;
   
   /* If the end coords are past the end of the game move them back one */
   if (*rowend >= size)
      *rowend = *rowend - 1;
   if (*colend >= size)
      *colend = *colend - 1;
}

/*************
 * calculateFinalField() compares the minefield and the display field
 * and uncovers all the unknowns on the display to show the final game board
 *************/
void calculateFinalField(char minefield[MAX_GRID][MAX_GRID], 
                         char displayGrid[MAX_GRID][MAX_GRID], 
                         unsigned size)
{
   int i,j;
   
   /* Step through the grid and uncover any unknowns and 
   change any wrongly placed flags to bad mines */
   for (i = 0; i<size ;i++)
   {
      for (j = 0; j<size ;j++)
      {
         if (displayGrid[i][j] == UNKNOWN)
            displayGrid[i][j] = minefield[i][j];
         else if (displayGrid[i][j] == FLAG && minefield[i][j] != MINE)
            displayGrid[i][j] = BAD_MINE;
      }
   }
}

/****************************************************************************
* Function readRestOfLine() is used for buffer clearing. Source: 
* https://inside.cs.rmit.edu.au/~sdb/teaching/C-Prog/CourseDocuments/
* FrequentlyAskedQuestions/
****************************************************************************/
void readRestOfLine()
{
   int c;

   /* Read until the end of the line or end-of-file. */   
   while ((c = fgetc(stdin)) != '\n' && c != EOF)
      ;

   /* Clear the error and end-of-file flags. */
   clearerr(stdin);
}
