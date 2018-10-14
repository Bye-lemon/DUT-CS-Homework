#include <stdio.h>
#define N 10

int array [N]; 

int main (void)
{
	int count,i,temp,max = 0;

	printf ("Please input ten numbers:\n");
	for (i = 0;i <= N - 1;i ++)
		scanf ("%d",&array [i]);

	for (i = 1;i <= N;i ++)
	{
		for (count = max = i - 1;count <= (N - 1);count ++)
		{
			if (array [count] > array [max])
				max = count;
		}
		temp = array [i - 1];
		array [i - 1] = array [max];
		array [max] = temp;
	}

	printf ("The array from the biggest to the least is:");
	for (i = 0;i <= N - 1;i ++)
		printf ("%d ",array [i]);

	return 0;
}
