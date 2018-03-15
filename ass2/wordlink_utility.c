/****************************************************************************
 COSC2138/CPT220 - Programming Principles 2A
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
 * Function readRestOfLine() is used for buffer clearing. Blackboard source:
 * "Course Documents" > "FAQ" > "Alternative to non-standard fflush(stdin);"
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

/****************************************************************************
 * Initialises the dictionary to a safe empty state.
 ****************************************************************************/
void systemInit(DictionaryType* dictionary)
{
   int i;
   WordLinkTypePtr list;

   /*Reserve space for the lists and blank key data*/
   for (i = 0; i < ALPHABET_LEN; i++)
   {
      list = malloc(sizeof(WordLinkType));
      list->nextWord = NULL;
      list->word = NULL;
      list->usedFlag = FALSE;
      dictionary->headWords[i] = list;
      dictionary->listCounts[i] = 0;
   }

   dictionary->totalWords = 0;
}

/****************************************************************************
 * Loads all data into the dictionary.
 ****************************************************************************/
int loadData(DictionaryType* dictionary, char* filename)
{
   FILE *fp;

   char *line = malloc(sizeof(char) * MAX_WORD_LENGTH);

   printf("Loading file %s into memory\n", filename);

   fp = fopen(filename, "r");

   /*check file existed and was opened successfully*/
   if (fp == NULL)
   {
      return FAILURE;
   }

   /*set random seed to load data in at random*/
   srand(time(NULL));

   /*read each line place in dictionary*/
   while (fgets(line, MAX_WORD_LENGTH, fp) != NULL)
   {
      if (line[strlen(line) - 1] == '\n')
         line[strlen(line) - 1] = '\0';
      addtodicRnd(dictionary, line);
   }

   /*close and free temp variables*/
   fclose(fp);
   free(line);

   return SUCCESS;
}

/****************************************************************************
 * Save all data into the dictionary.
 ****************************************************************************/
int saveData(DictionaryType* dictionary, char* filename)
{
   int i;
   FILE *fp;
   WordLinkTypePtr current;

   printf("Saving file %s into memory\n", filename);

   fp = fopen(filename, "w");

   /*check file existed and was opened successfully*/
   if (fp == NULL)
   {
      return FAILURE;
   }

   /*Go through dictionary and print to file*/
   for (i = 0; i < ALPHABET_LEN; i++)
   {
      current = dictionary->headWords[i];
      while ((current = current->nextWord) != NULL)
      {
         fprintf(fp, "%s\n", current->word);
      }
   }

   fclose(fp);

   printf("Save successful.\n\n");

   return SUCCESS;
}

/****************************************************************************
 * Deallocates memory used in the dictionary.
 ****************************************************************************/
void systemFree(DictionaryType* dictionary)
{
   int i;
   WordLinkTypePtr list;

   /*free the memory that was malloced and blank key data*/
   for (i = 0; i < ALPHABET_LEN; i++)
   {
      list = dictionary->headWords[i];
      freeList(list);
      free(list);
      dictionary->headWords[i] = NULL;
      dictionary->listCounts[i] = 0;
   }

   dictionary->totalWords = 0;
   free(dictionary);
}

/*
 * search via user input
 */
WordLinkTypePtr searchviauserinput(DictionaryType* dictionary)
{
   char* target = malloc(sizeof(char) * MAX_WORD_LENGTH);
   WordLinkTypePtr ptr;
   int i;

   /*get a word from the user and normalise the input*/
   fgets(target, MAX_WORD_LENGTH, stdin);
   if (strchr(target, '\n') == NULL)
      readRestOfLine();
   if (target[strlen(target) - 1] == '\n')
      target[strlen(target) - 1] = '\0';
   for (i = 0; target[i]; i++)
   {
      target[i] = tolower(target[i]);
   }

   /*if it begins with an alpha search the dictionary*/
   if (target[0] >= 97 && target[0] <= 122)
   {
      ptr = searchDic(dictionary, target);
      free(target);
      return ptr;
   }
   else
   {
      free(target);
      return NULL;
   }
}
