#include <stdio.h>
#include <stdlib.h>
#include <stack>

#define MAX(a,b) (a>=b?a:b)

typedef char TElemType;
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild;
	struct BiTNode *rchild;
} BiTNode, *BiTree;

static int trees = 1;
static int leaves = 0;

BiTree CreateBiLinkForest (BiTree T) {
	char ch;
	
	fflush (stdin);
	ch = getchar ();
	if (ch == '#')
		T = NULL;
	else {
		T = (BiTNode *) malloc (sizeof (BiTNode));
		if (!T)
			exit (-1);
		T->data = ch;
		T->lchild = CreateBiLinkForest (T->lchild);
		T->rchild = CreateBiLinkForest (T->rchild);
	}
	
	return T;
}

void ForestInorderTraversal (BiTree T) {
	std::stack<BiTree> S;
	BiTree p = T;
	
	if (T == NULL)
		return;
	else {
		while (p != NULL || !S.empty ()) {
			if (p) {
				S.push (p);
				p = p->lchild;
			} else {
				p = S.top ();
				S.pop ();
				printf ("%c", p->data);
				p = p->rchild;
			}
		}
	}
}

void CalcNumberOfLeavesInForest (BiTree T) {	
	if (T == NULL)
		return;
	if (T->lchild == NULL)
		leaves ++;
	CalcNumberOfLeavesInForest (T->lchild);
	CalcNumberOfLeavesInForest (T->rchild);
}

void CalcNumberOfTreesInForest (BiTree T) {	
	if (T->rchild != NULL) {
		trees ++;
		CalcNumberOfTreesInForest (T->rchild);
	}
}

int CalcHeightOfTheFirstTreeInForest (BiTree T) {
	static int height = 0;
	
	return ((T == NULL)? 0: MAX (CalcHeightOfTheFirstTreeInForest (T->lchild), CalcHeightOfTheFirstTreeInForest (T->rchild)) + 1);
} 

int main (void) {
	BiTree T;
	int height;
	
	T = CreateBiLinkForest (T);
	ForestInorderTraversal (T);
	putchar ('\n');
	CalcNumberOfLeavesInForest (T);
	CalcNumberOfTreesInForest (T);
	height = CalcHeightOfTheFirstTreeInForest (T);
	printf ("Leveas:%d, Trees:%d, Height of the First Tree:%d.", leaves, trees, height);
	
	return 0;
}
