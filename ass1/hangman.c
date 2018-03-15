/****************************************************************************
* COSC2138/CPT 220 - Programming Principles 2A
* Study Period 2  2015 Assignment #1 - hangman program
* Full Name        : Timothy David Boye
* Student Number   : s3482043
* Course Code      : CPT220
* Start up code provided by the CTeach Team
****************************************************************************/


#include "hangman.h"

/****************************************************************************
* Function main() is the entry point for the program.
****************************************************************************/
int main(void)
{
   char word[MAX_WORD_LEN + 1];
   unsigned wrongGuesses = 0;
   int guessedLetters[ALPHABET_SIZE] = {
      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
   };
   
   /* Pick a random word */
   init(word);
   
   /* display the initial board */
   displayGame(word, guessedLetters, wrongGuesses);
   
   /* play the game */
   while(isGameOver(word, guessedLetters, wrongGuesses) == GAME_CONTINUE)
   {
      if (guessLetter(word, guessedLetters) == BAD_GUESS)
         wrongGuesses++;
      displayGame(word, guessedLetters, wrongGuesses);
   }
   
   /* Game over */
   return EXIT_SUCCESS;
}

/*****
* Function guessedLetter() return true if letter has been guessed
*****/
int guessedLetter(char letter, int* guessedLetters)
{
   int j;
   
   /* go through the guessed letters and check if this letter has
      already been guessed */
   for(j = 0;j < ALPHABET_SIZE;j++)
   {
      if (letter == (char) guessedLetters[j])
         return 1;
   }
   return 0;
}

/*****
* Function displayGame() displays all the various game elements at once
*****/
void displayGame(char* word, int* guessedLetters, unsigned wrongGuesses)
{
   displayWord(word, guessedLetters);
   printf("Number of wrong guesses: %d of %d\n", wrongGuesses, MAX_GUESS);
      displayHangman(wrongGuesses);
}

/****************************************************************************
* Function init() choses a word for the hangman game from the words[] array.
* 
* ASSUMES: srand has already been used to set a seed
****************************************************************************/
void init(char* word)
{
   const char* words[NUM_WORDS] = {
      "array",      "auto",       "break",      "case",       "cast",
      "character",  "comment",    "compiler",   "constant",   "continue",
      "default",    "double",     "dynamic",    "else",       "enum",
      "expression", "extern",     "file",       "float",      "function",
      "goto",       "heap",       "identifier", "library",    "linker",
      "long",       "macro",      "operand",    "operator",   "pointer",
      "prototype",  "recursion",  "register",   "return",     "short",
      "signed",     "sizeof",     "stack",      "statement",  "static",
      "string",     "struct",     "switch",     "typedef",    "union",
      "unsigned",   "variable",   "void",       "volatile",   "while"
   };
   int wordIndex;
   
   /* Initialise the random seed based on the time */
   srand(time(NULL));
    
   /* pick a random word from the table of words */
   wordIndex = rand() % NUM_WORDS;
   strcpy(word, words[wordIndex]);
   
}


/****************************************************************************
* Function displayWord() prints the word to screen with all letters that 
* have not been correctly guessed blanked out with an underscore. 
* Output example:
* +-+-+-+-+-+-+-+-+-+-+
* |i|d|e|n|_|i|_|i|e|r|
* +-+-+-+-+-+-+-+-+-+-+
****************************************************************************/
void displayWord(char* word, int* guessedLetters)
{
   int i;
   
   /* print the fancy border: top */
   for(i = 0;i < strlen(word);i++)
      printf("+-");
   printf("+\n");
   
   /* Print the redacted word 
      Outer loop is each letter of the word
      Inner loop is checking if that letter has been guessed
   */
   for(i = 0;i < strlen(word);i++)
   {
      if (guessedLetter(word[i], guessedLetters) == 1)
         printf("|%c", word[i]);
      else
         printf("|_");
      
   }
   printf("|\n");
   
   /* print the fancy border: bottom */
   for(i = 0;i < strlen(word);i++)
      printf("+-");
   printf("+\n");
   
}


/****************************************************************************
* Function guessLetter() prompts the user to enter one letter. The function
* maintains an array of guessed letters. The function returns GOOD_GUESS
* or BAD_GUESS depending on whether or not the letter is in the word.
****************************************************************************/
int guessLetter(char* word, int* guessedLetters)
{
   int i;
   char guess[MAX_WORD_LEN] = "";
   
   /* ask for a letter and keep asking until the user 
      succumbs to the pressure
     */
   do
   {
      printf("\nPlease enter a single letter: ");
      fgets(guess, MAX_WORD_LEN, stdin);
      if (strchr(guess, '\n') == NULL)
         readRestOfLine();
   } while (strlen(guess) != 2);

   /* normalise guesses to lower case only */ 
   guess[0] = tolower(guess[0]);

   /* check if already guessed */
   if (guessedLetter(guess[0], guessedLetters) == 1)
      return GOOD_GUESS;
   
   /* place new guess in next slot */
   for (i = 0; i < ALPHABET_SIZE; i++)
   {
      if (guessedLetters[i] == 0)
      {
         guessedLetters[i] = (int) guess[0];
         break;
      }
   }
   
   /* check word for the guessed 
      letter and return good or bad 
   */
   for (i = 0;i < strlen(word);i++)
   {
      if (word[i] == guess[0])
      {
         return GOOD_GUESS;
      }
   }
   return BAD_GUESS;
   
   
}


/****************************************************************************
* Function displayHangman() displays an ascii art drawing to complement the
* game. The drawing varies depending on the number of wrong guesses.
* When there are no wrong guesses, an empty drawing is displayed:
* **********
* *        *
* *        *
* *        *
* *        *
* *        *
* *        *
* **********
* When there are 10 wrong guesses (and the game is over), the complete
* drawing is displayed:
* **********
* * +--+   *
* * |  |   *
* * |  O   *
* * | -+-  *
* * | / \  *
* * +----- *
* **********
* You need to display an appropriate drawing depending on the number of 
* wrong guesses:
* - 0 wrong: empty drawing.
* - 1 wrong: include floor.
* - 2 wrong: include vertical beam.
* - 3 wrong: include horizontal beam.
* - 4 wrong: include noose.
* - 5 wrong: include head.
* - 6 wrong: include body.
* - 7 wrong: include left arm.
* - 8 wrong: include right arm.
* - 9 wrong: include left leg.
* - 10 wrong: include right leg (complete drawing).
****************************************************************************/
void displayHangman(unsigned wrongGuesses)
{
   printf("**********\n");
   switch (wrongGuesses)
   {
      case (0):printf("*        *\n"
                     "*        *\n"
                     "*        *\n"
                     "*        *\n"
                     "*        *\n"
                     "*        *\n");
               break;
      case (1):printf("*        *\n"
                     "*        *\n"
                     "*        *\n"
                     "*        *\n"
                     "*        *\n"
                     "* +----- *\n");
               break;
      case (2):printf("*        *\n"
                     "* |      *\n"
                     "* |      *\n"
                     "* |      *\n"
                     "* |      *\n"
                     "* +----- *\n");
               break;
      case (3):printf("* +--+   *\n"
                     "* |      *\n"
                     "* |      *\n"
                     "* |      *\n"
                     "* |      *\n"
                     "* +----- *\n");
               break;
      case (4):printf("* +--+   *\n"
                     "* |  |   *\n"
                     "* |      *\n"
                     "* |      *\n"
                     "* |      *\n"
                     "* +----- *\n");
               break;
      case (5):printf("* +--+   *\n"
                     "* |  |   *\n"
                     "* |  O   *\n"
                     "* |      *\n"
                     "* |      *\n"
                     "* +----- *\n");
               break;
      case (6):printf("* +--+   *\n"
                     "* |  |   *\n"
                     "* |  O   *\n"
                     "* |  +   *\n"
                     "* |      *\n"
                     "* +----- *\n");
               break;
      case (7):printf("* +--+   *\n"
                     "* |  |   *\n"
                     "* |  O   *\n"
                     "* | -+   *\n"
                     "* |      *\n"
                     "* +----- *\n");
               break;
      case (8):printf("* +--+   *\n"
                     "* |  |   *\n"
                     "* |  O   *\n"
                     "* | -+-  *\n"
                     "* |      *\n"
                     "* +----- *\n");
               break;
      case (9):printf("* +--+   *\n"
                     "* |  |   *\n"
                     "* |  O   *\n"
                     "* | -+-  *\n"
                     "* | /    *\n"
                     "* +----- *\n");
               break;
      case (10):printf("* +--+   *\n"
                     "* |  |   *\n"
                     "* |  O   *\n"
                     "* | -+-  *\n"
                     "* | / \\  *\n"
                     "* +----- *\n");
               break;
   }
   printf("**********\n");

}


/****************************************************************************
* Function isGameOver() is the final step in the program. The game is over
* if either all letters in the word have been guessed, or the player has run
* out of guesses. The player is congratulated if he/she wins. The word is
* displayed to the player if he/she loses. This function returns either 
* GAME_OVER or GAME_CONTINUE.
****************************************************************************/
int isGameOver(char* word, int* guessedLetters, unsigned wrongGuesses)
{
   int i;
   
   /* Guessed too many times? */
   if (wrongGuesses == MAX_GUESS)
   {
      printf("Game over. Sorry the word was %s and you didn't guess it.\n", word);
      return GAME_OVER;
   }
   
   /* is the word complete */
   for (i = 0; i < strlen(word); i++)
   {
      if (guessedLetter(word[i], guessedLetters) == 0)
         return GAME_CONTINUE;
   }
   
   /* GOOD JOB you win */
   printf("You Win! The word was %s and you guessed it.\n", word);
   return GAME_OVER;
   
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
