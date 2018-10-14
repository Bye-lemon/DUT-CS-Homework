#include <stdio.h>

int main (void)
{
	int n,m,array [10],count;
	void shift (int a [],int n,int m);
	
	while (1)
	{
		printf ("Input n(n<=10)£º");
		scanf ("%d",&n);
		if (n <= 10 && n > 0)
			break;
		else 
			printf ("\nError! Please follow the request.\n");
	}
	
	printf ("Input %d integers£º",n);
	for (count = 0;count < n;count ++)
		scanf ("%d",&array [count]);
		
	printf ("Output the original£º");
	for (count = 0;count < n;count ++)
		printf ("%d ",array [count]);
	putchar ('\n');
		
	while (1)
	{
		printf ("Input m(m<=%d)£º",n);
		scanf ("%d",&m);
		
		if (m <= n && m > 0)
			break;
		else 
			printf ("\nError! Please follow the request.\n");
	}	
	shift (array,n,m);
	
	printf ("Output the shifted£º");
	for (count = 0;count < n;count ++)
		printf ("%d ",array [count]);
	putchar ('\n');
		
	return 0;
} 

void shift (int a [],int n,int m)
{
	int count,temp [10];
	
	for (count = 0;count < n;count ++)
	{
		if (count+m < n)
			temp [count+m] = a [count];
		else 
			temp [count+m-n] = a [count];
	}
	
	for (count = 0;count < n;a [count] = temp [count],count++);
}
