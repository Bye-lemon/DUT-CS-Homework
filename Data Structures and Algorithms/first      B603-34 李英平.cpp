#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct {
	float coef;
	int expn;
}ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode * next;
} Node, * Polynomial;

Polynomial InitPolyn (int m);
Polynomial SortPolyn (Polynomial P, int m);
void DisplayPolyn (Polynomial P, int m);
Polynomial ReservePolyn (Polynomial P);
float CalcPolyn (Polynomial P, float x);
Polynomial AddPolyn (Polynomial Pa, Polynomial Pb);
void InitUI (void);
void TestFunc (void);

Polynomial InitPolyn (int m)
{
	int cnt;
	Polynomial P, p;
	
	P = (Polynomial) malloc (sizeof (Node));
	if (!P)
		P->next = NULL;
	for (cnt = m; cnt > 0; cnt --)
	{
		p = (Polynomial) malloc (sizeof (Node));
		printf ("�������%d����ĵ�����ָ����\n", m+1-cnt); 
		scanf ("%f %d", &p->data.coef, &p->data.expn);
		p->next = P->next;
		P->next = p;
	}
	P->data.expn = m;
	SortPolyn (P, m);
	
	return P;
}

Polynomial SortPolyn (Polynomial P, int m)
{
	Polynomial q;
	int cnt, i;
	ElemType temp;
	
	for (cnt = 0; cnt < m; cnt ++)
	{
		for (q = P->next, i = 0; i < m-cnt-1; q = q->next, i ++)
		{
			if (q->data.expn > q->next->data.expn)
			{
				temp = q->data;
				q->data = q->next->data;
				q->next->data = temp;
			}
		}
	}
	return P;	
}

void DisplayPolyn (Polynomial P, int m)
{
	Polynomial p = P->next;
	int cnt = 0;
	
	for (; cnt < m; cnt ++, p = p->next)
	{
		if (p->data.coef != 0)
			printf ("%f %d\n", p->data.coef, p->data.expn);
	}
}

Polynomial ReservePolyn (Polynomial P)
{
	Polynomial p, q;
	int m = P->data.expn;
	
	p = P->next;
	while (m --)
	{
		q = p;
		p = p->next;
		q->next = NULL;
		q->next = P->next;
		P->next = q;
	}
	return P;
}

float CalcPolyn (Polynomial P, float x) //�ؾ����㷨 
{
	int maxexpn, exp;
	float result = P->next->data.coef;
	Polynomial p;
	
	for (p = P->next, exp = maxexpn = p->data.expn; exp != 0; exp --)
	{
		result = result * x + ((exp-1 == p->next->data.expn)? p->next->data.coef: 0);
		if (exp-1 == p->next->data.expn)
			p = p->next;
	}
	return result;
}

Polynomial AddPolyn (Polynomial Pa, Polynomial Pb) 
{
	Polynomial pa, pb, p;
	int sum, m_a = Pa->data.expn, m_b = Pb->data.expn;
	
	p = Pa;
	pa = Pa->next;
	pb = Pb->next;
	Pa->data.expn += Pb->data.expn;
	while (m_a && m_b)
	{
		if (pa->data.expn > pb->data.expn)
		{
			p->next = pa;
			pa = pa->next;
			m_a --;
		}
		else if (pa->data.expn == pb->data.expn)
		{
			p->next = pa;
			pa->data.coef += pb->data.coef;
			pb = pb->next;
			pa = pa->next;
			Pa->data.expn -= 1;
			m_a --;
			m_b --;
		}
		else
		{
			p->next = pb;
			pb = pb->next;
			m_b --;
		}
		p = p->next;
	}
	if (!m_b)
		p->next = pb;
	else if (!m_a)
		p->next = pa;
	free (Pb);
	return Pa;
}

void InitUI (void)
{
    printf ("***************************************************\n");
    printf ("*                                                 *\n");
    printf ("*                  ��ӭʹ��!                      *\n");
    printf ("*                                                 *\n");
    printf ("*                [1]�������ʽ                    *\n");
    printf ("*                [2]չʾ����ʽ                    *\n");
    printf ("*                [3]���ö���ʽ                    *\n");
    printf ("*                [4]���㺯��ֵ                    *\n");
    printf ("*                [5]����ʽ�ӷ�                    *\n");
    printf ("*                [6]�˳�                          *\n");
    printf ("*                                                 *\n");
    printf ("***************************************************\n");
}

void TestFunc (void)
{
	int m;
	float x;
	Polynomial Pa, Pb;
	
	InitUI ();
	while (1)
	{
		int choice;
		printf ("\n��ѡ������Ҫʹ�õĹ��ܣ�");
		scanf ("%d", &choice);
		if (6 == choice)
			break;
		switch (choice)
		{
			case 1: 
				printf ("�������һ������ʽ���м��");
				scanf ("%d", &m);
				Pa = InitPolyn (m);
				printf ("������ڶ�������ʽ���м��");
				scanf ("%d", &m);
				Pb = InitPolyn (m);
				break;
			case 2:
				printf ("����������Ҫ��ʾ�ڼ�������ʽ�Ĳ�����");
				scanf ("%d", &m);
				switch (m)
				{
					case 1: DisplayPolyn (Pa, Pa->data.expn); break;
					case 2: DisplayPolyn (Pb, Pb->data.expn); break;
				}
				break;
			case 3:
				printf ("����������Ҫ���õڼ�������ʽ��");
				scanf ("%d", &m);
				switch (m)
				{
					case 1: Pa = ReservePolyn (Pa); DisplayPolyn (Pa, Pa->data.expn); break;
					case 2: Pb = ReservePolyn (Pb); DisplayPolyn (Pb, Pb->data.expn); break;
				}
				break;
			case 4:
				printf ("����������Ҫ����ڼ�������ʽ��ֵ��");
				scanf ("%d", &m);
				printf ("������δ֪����ֵ��");
				scanf ("%f", &x);
				switch (m)
				{
					case 1: Pa = ReservePolyn (Pa); x = CalcPolyn (Pa, x); printf ("%f", x); break;
					case 2: Pb = ReservePolyn (Pb); x = CalcPolyn (Pb, x); printf ("%f", x); break;
				}
				break;
			case 5:
				printf ("Warning: ���򽫶�ǰ��������ʽ��ӣ������ٵڶ�������ʽ��\n");
				Pa = ReservePolyn (Pa);
				Pb = ReservePolyn (Pb);
				Pa = AddPolyn (Pa, Pb);
				DisplayPolyn (Pa, Pa->data.expn);
				break;
			default:
				printf ("Error: ������ѡ��\n");
		}
	}
} 

int main (void)
{
	TestFunc ();
	return 0; 
}
