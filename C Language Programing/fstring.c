/*#ifndef <stdio.h>
#include <stdio.h>
#endif
#ifndef <string.h>
#include <string.h>
#endif*/

void delchar (char s [100],char c)
{
	int count,temp;
	
	for (count = 0;s [count] != '\0';count ++)
		if (s [count] == c)
		{
			for (temp = count;s [temp] != '\0';temp ++)
				s [temp] = s [temp + 1];
		
			count --;
		}
}

void strreverse (char s [100])
{
	int count,num_d,num;
	char temp;
	
	num_d = strlen (s);
	num = num_d / 2;
	
	for (count = 0;count < num;count ++)
	{
		temp = s [num_d - count - 1];
		s [num_d - count - 1] = s [count];
		s [count] = temp;
	}
}
