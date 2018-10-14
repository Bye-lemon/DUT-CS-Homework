#include <stdio.h>
#include <string.h>
#define NUM 10
#define STR 80

int main (void)
{
	void sort (char *s[]);
	char str [NUM] [STR],*strp [NUM];
	int count;
	
	printf ("Please input %d strings.",NUM);
	printf ("\nAttention: Any string can't have equal length.\n\n");
	
	for (count = 0;count < NUM;count ++)
	{
		printf ("Please input NO.%d string: ",count+1);
		gets (str [count]);
		strp [count] = str [count];
	}
	
	sort (strp);
	
	putchar ('\n');
	for (count = 0;count < NUM;count ++)
		puts (strp [count]);
		
	return 0;
}

void sort (char *s [])
{
	int cin,cex;
	char *p;
	
	for (cex = 0;cex < NUM-1;cex ++)
		for (cin = 0;cin < NUM-cex-1;cin ++)
			if (strcmp (s [cin],s [cin+1]) < 0)
			{
				p = s [cin];
				s [cin] = s [cin+1];
				s [cin+1] = p;
			}
}
