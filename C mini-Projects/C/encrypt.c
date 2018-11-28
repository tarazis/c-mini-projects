//
// EECS2031 encrypt.c
//
// This is a program for creating a an encryption program programmed in C.
//
//
// Author: Sami Tarazi
// Student Info: 214487847
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  FILE *file_in, *file_out;
  char *fileName, fileName_enc[FILENAME_MAX];
  int i, shift;

  if (argc != 3) // check if correct number of arguments
  {
    printf("Invalid input\n");
    exit(1);
  }

  if (atoi(argv[2]) < 1 || atoi(argv[2]) > 25) // if user enters wrong shiftr amound, display error
  {
    printf("Invalid shift amount.\n");
    exit(1);
  }

  fileName = argv[1]; // argument 1 = fileName
  shift = atoi(argv[2]); // argument 2 = shift amound

  if ((file_in = fopen(fileName, "r")) == NULL)
  {
    printf("Cannot open file\n");
    exit(1);
  }

  strcpy(fileName_enc, fileName); // assign file name
  strcat(fileName_enc, ".enc"); // assign extension

 if ((file_out = fopen(fileName_enc, "w")) == NULL) // make sure output file can be opened.
  {
    printf("Cannot open file\n");
    fclose(file_in);
    exit(1);
  }


  while ((i = getc(file_in)) != EOF) // loop until you reach last character
  {
    if ('A' <= i && i <= 'Z') // Shifting capitals
    {
      i = ((i - 'A') + shift);
      i = (i % 26) + 'A';
    }
    else if ('a' <= i && i <= 'z') // shifting smalls
    {
      i = ((i - 'a') + shift);
      i = (i % 26) + 'a';
    }
    putc(i, file_out); // inject every single char in the output file
  }

  fclose(file_in); //Close input
  fclose(file_out); //close output

//end
  return 0;
}
