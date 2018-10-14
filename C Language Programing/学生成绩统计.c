#include <stdio.h>
#define N 30

struct SS
{
	char name [10];
	int number;
	int grade [5];
	float ave;
};

int main (void)
{
	struct SS class [N];
	int count,cin;
	void average (struct SS ss []);
	void findfail (struct SS ss []);
	void findgood (struct SS ss []);
	
	printf ("Please input every students information.\n");
	for (count = 0;count < N;count ++)
	{
		printf ("Please input NO.%d students' name, school number, every grade.\n",count+1);
		fflush (stdin);
		gets (class [count].name);
		scanf ("%d",&class [count].number);
		for (cin = 0;cin < 5;cin ++)
			scanf ("%d",&class [count].grade [cin]);
	}
	
	average (class);
	
	printf ("They fail:\n");
	findfail (class);
	
	printf ("They are good.\n");
	findgood (class);
	
	return 0;
}

void average (struct SS ss [])
{
	int count,sum = 0,cin;
	
	for (count = 0;count < N;count ++,sum = 0)
	{
		for (cin = 0;cin < 5;cin ++)
			sum += ss [count].grade [cin];
		ss [count].ave = sum / 5.0f;
	}
}

void findfail (struct SS ss [])
{
	int count,cin,flag = 0;
	
	for (count = 0;count < N;count ++)
	{
		flag = 0;
		for (cin = 0;cin < 5;cin ++)
		{
			if (ss [count].grade [cin] < 60)
				flag ++;
		}
		if (flag >= 2)
			printf ("%s %d %d %d %d %d %d %.2f\n",ss [count].name,ss [count].number,ss [count].grade [0],
			ss [count].grade [1],ss [count].grade [2],ss [count].grade [3],ss [count].grade [4],ss [count].ave);
	}
}

void findgood (struct SS ss [])
{
	int count,cin,flag = 1,rec = 0;
	
	for (count = 0;count < N;count ++)
	{
		flag = 0;
		if (ss [count].ave >= 90)
			flag = 1;
		for (cin = 0,rec = 0;cin < 5;cin ++)
			if (ss [count].grade [cin] >= 85)
				rec ++;
		if (rec == 5)
			flag = 1;
		if (flag == 1)
			printf ("%s %d %d %d %d %d %d %.2f\n",ss [count].name,ss [count].number,ss [count].grade [0],
			ss [count].grade [1],ss [count].grade [2],ss [count].grade [3],ss [count].grade [4],ss [count].ave);
	}
}
