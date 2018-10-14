#include <stdio.h>
#include <stdlib.h>

int choose;

int main (void)
{
	home ();
	if (choose == 1)
		{
			system ("cls");
			control (); 
		}
	else if (choose == 2)
		{
			system ("cls");
			users ();
		}	
	else if (choose == 3)
		{
			system ("cls");
			return; 
		} 
	else
	{ 
		system ("cls");
		printf ("请输入1~3之间的数字。\n\n");
		main();
	} 
} 

int home (void)
{
	printf ("\t\t\t欢迎使用飞机航班查询与订票系统\n");
	printf ("********************************************************************************\n");
	printf ("\t\t\t\t1.管理员登录\n");
	printf ("\t\t\t\t2.客户登录\n");
	printf ("\t\t\t\t3.退出系统\n"); 
	printf ("********************************************************************************\n");
	printf ("请输入选择：");
	scanf ("%d",&choose);
	
	return choose;
} 
int control (void)
{
	printf ("\t\t\t管理员登陆飞机航班信息管理系统\n");
	printf ("********************************************************************************\n");
	printf ("\t\t\t\t1.显示所有航班和乘客信息\n");
	printf ("\t\t\t\t2.添加航班\n");
	printf ("\t\t\t\t3.删除航班\n"); 
	printf ("\t\t\t\t4.修改航班信息\n"); 
	printf ("\t\t\t\t5.返回登陆界面\n"); 
	printf ("********************************************************************************\n");
	printf ("请输入选择：");
	scanf ("%d",&choose);
	
	if (choose == 5)
	{	
		system ("cls");
		main();
	} 
	else
		printf ("暂时还不会做（调皮脸）");
	
	return 0; 
}
int users (void)
{
	printf ("\t\t\t客户使用飞机航班查询与订票系统\n");
	printf ("********************************************************************************\n");
	printf ("\t\t\t\t1.显示所有航班信息\n");
	printf ("\t\t\t\t2.航班查询\n");
	printf ("\t\t\t\t3.航班订票\n"); 
	printf ("\t\t\t\t4.航班退票\n"); 
	printf ("\t\t\t\t5.返回登陆界面\n"); 
	printf ("********************************************************************************\n");
	printf ("请输入选择：");
	scanf ("%d",&choose);
	
	if (choose == 5)
	{	
		system ("cls");
		main ();
	} 
	else 
		printf ("暂时还不会做（调皮脸）");
	
	return 0; 
}
