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
		printf ("������1~3֮������֡�\n\n");
		main();
	} 
} 

int home (void)
{
	printf ("\t\t\t��ӭʹ�÷ɻ������ѯ�붩Ʊϵͳ\n");
	printf ("********************************************************************************\n");
	printf ("\t\t\t\t1.����Ա��¼\n");
	printf ("\t\t\t\t2.�ͻ���¼\n");
	printf ("\t\t\t\t3.�˳�ϵͳ\n"); 
	printf ("********************************************************************************\n");
	printf ("������ѡ��");
	scanf ("%d",&choose);
	
	return choose;
} 
int control (void)
{
	printf ("\t\t\t����Ա��½�ɻ�������Ϣ����ϵͳ\n");
	printf ("********************************************************************************\n");
	printf ("\t\t\t\t1.��ʾ���к���ͳ˿���Ϣ\n");
	printf ("\t\t\t\t2.��Ӻ���\n");
	printf ("\t\t\t\t3.ɾ������\n"); 
	printf ("\t\t\t\t4.�޸ĺ�����Ϣ\n"); 
	printf ("\t\t\t\t5.���ص�½����\n"); 
	printf ("********************************************************************************\n");
	printf ("������ѡ��");
	scanf ("%d",&choose);
	
	if (choose == 5)
	{	
		system ("cls");
		main();
	} 
	else
		printf ("��ʱ������������Ƥ����");
	
	return 0; 
}
int users (void)
{
	printf ("\t\t\t�ͻ�ʹ�÷ɻ������ѯ�붩Ʊϵͳ\n");
	printf ("********************************************************************************\n");
	printf ("\t\t\t\t1.��ʾ���к�����Ϣ\n");
	printf ("\t\t\t\t2.�����ѯ\n");
	printf ("\t\t\t\t3.���ඩƱ\n"); 
	printf ("\t\t\t\t4.������Ʊ\n"); 
	printf ("\t\t\t\t5.���ص�½����\n"); 
	printf ("********************************************************************************\n");
	printf ("������ѡ��");
	scanf ("%d",&choose);
	
	if (choose == 5)
	{	
		system ("cls");
		main ();
	} 
	else 
		printf ("��ʱ������������Ƥ����");
	
	return 0; 
}
