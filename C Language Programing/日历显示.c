#include <stdio.h>
#include <stdlib.h>
#define FIRST_DAY 7
#define FEB_DAYS 28

/*��һ���궨�����ڴ洢�����һ�������ڼ���
�ڶ����궨�����ڴ洢������·��м��졣*/ 

int month_in,count,sum = 0,temp,day;
char flag;
int month[12] = {31,FEB_DAYS,31,30,31,30,31,31,30,31,30,31};
void in_out (void),judge (void),output (void);

int main (void)
{
	do
	{
		in_out ();
		while (1)
		{
			judge ();
			
			if (flag ==  'y' || flag == 'Y' || flag == 'n' || flag == 'N')
				break;
			else
				printf ("ERROR---Enter \'y\' or \'n\'\n");	
		}
		if (flag ==  'y' || flag == 'Y')
			continue;
		else
			break;
	} while (1);
	
	return 0;
}

void in_out (void)
{
	do
	{
		printf ("Enter month in 2017 to display calendar (1-12):");
		fflush (stdin);
		scanf ("%d",&month_in);
		putchar ('\n');
		
		if (month_in > 12 || month_in < 1)
			printf ("ERROR--- Enter month in range of (1-12)!\n");
		else
			break;
	} while (1);
	
	for (count = 0;count <= (month_in - 2);count++)
		sum += month[count];
	
	temp = sum % 7;
	day = (FIRST_DAY + temp) % 7;
	sum = 0;
	
	output ();
}

void output (void)
{
	day = (day + 1) % 7;/*�������µ�һ������λ��*/ 
	switch (day)
	{
		case 0 : day = 7; break;
	}/*��Ӧ��SAT����ʾʱ���������ʽ��ֵΪ0����ʾ���λ����switch��λ����0����7*/ 
	printf ("****************************************************\n");
	printf ("  SUN   MON  TUE   WED   THU   FRI   SAT  \n");
	for (count = 1;count < day;count++)
		printf ("      ");
	for (count = 1;count <= month[month_in - 1];count++)
	{
		if ((count + day - 1) % 7 != 0)
			printf ("  %2d  ",count);
		else
			printf ("  %2d  \n",count);
	}
	putchar ('\n');
} 

void judge (void)
{
	printf ("Would you like to display another month (y/n) ? ");
	fflush(stdin);
	scanf ("%c",&flag);
	putchar ('\n');
}
