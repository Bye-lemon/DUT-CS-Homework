#include <stdio.h>

int bool_a,bool_c,bool_d,bool_sum;

int main (void)
{
	doit ();
	
	bool_a = ! bool_a;
	bool_sum = bool_a + bool_c + bool_d;
	if (bool_sum == 1)
		printf ("A说的是假话。");
	bool_a = ! bool_a;
	/*验证A说假话的情况，而后重置*/ 
	bool_c = ! bool_c;
	bool_sum = bool_a + bool_c + bool_d;
	if (bool_sum == 1)
		printf ("B说的是假话。");
	bool_c = ! bool_c;
	/*验证B说假话的情况，而后重置*/ 	
	bool_sum = bool_a + bool_c + bool_d;
	if (bool_sum == 1)
		printf ("C说的是假话。C做的好事。");
	/*验证C说假话的情况，而后重置*/ 	
	bool_d = ! bool_d;
	bool_sum = bool_a + bool_c + bool_d;
	if (bool_sum == 1)
		printf ("D说的是假话。D做的好事。");
	bool_d = ! bool_d;
	/*验证D说假话的情况，而后重置*/ 
	
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

