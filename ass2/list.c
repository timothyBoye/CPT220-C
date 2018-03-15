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
 * free ([ the list ]), release the space
 */
void freeList(WordLinkTypePtr list)
{
   WordLinkTypePtr current, next;
   current = list->nextWord;
   /* Step through each word node and free it */
   while (current != NULL)
   {
      next = current->nextWord;
      free(current->word);
      free(current);
      current = next;
   }
   /* blank the "headnode" */
   list->nextWord = NULL;
   list->word = NULL;
   list->usedFlag = FALSE;
}

/*
 * Get the list size (Such OOP wow)
 */
unsigned getListSize(DictionaryType* dic, char letter)
{
   int i = letter - 97;
   return dic->listCounts[i];
}

/*
 * Add a value to the dictionary at the end
 */
int addtodic(DictionaryType* dic, char* source)
{
   int listIndex = (source[0]) - 97; /* Get the index from the char */
   WordLinkTypePtr new, current;

   /* Adding to a list so incrememnt the list lengths */
   dic->listCounts[listIndex]++;
   dic->totalWords++;

   /* Reserve space for the new node */
   if ((new = malloc(sizeof(WordLinkType))) == NULL)
   {
      return FAILURE;
   }

   /* fill in the node */
   new->word = malloc(sizeof(char) * MAX_WORD_LENGTH);
   new->usedFlag = FALSE;
   strcpy(new->word, source);

   /* GOTO end of list (check for preexisting word */
   current = (dic->headWords[listIndex])->nextWord;
   while (current->nextWord != NULL && strcmp(current->word, source) != 0)
   {
      current = current->nextWord;
   }

   /* Check if word exists */
   if (strcmp(current->word, source) == 0)
   {
      printf("Word already exists in dictionary.");
      return FAILURE;
   }

   /*Place the new node in the list*/
   new->nextWord = current->nextWord;
   current->nextWord = new;

   return SUCCESS;
}

/*
 * Add a value to the dictionary at a random location
 */
int addtodicRnd(DictionaryType* dic, char* source)
{
   int listIndex = (source[0]) - 97; /*Convert from char to index*/
   int i, rnd;

   WordLinkTypePtr new, current;

   /*increment the list counters*/
   dic->listCounts[listIndex]++;
   dic->totalWords++;

   /*Get the list*/
   current = (dic->headWords[listIndex]);

   /*Reserve space for the new node*/
   if ((new = malloc(sizeof(WordLinkType))) == NULL)
   {
      return FAILURE;
   }

   /*goto a random location in the list*/
   rnd = rand() % (dic->listCounts[listIndex]);
   for (i = 0; i < rnd; i++)
   {
      current = current->nextWord;
   }

   /*fill in the new node*/
   new->word = malloc(sizeof(char) * MAX_WORD_LENGTH);
   new->usedFlag = FALSE;
   strcpy(new->word, source);
   /*place the new node in the list*/
   new->nextWord = current->nextWord;
   current->nextWord = new;

   return SUCCESS;
}

/*
 * print the list to the console, one node per line
 */
void displayList(DictionaryType* dictionary, char letter)
{
   WordLinkTypePtr current;
   int index = letter - 97;
   current = dictionary->headWords[index]->nextWord;

   while (current != NULL)
   {
      printf("%s\n", current->word);
      current = current->nextWord;
   }
}

/*
 * find a VALUE in the dictionary returns:
 *    NULL not found
 *    location of first matching node
 */
WordLinkTypePtr searchDic(DictionaryType* dic, char* target)
{
   /*call searchlist on the correct list*/
   int listIndex = (target[0]) - 97;
   return searchList((dic->headWords[listIndex]), target);
}

/*
 * find a VALUE in the list returns:
 *    NULL not found
 *    location of first matching node
 */
WordLinkTypePtr searchList(WordLinkTypePtr list, char* target)
{
   WordLinkTypePtr current;
   current = list->nextWord;
   /*Look for the word*/
   while (current != NULL && strcmp(current->word, target) != 0)
   {
      current = current->nextWord;
   }

   return current;
}
