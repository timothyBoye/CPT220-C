/****************************************************************************
 COSC2138/CPT220 - Programming Principles 2A
 * SP2 2015 Assignment #2 - word link program
 * Full Name        : Timothy D Boye
 * Student Number   : s3482043
 *****************************************************************************/

#include "wordlink.h"
#include "wordlink_options.h"
#include "wordlink_utility.h"
#include "list.h"
#include "game.h"

/*
 * Reset flags
 */
void resetflags(DictionaryType* dic)
{
   int i;
   WordLinkTypePtr current;

   /* Go through every list */
   for (i = 0; i < ALPHABET_LEN; i++)
   {
      current = dic->headWords[i];
      /* reset every flag in the list */
      while ((current = current->nextWord) != NULL)
      {
         current->usedFlag = FALSE;
      }
   }
}

/*
 * computer guess in game
 */
WordLinkTypePtr computerguess(DictionaryType* dictionary, char previous, int player)
{
   int index = previous - 97; /* need to subtract 97 to convert from LOWERCASE char */
   WordLinkTypePtr current = dictionary->headWords[index];
   /* Search for word */
   while ((current = current->nextWord) != NULL)
   {
      if (current->usedFlag == FALSE)
      {
         /* Found a word */
         current->usedFlag = TRUE;
         printf("Player 2 selects word “%s”.", current->word);
         return current;
      }
   }
   /* No word found, game over */
   printf("\nPlayer 2 could not make a guess. You win!\n\n");
   return NULL;
}

/*
 * user guess in game
 */
WordLinkTypePtr userguess(DictionaryType* dictionary, char previous, int player)
{
   WordLinkTypePtr ptr;
   /* set the opponent name */
   int opponent;
   if (player == 1)
      opponent = 2;
   else
      opponent = 1;

   /* Get a guess */
   printf("\nPlayer %d: Enter a word (1-%d char, blank line to quit): ",
          player,
          MAX_WORD_LENGTH);
   ptr = searchviauserinput(dictionary);
   if (ptr == NULL)
   {
      printf("\nGuess not found in the dictionary. Player %d wins!\n\n", opponent);
      return NULL;
   }
   else if (ptr->usedFlag == TRUE)
   {
      printf("\nGuess was used before. Player %d wins!\n\n", opponent);
      return NULL;
   }
   else if (ptr->word[0] != previous)
   {
      printf("\nThat word doesn't begin with '%c'. Player %d wins!\n\n",
             previous,
             opponent);
      return NULL;
   }
   /* Good guess return the guess */
   else
   {
      ptr->usedFlag = TRUE;
      return ptr;
   }
}

/*
 * Controlls both single and dual player games using kinda-polymorphism!
 * Takes a function pointer to two "players" (in 1 vs computer the former
 * is the player function and the latter the computer dunction, the controller
 * function doesn't care whether it's a computer of player it just uses the
 * provided function pointers).
 */
void gamecontroller(DictionaryType* dictionary,
               WordLinkTypePtr (*player1)(DictionaryType*, char, int),
               WordLinkTypePtr (*player2)(DictionaryType*, char, int))
{
   WordLinkTypePtr ptr;
   int i;
   int continueGame = TRUE;
   char previous = 'a';

   /* Play the game until told to stop */
   while (continueGame == TRUE)
   {
      /* call the first function (pointer) */
      ptr = player1(dictionary, previous, 1);
      /* Game over? */
      if (ptr == NULL)
      {
         continueGame = FALSE;
      }
      /* Nope set the next letter and call the second fn (pointer) */
      else
      {
         for (i = 0; ptr->word[i] != '\n' && ptr->word[i] != '\0'; i++)
         {
            previous = ptr->word[i];
         }
         ptr = player2(dictionary, previous, 2);
         /* Game over? */
         if (ptr == NULL)
         {
            continueGame = FALSE;
         }
         /* Nope, set the next letter then loop*/
         else
         {
            for (i = 0; ptr->word[i] != '\n' && ptr->word[i] != '\0'; i++)
            {
               previous = ptr->word[i];
            }
         }
      }
   }
}
