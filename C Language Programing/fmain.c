#include <stdio.h>
#include <string.h>
#include "fstring.c"

void delchar (char s [100],char c);
void strreverse (char s [100]);

int main (void)
{
	int choose;
	char str;
	char array [100];
	
	while (1)
	{
		printf ("1.	Reverse a string.\n2.	Delete a character in a string.\n");
		printf ("Please input your choice: ");
		scanf ("%d",&choose);
		
		switch (choose)
		{
			case 2 :
			{
				printf ("Enter a string: ");
				fflush (stdin);
				gets (array);
				printf ("Enter a character you want to delete: ");
				fflush (stdin);
				scanf ("%c",&str);
				delchar (array,str);
				printf ("Deleted string is£º");
				puts (array);
				break;
			}
			case 1 :
			{
				printf ("Enter a string:");
				fflush (stdin);
				gets (array);
				strreverse (array);
				printf ("Reversed string is£º");
				puts (array);
				break;
			}
		}
		
		printf ("Would you like to continue?£¨y/n£©");
		fflush (stdin);
		scanf ("%c",&str);
		if (str == 'N' || str == 'n')
			break;
	}
	
	return 0;
}
