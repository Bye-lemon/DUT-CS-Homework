#include <stdio.h>

int main (void)
{
	int n = 0,count = 0,num;
	int array [6] [6];
	void transpose(int a [6] [6],int n);
	
	while (n < 1 || n > 6)
	{
		printf ("Please input a number from 1 to 6:");
		scanf ("%d",&n);
		putchar ('\n');
	}

	printf ("\nPlease input a %d*%d square.\n",n,n);
	for (;count < n;count ++)
	{
		printf ("Line %d\n",count + 1);
		for (num = 0;num < n;num ++)
			scanf ("%d",&array [count] [num]);
		putchar ('\n');
	}
	
	transpose(array,n);
	
	for (count = 0;count < n;count ++,putchar ('\n'))
		for (num = 0;num < n;num ++)
		{
			printf ("%d ",array [count] [num]);
		}
	
	return 0;
}

void transpose(int a [6] [6],int n)
{
	int c_c,c_l,temp;
	
	for (c_l = 0;c_l < n;c_l ++)
		for (c_c = c_l;c_c < n;c_c ++)
		{
			temp = a [c_l] [c_c];
			a [c_l] [c_c] = a [c_c] [c_l];
			a [c_c] [c_l] = temp;			
		}	
}
