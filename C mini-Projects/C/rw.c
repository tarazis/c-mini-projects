/*
This program simulates  a cross walk in a 10X10 array. The program shows the 10X10 array as a matrix of dots. It then
randomly selects a dot and fills it with a letter ordered alphabitically. Once it randomly selects a dot (position) it then
moves one step in any 4 directions (right, left, top, bottom). The program repeats itself until it is fully trapped and cannot
go anywhere.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLUMNS 10 // # OF COLUMNS
#define ROWS 10 // # OF ROWS

int main(void)
{
   int column, row = 0;
   int direction, i, j;
   int blockedNum = 0;

   char path[ROWS][COLUMNS];
   char blocked;

   _Bool isBlocked = false;

   // for loop creates a [10][10] matrix that has '.' filled out
   for (i = 0; i < ROWS; i++) {
      for (j = 0; j < COLUMNS; j++) {
         path[i][j] = '.';
      }
   }
   srand((unsigned) time(NULL));

   path[0][0] = 'A';  // fill in A in the first upper left dot 

   // Whenever a step is taken, fill in an alphabet by order
   for (i = 'B'; i <= 'Z'; i++) {
      direction = ((rand() % ROWS) % 4); // direction up, down, right, or left randomly

      switch(direction) { // switch 0: north, 1: south, 2: east, 3: west
         case 0: // north
            if ((row - 1  >= 0) && (path[row - 1][column] == '.')) { // can go north
               path[--row][column] = i;
               break;
            } else {
               blockedNum++; // else, north is blocked
            }

            if ((row + 1 <= 9) && (path[row + 1][column] == '.')) { //can go south
               path[++row][column] = i;
               break;
            } else { // else south is blocked
               blockedNum++;
            }

            if ((column + 1 <= 9) && (path[row][column + 1] == '.')) { // can go east
               path[row][++column] = i;
               break;
            } else { // else east is blocked
               blockedNum++;
            }

            if ((column - 1 >= 0) && (path[row][column - 1] == '.')) { // can go west
               path[row][--column] = i;
               break;
            } else {
               blockedNum++; // else west is blocked
            }

            break;

         case 1: // South is the direction
            if ((row + 1 <= 9) && (path[row + 1][column] == '.')) { //can go south
               path[++row][column] = i;
               break;
            } else {
               blockedNum++;
            }

            if ((row - 1  >= 0) && (path[row - 1][column] == '.')) { //can go north
               path[--row][column] = i;
               break;
            } else {
               blockedNum++;
            }

            if ((column + 1 <= 9) && (path[row][column + 1] == '.')) { //can go east
               path[row][++column] = i;
               break;
            } else {
               blockedNum++;
            }

            if ((column - 1 >= 0) && (path[row][column - 1] == '.')) { //can go west
               path[row][--column] = i;
               break;
            } else {
               blockedNum++;
            }

            break;

         case 2: // East is the direction
            if ((column + 1 <= 9) && (path[row][column + 1] == '.')) { //can go east
               path[row][++column] = i;
               break;
            } else {
               blockedNum++;
            }

            if ((column - 1 >= 0) && (path[row][column - 1] == '.')) { //can go west
               path[row][--column] = i;
               break;
            } else {
               blockedNum++;
            }

            if ((row - 1  >= 0) && (path[row - 1][column] == '.')) {// can go north
               path[--row][column] = i;
               break;
            } else {
               blockedNum++;
            }

            if ((row + 1 <= 9) && (path[row + 1][column] == '.')) { // can go south
               path[++row][column] = i;
               break;
            } else {
               blockedNum++;
            }

            break;

         case 3: // West is the direction
            if ((column - 1 >= 0) && (path[row][column - 1] == '.')) { // can go west
               path[row][--column] = i;
               break;
            } else {
               blockedNum++;
            }

            if ((column + 1 <= 9) && (path[row][column + 1] == '.')) { // can go east
               path[row][++column] = i;
               break;
            } else {
               blockedNum++;
            }

            if ((row - 1  >= 0) && (path[row - 1][column] == '.')) { // can go north
               path[--row][column] = i;
               break;
            } else {
               blockedNum++;
            }

            if ((row + 1 <= 9) && (path[row + 1][column] == '.')) { // can go south
               path[++row][column] = i;
               break;
            } else {
               blockedNum++;
            }

            break;

      }

      if (blockedNum == 4) { // if direction is blocked from all 4 sides
         blocked = --i;
         isBlocked = true;

         break;
      }

      blockedNum = 0;         // letter found a home. Clear the counter for next letter.

   }

   // provide the final path (matrix)
   printf("\n");

   for (i = 0; i < ROWS; i++) {
      for (j = 0; j < COLUMNS; j++) {
         printf("%c ", path[i][j]);
      }
      printf("\n");
   }

   return 0;
}
