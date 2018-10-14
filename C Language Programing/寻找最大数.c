#include <stdio.h>
#define MAX(a,b,c) (a>b)?(a>c?a:c):(b>c?b:c)

int max_find (int a,int b,int c);

int main (void)
{
	int a,b,c,ans_1,ans_2;
	
	printf ("Please input three digital number.\n");
	scanf ("%d%d%d",&a,&b,&c);
	
	ans_1 = MAX (a,b,c);
	ans_2 = max_find (a,b,c);
	
	printf ("Using define : The most number is %d\n",ans_1);
	printf ("Using function : The most number is %d\n",ans_2);
	
	return 0;
}

int max_find (int a,int b,int c)
{
	return (a>b)?(a>c?a:c):(b>c?b:c);
}
