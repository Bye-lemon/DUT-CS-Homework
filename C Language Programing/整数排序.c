/* �Ӽ�����������4�����������䰴��С����˳������������*/

#include <stdio.h>

int num_1,num_2,num_3,num_4,temp;

int main (void)
{
	printf ("Please input four integer.\n");
	scanf ("%d%d%d%d",&num_1,&num_2,&num_3,&num_4);
	
	if (num_1 > num_2)
	{
		temp = num_1;
		num_1 = num_2;
		num_2 = temp;
	}
	if (num_2 > num_3)
	{
		temp = num_2;
		num_2 = num_3;
		num_3 = temp;
	}
	if (num_3 > num_4)
	{
		temp = num_3;
		num_3 = num_4;
		num_4 = temp;
	}
	if (num_2 > num_3)
	{
		temp = num_2;
		num_2 = num_3;
		num_3 = temp;
	} 
	if (num_1 > num_2)
	{
		temp = num_1;
		num_1 = num_2;
		num_2 = temp;
	}
	
	printf ("\nAfter ascending sorting:%d %d %d %d\n",num_1,num_2,num_3,num_4);
	
	return 0;
}

