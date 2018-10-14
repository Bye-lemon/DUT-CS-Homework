#include <stdio.h>
#include <math.h>

float low,high,mid,f_low,f_high,f_mid,temp;
float func (float x);

int main (void)
{
	do
	{
		printf ("Please input the lower and upper boundaries: ");
		scanf ("%f%f",&low,&high);
		
		f_low = func (low);
		f_high = func (high);
		temp = f_low * f_high;
		
		if (temp > 0)
			printf ("\nNo root in this boundary!\n");
	} while (temp > 0);
	
	if (f_low == 0)
		printf ("The root is %.2f",low);
	else if (f_high == 0)
		printf ("The root is %.2f",high);
	else
	{
		do
		{
			mid = (low + high) / 2;
			f_high = func (high);
			f_low = func (low);
			f_mid = func (mid);
			
			if (f_mid * f_low <= 0)
				high = mid;
			else
				low = mid;
		} while (f_mid > 0.0001 || f_mid < -0.0001);
		
		printf ("The root is %.2f",mid);
	}
	
	return 0;
}

float func (float x)
{
	float ans;
	ans = 2*x*x*x - 4*x*x + 3*x - 6;
	
	return ans;
}
