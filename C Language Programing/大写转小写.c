#include <stdio.h>

char letter;

int main (void)
{
	printf ("Please input a capital letter:\n");
	scanf ("%c",&letter);
	letter = letter + 32;
	printf ("It\'s lower case is %c",letter);
	
	return 0;
} 
