#include <stdio.h>

int n,array [6] [6],sum = 0,count_l,count_c;

int main (void)
{
	while (1)
	{
		printf ("Please input a integer in the range from 1 to 6.\n");
		scanf ("%d",&n);
		if (n <= 6 && n >= 1)
			break;
		else
			printf ("Error!\n");	
	}
	printf ("Please enter a %d-order square.\n",n);
	for (count_l = 0;count_l <= (n - 1);count_l ++)
	{
		for (count_c = 0;count_c <= (n - 1);count_c ++)
		{
			scanf ("%d",&array [count_l] [count_c]);
		}
	}

	for (count_l = 0;count_l <= (n - 2);count_l ++)
	{
		for (count_c = 0;count_c <= (n - 2);count_c ++)
		{
			if ((count_l + count_c) != (n - 1))
				sum += array [count_l] [count_c];
		}
	}
	
	printf ("sum=%d",sum);
	
	return 0;
}
