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

/******
 * MAIN FUNCTION
 */
int main(int argc, char* argv[])
{
   DictionaryType* dictionary;
   char* filename;

   printf("\n==========\n"
          "Welcome to the Word link game\n"
          "==========\n"
          "Loading dictionary file...\n");

   /* Check a filename was passed */
   if (argc != 2)
   {
      printf("\n!!!!!!!!!!\n"
             "Dictionary file not provided.\n"
             "The program will now exit...\n"
             "!!!!!!!!!!\n\n");
      abort();
   }
   else
   {
      /* filename was passed so system initialise */
      filename = argv[1];
      dictionary = malloc(sizeof(DictionaryType));
      systemInit(dictionary);
   }
   /* Check the system can load the data (and load it) */
   if (loadData(dictionary, filename))
   {
      printf("File successfully loaded, let's play!\n\n");
   }
   else
   {
      /* file not found, free() and abort program */
      printf("\n!!!!!!!!!!\n"
             "Dictionary file does not exist.\n"
             "The program will now exit...\n"
             "!!!!!!!!!!\n\n");
      systemFree(dictionary);
      abort();
   }

   /* Loop the menu until exit called */
   while (menu(dictionary, filename)) {}

   /* Time to exit free() the mem */
   systemFree(dictionary);

   return EXIT_SUCCESS;
}

/*****
 * MENU
 */
int menu(DictionaryType* dictionary, char* filename)
{
   char choice[ALPHABET_LEN] = "";
   int choiceint;
   char* strtolError;

   printf("Main Menu:\n"
          "(1) 1 Player Game\n"
          "(2) 2 Player Game\n"
          "(3) Dictionary Summary\n"
          "(4) Search Dictionary\n"
          "(5) Add Dictionary Word\n"
          "(6) Save Dictionary\n"
          "(7) Exit\n");

   /* ask for a letter and keep asking until the user 
    succumbs to the pressure
    */
   do
   {
      printf("\nSelect your option (1-7): ");
      fgets(choice, 3, stdin);
      if (strchr(choice, '\n') == NULL)
         readRestOfLine();
      choiceint = strtol(choice, &strtolError, 10);
   }
   while (!(*strtolError == '\n' || *strtolError == '\0') ||
         !(choiceint >= 1 && choiceint <= 7)
   );

   switch (choiceint)
   {
      case (1): /* 1 Player Game */
         printf("\n==================================\n"
                "Menu option #1: 1 Player Game\n"
                "==================================\n");
         onePlayerGame(dictionary);
         break;
      case (2): /* 2 Player Game */
         printf("\n==================================\n"
                "Menu option #2: 2 Player Game\n"
                "==================================\n");
         twoPlayerGame(dictionary);
         break;
      case (3): /* Dictionary Summary */
         printf("\n==================================\n"
                "Menu option #3: Dictionary Summary\n"
                "==================================\n");
         dictionarySummary(dictionary);
         break;
      case (4): /* Search Dictionary */
         printf("\n==================================\n"
                "Menu option #4: Search Dictionary\n"
                "==================================\n");
         searchDictionary(dictionary);
         break;
      case (5): /* Add Dictionary Word */
         printf("\n==================================\n"
                "Menu option #5: Add Dictionary Word\n"
                "==================================\n");
         addDictionaryWord(dictionary);
         break;
      case (6): /* Save Dictionary */
         printf("\n==================================\n"
                "Menu option #6: Save Dictionary\n"
                "==================================\n");
         if (!saveDictionary(dictionary, filename))
         {
            printf("Error writing to file");
            systemFree(dictionary);
            abort();
         }
         break;
      case (7): /* Exit */
         printf("\n==================================\n"
                "Menu option #7: Exit\n"
                "==================================\n");
         return 0;
         break;
      /* debuging method, can't be reached unless user
       * input is set to accept values up to 8 */
      case (8):
         displayList(dictionary, 'a');
         break;
   }
   return 1;
}
