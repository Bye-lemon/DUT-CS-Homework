#include <stdio.h>
#define N 10

int array [N];

int main (void)
{
	int count,i,temp;

	printf ("Please input ten numbers:\n");
	for (i = 0;i <= N - 1;i ++)
		scanf ("%d",&array [i]);

	for (i = 1;i <= N;i ++)
	{
		for (count = 0;count <= (N - i - 1);count ++)
		{
			if (array [count] < array [count + 1])
			{
				temp = array [count];
				array [count] = array [count + 1];
				array [count + 1] = temp;
			}
		}
	}

	printf ("The array from the biggest to the least is:");
	for (i = 0;i <= N - 1;i ++)
		printf ("%d ",array [i]);

	return 0;
}
