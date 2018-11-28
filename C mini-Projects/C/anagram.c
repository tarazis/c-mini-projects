/*
This program checks if two words are made of the same letters regardless of case.
*/

#include <stdio.h>
#include <ctype.h>

int main(void)
{
	char userInput;
	int i,flag = 0;
	int text[26] = {0};

	printf("Please enter your first word: ");

// take every character, make it lower case, check if it's a letter
// then add 1 in its position in the array (assuming that text[0] is a and text[1] is b ..etc. )
	for (i = 0; (userInput = getchar()) != '\n'; i++) {
		userInput = tolower(userInput);
		if (isalpha(userInput) != 0){
			text[userInput - 'a']++;
		}
}
	printf("Please enter your second word: ");

	// take every character of the second word, make it lower case, check if it's a letter
	// then subtract 1 in its position in the array (assuming that text[0] is a and text[1] is b ..etc. )
	for (i = 0; (userInput = getchar()) != '\n'; i++)
	{
		userInput = tolower(userInput);
		if (isalpha(userInput) != 0)
		text[userInput - 'a']--;
	}

	for (i = 0; i < 26; i++)
	{
		if (text[i] != 0) // if an element is not 0 then letters did not match. so, flag = 1 and break off the loop
		{
			flag = 1;
			break;
			//return 0;
		}
	}
	if (flag == 1) {
		printf("The words are not anagrams.\n");
	} else {
			printf("The words are anagrams.\n");
	}
	return 0;
}
