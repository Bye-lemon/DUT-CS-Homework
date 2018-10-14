#include <stdio.h>

int number,temp_k,temp_h,temp_d,temp,hide;

int main (void)
{
	printf ("Please input a four digit number:\n");
	scanf ("%d",&number);
	temp_k = (9 + number / 1000) % 10;
	temp_h = (9 + (number / 100 - 10 * temp_k))% 10;
	temp_d = (9 + (number % 100) / 10) % 10;
	temp = (9 + number % 10) % 10;
	hide = 1000 * temp_d + 100 * temp + 10 * temp_k + temp_h;
	printf ("The encrypted number is %d",hide);
	
	return 0;
}
