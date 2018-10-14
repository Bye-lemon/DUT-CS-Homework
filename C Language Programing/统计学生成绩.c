#include <stdio.h>
#include <conio.h>
#define N 10

int MT [N],EN [N],PH [N],SUM [N],AVE [N],temp;
char _90 [N];

int main (void)
{
	printf ("Please input every student's math grade, English grade and physics grade:\n");

	for (temp = 0;temp <= (N - 1);temp ++)
	{
		printf ("Now, please enter NO.%d student's grades.\n",temp + 1);
		scanf ("%d%d%d",&MT [temp],&EN [temp],&PH [temp]);
		SUM [temp] = MT [temp] + EN [temp] + PH [temp];
		AVE [temp] = SUM [temp] / 3;
		if (MT [temp] >= 90 && EN [temp] >= 90 && PH [temp] >= 90)
			_90 [temp] = 'Y';
		else
			_90 [temp] = 'N';
	}

	printf ("NO     MT   EN   PH   SUM   AVE  >90 \n");
	printf (" --------------------------------------------------------------------\n");
	for (temp = 0;temp <= (N - 1);temp ++)
		printf ("%d       %d    %d    %d    %d    %d    %c\n",temp,MT [temp],EN [temp],PH [temp],SUM [temp],AVE [temp],_90 [temp]);

	return 0;
}
