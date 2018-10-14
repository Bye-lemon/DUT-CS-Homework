#include <stdio.h>

char str_1 [50],str_2 [50],str [100];
int count_1,count_2,temp;

int main (void)
{
	printf ("Please input two strings.\n");
	printf ("Now, Please input the first string.\n");
	gets (str_1);
	printf ("Now, Please input the second string.\n");
	gets (str_2);
	
	for (temp = 0;str_1 [temp] != '\0';temp ++);
	count_1 = temp - 1;
	for (temp = 0;str_2 [temp] != '\0';temp ++);
	count_2 = temp - 1;
	for (temp = 0;temp <= count_1;temp ++)
		str [temp] = str_1 [temp];
	for (temp = 0;temp <= count_2;temp ++)
		str [temp + count_1 + 1] = str_2 [temp];
	str [count_1 + count_2 + 3] = '\0';

	printf ("%s",str);
	
	return 0;
}
