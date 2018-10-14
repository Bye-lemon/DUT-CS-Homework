#include <stdio.h>
#include <math.h>

float number;

int main (void)
{
	printf ("Please input a number:\n");
	scanf ("%f",&number);
	printf ("The square root of %.1f is %.1f\n",number,sqrt(number));
	
	return 0;
}
