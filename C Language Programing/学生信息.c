#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 20

int home (void); 
void input (char name [N] [10],int grade [N]);
void sort (char name [N] [10],int grade [N]);
void display (char name [N] [10],int grade [N]);
int search (char name [N] [10],int grade [N]);

int main (void)
{
	char name [N] [10];
	int grade [N];
	int i,choose;
	char to_do;

	while (1)
	{
		choose = home ();
		
		if (choose == 1)
		{
			system ("cls");
			input (name,grade);
		}
		else if (choose == 2)
		{
			system ("cls");
			sort (name,grade);
		}	
		else if (choose == 3)
		{
			system ("cls");
			display (name,grade); 
		}
		else if (choose == 4)
		{
			system ("cls");
			i = search (name,grade);
		
			if (i = -1)
				printf ("Error. This student not found.");
			else
				printf ("%s %d",name [i],grade [i]); 
		} 
		else if (choose == 5)
		{
			system ("cls");
			exit (0); 
		} 
		else
		{ 
			system ("cls");
			printf ("请输入1~5之间的数字。\n\n");
			continue;
		} 
		
		while (1)	
		{
			printf ("\nDo you need to do more operating? (y/n) :");
			fflush (stdin);
			scanf ("%c",&to_do);
			if (to_do == 'y' || to_do == 'Y')
				break;
			else if (to_do == 'n' || to_do == 'N')
				return 0;
			else 
				printf ("\nError: Please input as require.");
		}
		
		system ("cls");	
	}
	
	return 0;
}

int home (void)
{
	int choose;
	
	printf ("\t\t\t欢迎使用学生成绩统计系统\n");
	printf ("********************************************************************************\n");
	printf ("\t\t\t\t1.录入成绩\n");
	printf ("\t\t\t\t2.执行排序\n");
	printf ("\t\t\t\t3.显示数据\n");
	printf ("\t\t\t\t4.查找信息\n");
	printf ("\t\t\t\t5.退出系统\n"); 
	printf ("********************************************************************************\n");
	printf ("请输入选择：");
	scanf ("%d",&choose);
	
	return choose;
} 

void input (char name [N] [10],int grade [N])
{
	int count;
	
	printf ("Please input these %d students' informations.\n",N);
	for (count = 0;count < N;count ++)
	{
		printf ("Student %d Name & Grade:",count);
		gets (name [count]);
		fflush (stdin);
		scanf ("%d",&grade [count]);
		fflush (stdin);
		putchar ('\n');
	}
}

void sort (char name [N] [10],int grade [N])
{
	int c_ex,c_in,temp;
	char temp_ch [10];
	
	for (c_ex = 0;c_ex < N;c_ex ++)
		for (c_in = 0;c_in < N - c_ex;c_in ++)
			if (grade [c_in] < grade [c_in + 1])
			{
				temp = grade [c_in];
				grade [c_in] = grade [c_in + 1];
				grade [c_in + 1] = temp;
				strcpy (temp_ch,name [c_in]);
				strcpy (name [c_in],name [c_in + 1]);
				strcpy (name [c_in + 1],temp_ch);
			}
}

void display (char name [N] [10],int grade [N])
{
	int count;
	
	for (count = 0;count < N;count ++)
	{
		printf ("No.%d Name & Grade:",count + 1);
		printf ("%s %d",name [count],grade [count]);
		putchar ('\n');
	}	
}

int search (char name [N] [10],int grade [N])
{
	char temp_ch [10];
	int address = -1,count;
	
	printf ("please input the students' name you want to find:");
	fflush (stdin);
	gets (temp_ch);
	putchar ('\n');
	
	for (count = 0;count < N;count ++)
		if (strcmp(temp_ch,name [count]) == 0)
			address = count;
	
	return address;
}
