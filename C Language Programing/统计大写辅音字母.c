#include <stdio.h>
#include <string.h>

char line_1 [80],line_2 [80],line_3 [80];
int judge (char test);

int main (void)
{
	int temp,count = 0;

	printf ("Please input three lines words.\n");
	printf ("Now, please input No.1 line.\n");
	gets (line_1);
	printf ("Now, please input No.2 line.\n");
	gets (line_2);
	printf ("Now, please input No.3 line.\n");
	gets (line_3);

	for (temp = 0;temp < 79;temp ++)
	{
		count += judge (line_1 [temp]);
		count += judge (line_2 [temp]);
		count += judge (line_3 [temp]);
	}
	
	printf ("There are %d capital consonant letters in this paper.",count);
	
	return 0;
}
int judge (char test)
{
	int flag = 0;
	if (test <= 'Z' && test >= 'B' && test != 'E' && test != 'I' && test != 'O' && test != 'U')
		flag = 1;
	
	return flag;
}
