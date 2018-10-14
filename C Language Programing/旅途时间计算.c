#include <stdio.h>

int time_start,time_arrive,temp,temp_1,temp_2,hour,minute;

int main (void)
{
	printf ("Please input the time you start:\n");
	scanf ("%d",&time_start);
	printf ("\nPlease input the time you arrive:\n");
	scanf ("%d",&time_arrive);
	temp_1 = 60 * (time_arrive / 100) + (time_arrive % 100);
	temp_2 = 60 * (time_start / 100) + (time_start % 100);
	temp = temp_1 - temp_2;
	hour = temp / 60;
	minute = temp % 60;	
	printf ("\nThe train journey time is %d hours %d minutes.\n",hour,minute);
	
	return 0;
}
