#include <stdio.h>

int main (void)
{
	int n,m,a [5] [5],b [5] [5],c [5] [5],count,cin;
	void multiply (int a [5] [5],int b [5] [5],int c [5] [5]);
	
	while (1)
	{
		printf ("Input m and n (1~5)£º");
		scanf ("%d%d",&m,&n);
		if (m >= 1 && m <= 5 && n >= 1 && n <= 5)
			break;
		else 
			printf ("\nError! Please follow the request.\n");
	}
	printf ("Input A%d X %d£º\n",m,n);
	for (count = 0;count < m;count ++)
		for (cin = 0;cin < n;cin ++)
			scanf ("%d",&a [count] [cin]);
	printf ("Input B%d X %d£º\n",n,m);
	for (count = 0;count < n;count ++)
		for (cin = 0;cin < m;cin ++)
			scanf ("%d",&b [count] [cin]);
	
	multiply (a,b,c);
	
	printf ("C=AXB is£º\n");
	for (count = 0;count < m;count ++)
	{
		for (cin = 0;cin < m;cin ++)
			printf ("%-3d ",c [count] [cin]);
		putchar ('\n');
	}
	
	return 0;
}

void multiply (int a [5] [5],int b [5] [5],int c [5] [5])
{
	int c_c,c_l,cin;
	int i,j;
	for (c_c = 0;c_c < 5;c_c ++)
		for (cin = 0;cin < 5;cin ++)
			c [c_c] [cin] = 0;
	
	for (c_c = 0;c_c < 5;c_c ++)
		for (c_l = 0;c_l < 5;c_l ++)
			for (cin = 0;cin < 3;cin ++)
				c [c_c] [c_l] += (a [c_c] [cin]) * (b [cin] [c_l]); 
}
