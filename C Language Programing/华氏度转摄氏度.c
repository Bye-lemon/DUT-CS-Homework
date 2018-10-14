#include <stdio.h>

float degree,fahrenheit;

int main (void)
{
	printf ("Please input Fahrenheit temperature: ");
	scanf ("%f",&fahrenheit);
	degree = 5 * (fahrenheit - 32) / 9;
	printf ("\nThe corresponding Celsius temperature is %.2f",degree);
	
	return 0;
} 
