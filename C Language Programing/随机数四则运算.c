/*计算机自动出0-9之间的四则运算（+ - * /）计算题；由用户输入结果，然后自动批改结果是否正确。*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int a,b,d,flag;
float num,c,temp; 

int main (void)
{
	srand ((unsigned)time(NULL));
	a = rand () % 10;
	b = rand () % 10;
	d = rand () % 9 + 1;
	flag = rand () % 4;
	
	switch (flag)
	{
		case 0 : c = a + b; printf ("Please caculate: %d+%d= ",a,b); break;
		case 1 : c = a - b; printf ("Please caculate: %d-%d= ",a,b); break;
		case 2 : c = a * b; printf ("Please caculate: %d*%d= ",a,b); break;
		case 3 : c = (float)a / (float)d; printf ("Please caculate: %d/%d= ",a,d); break;		
	}
	
	scanf ("%f",&num);

	if (flag == 3)
	{
		temp = num - c;
		
		if (fabs (temp) <= 0.0001)
			printf ("\nCorrect!\n");
		else
			printf ("\nSorry, the answer is %f.",c);
	}
	else
	{
		if ((int)num == (int)c)
			printf ("\nCorrect!\n");
		else
			printf ("\nSorry, the answer is %d.",(int)c);
	}
	
	return 0;
}
