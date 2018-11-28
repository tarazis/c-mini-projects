#include <stdio.h>
#include <stdlib.h>
/*
This program writes an encryption method named after Julios Caesar. The letters are encrypted by shifting each letter by a
fixed number of positions in the alphabet.
*/

#define SIZE 80 // MAX SIZE

int main(void)
{
	char text[SIZE] = {}; //array of chars to store text in
	char userInput; // will store every character of the inputted phrase

	int i, shiftNum;

	printf("Enter your message:");

	for (i = 0; (userInput = getchar()) != '\n'; i++) // get every letter of the message
	{
	//	printf("%d ", i);
		if (i >= SIZE) { // if message is too big exit program
			printf("your text is too big. Please limit to 80 chars and try again!\n");
			exit(0);
		} else {
				text[i] = userInput; // register character in array
		}

	}

	printf("Enter your desired shift amount (1-25):");
	scanf("%d", &shiftNum);

	while (shiftNum < 1 || shiftNum > 25) { // make sure to have a correct shift amount
		printf("Incorrect shift amount.\n");
		printf("Enter your desired shift amount (1-25):\n");
		scanf("%d", &shiftNum);
	}

	for (i = 0; i < SIZE; i++) // go through the whole array and replace with desired position
	{
		if (text[i] == 0){ // if no elements break loop
			break;
		}

		if (text[i] >= 'A' && text[i] <= 'Z') //shift capital letters
		{
			text[i] = (text[i] - 'A') + shiftNum;
			text[i]= text[i]% 26 + 'A';
		}

		if (text[i] >= 'a' && text[i] <= 'z') //shift small letters
		{
			text[i] = (text[i] - 'a') + shiftNum;
			text[i] = text[i] % 26 + 'a';
		}
	}

	printf("Your encrypted message: ");

	for (i = 0; i < SIZE; i++) // print every element of array to the user as 'encrypted message'
	{
		if (text[i] == 0){
			break;
		}
		putchar(text[i]);
	}

	printf("\n");

	return 0;
}
