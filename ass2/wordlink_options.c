/****************************************************************************
 * COSC2138/CPT220 - Programming Principles 2A
 * SP2 2015 Assignment #2 - word link program
 * Full Name        : Timothy D Boye
 * Student Number   : s3482043
 *
 * Start up code provided by the C Teaching Team

 ****************************************************************************/

#include "wordlink.h"
#include "wordlink_options.h"
#include "wordlink_utility.h"
#include "list.h"
#include "game.h"

/****************************************************************************
 * Menu option #1: 1 Player Game
 * Game between human and computer controlled players.
 *
 * Note: Additional modularisation is strongly recommended here.
 * Extra candidate functions include playerGuess(), resetGame(), etc.
 ****************************************************************************/
void onePlayerGame(DictionaryType* dictionary)
{
   /**************************
    Wait just a minute!

    This is very similar to the two player game...
    POLYMORPHISM B*TCHES!!!
    Converted to one function that takes function pointers to the
    player/computer functions.
    ***************************
    WordLinkTypePtr ptr;
    int i;
    int continueGame = TRUE;
    char previous = 'a';

    printf("\n1 Player Game\n"
    "-------------\n"
    "This game works by the players choosing a word that begins\n"
    "with the letter the previous players word ended with.\n"
    "Let's start with a word beginning with the letter 'a'.\n");
    while(continueGame == TRUE)
    {
    ptr = userguess(dictionary, previous, 1);
    if (ptr == NULL) {
    continueGame = FALSE;
    }
    else
    {
    for(i = 0;ptr->word[i]!='\n' && ptr->word[i]!='\0'; i++)
    {
    previous = ptr->word[i];
    }
    ptr = computerguess(dictionary, previous);
    if (ptr == NULL)
    {
    continueGame = FALSE;
    }
    else
    {
    for(i = 0;ptr->word[i]!='\n' && ptr->word[i]!='\0'; i++)
    {
    previous = ptr->word[i];
    }
    }
    }
    }*/

   /* pass the game controller a player and an ai, let it take care of
    * the game, when it returns reset the game */
   gamecontroller(dictionary, userguess, computerguess);
   resetflags(dictionary);
}

/****************************************************************************
 * Menu option #2: 2 Player Game
 * Game between two human-controlled players.
 *
 * Note: Additional modularisation is strongly recommended here.
 * Extra candidate functions include playerGuess(), resetGame(), etc.
 ****************************************************************************/
void twoPlayerGame(DictionaryType* dictionary)
{
   /* pass the game controller two players, let it take care of
    * the game, when it returns reset the game */
   gamecontroller(dictionary, userguess, userguess);
   resetflags(dictionary);
}

/****************************************************************************
 * Menu option #3: Dictionary Summary
 * Displays statistics on the words in the dictionary.
 ****************************************************************************/
void dictionarySummary(DictionaryType* dictionary)
{
   int i;
   printf("\nDictionary Summary\n"
          "---------------------\n"
          "+---------+---------+\n");
   for (i = 0; i < ALPHABET_LEN / 2; i++)
   {
      printf("| %c:%5d | %c:%5d |\n",
             (i + 65),
             dictionary->listCounts[i],
             (i + 65 + 13),
             dictionary->listCounts[i + 13]);
   }
   printf("+---------+---------+\n\n"
          "Total Words: %d\n\n",
          dictionary->totalWords);
}

/****************************************************************************
 * Menu option #4: Search Dictionary
 * Prompts the user for a dictionary word and reports if the word is in the
 * dictionary.
 ****************************************************************************/
void searchDictionary(DictionaryType* dictionary)
{
   WordLinkTypePtr ptr;

   printf("\nSearch Dictionary"
          "\n-----------------"
          "\nEnter a word (1-%d char): ",
          MAX_WORD_LENGTH);

   /*prompt for user input and find the word*/
   ptr = searchviauserinput(dictionary);

   /*Word found?*/
   if (ptr == NULL)
   {
      printf("The word was NOT in the dictionary.\n\n");
   }
   else
   {
      printf("\"%s\" was found at %p\n\n", ptr->word, (void*) ptr);
   }
}

/****************************************************************************
 * Menu option #5: Add Dictionary Word
 * Prompts the user for a new dictionary word to be added to the data
 * structure.
 ****************************************************************************/
void addDictionaryWord(DictionaryType* dictionary)
{
   char* target = malloc(sizeof(char) * MAX_WORD_LENGTH);
   int i;

   printf("\nAdd word to Dictionary"
          "\n---------------------"
          "\nEnter a word (1-%d char): ",
          MAX_WORD_LENGTH);

   /*Prompt the user for a word and normalise the input*/
   fgets(target, MAX_WORD_LENGTH, stdin);
   if (strchr(target, '\n') == NULL)
      readRestOfLine();
   if (target[strlen(target) - 1] == '\n')
      target[strlen(target) - 1] = '\0';
   for (i = 0; target[i]; i++)
   {
      target[i] = tolower(target[i]);
   }

   /*if it begins with an alpha try adding it*/
   if (target[0] >= 97 && target[0] <= 122)
   {
      /*added*/
      if (addtodic(dictionary, target) == SUCCESS)
      {
         printf("\n\"%s\" added to the dictionary.\n\n", target);
      }
      /*already exists*/
      else
      {
         printf("\n\"%s\" could not be added to the dictionary.\n\n", target);
      }
   }
   /*User can't spell*/
   else
   {
      printf("\"%s\" does not start with an alpha character.\n\n", target);
   }

   free(target);
}

/****************************************************************************
 * Menu option #6: Save Dictionary
 * Writes the contents of the dictionionary back to the original file.
 ****************************************************************************/
int saveDictionary(DictionaryType* dictionary, char* filename)
{
   printf("Save fictionary to file\n"
          "-----------------------\n");
   return saveData(dictionary, filename);
}
