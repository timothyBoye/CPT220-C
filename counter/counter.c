/*
 * counter.c
 * Counts down from 10
 *
 *  Created on: 5 Jun 2015
 *      Author: timothyboye
 */
#include <stdio.h> 
#include <stdlib.h> 
int main(void)
{
   int j;
   j = 10; /* Initialisation of the counter j */
   /* Loops until j==0 as in c 0==false */
   do 
      printf(" %d", j); 
   while (j--);
   printf("\n");
}
