#include <stdio.h>
#include <math.h>

int x,count = 0;
double ans = 1,sum = 0,fct = 1;

int main (void)
{
	printf ("Please input a integer:\n");
	scanf ("%d",&x);
	
	if (x < 0)
	{
		printf ("\nAttention: x >= 0 !\n");
		scanf ("%d",&x);
	}
	
	while (fabs (ans) >= 0.000001)
	{
		if (count != 0)
			fct = fct * count;
		ans = pow (x,count) / fct;
		sum = sum + ans;
		count++;
	}
	
	printf ("%.4f",sum);
	
	return 0;
}

