#include <stdio.h>

int bool_a,bool_c,bool_d,bool_sum;

int main (void)
{
	doit ();
	
	bool_a = ! bool_a;
	bool_sum = bool_a + bool_c + bool_d;
	if (bool_sum == 1)
		printf ("A˵���Ǽٻ���");
	bool_a = ! bool_a;
	/*��֤A˵�ٻ����������������*/ 
	bool_c = ! bool_c;
	bool_sum = bool_a + bool_c + bool_d;
	if (bool_sum == 1)
		printf ("B˵���Ǽٻ���");
	bool_c = ! bool_c;
	/*��֤B˵�ٻ����������������*/ 	
	bool_sum = bool_a + bool_c + bool_d;
	if (bool_sum == 1)
		printf ("C˵���Ǽٻ���C���ĺ��¡�");
	/*��֤C˵�ٻ����������������*/ 	
	bool_d = ! bool_d;
	bool_sum = bool_a + bool_c + bool_d;
	if (bool_sum == 1)
		printf ("D˵���Ǽٻ���D���ĺ��¡�");
	bool_d = ! bool_d;
	/*��֤D˵�ٻ����������������*/ 
	
	return 0;
}

int A (void)
{
	bool_a = 0;
	
	return (bool_a);
}
int B (void)
{
	bool_c = 1;
	
	return (bool_c);
}
int C (void)
{
	bool_d = 1;
	
	return (bool_d);
}
int D (void)
{
	bool_d = 0;
	
	return (bool_d);
}
void doit (void)
{
	A ();
	B ();
	C ();
	D ();
}

