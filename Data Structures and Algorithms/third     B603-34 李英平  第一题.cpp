#include <stdio.h>
#include <stdlib.h>
#include <queue>

#define TRUE 1
#define FALSE 0


typedef int Status;
typedef char TElemType;
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild;
	struct BiTNode *rchild;
} BiTNode, *BiTree;

BiTree CreateBiTree (BiTree T) {
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
		T->lchild = CreateBiTree (T->lchild);
		T->rchild = CreateBiTree (T->rchild);
	}
	
	return T;
}

Status isCompleteBiTree (BiTree T) {
	std::queue<BiTree> Q;
	BiTree e;
	int flag = 0;
	
	if (T == NULL)
		return TRUE;
	Q.push (T);
	while (!Q.empty ()) {
		e = Q.front ();
		Q.pop ();
		if (e->lchild == NULL) 
			flag = 1;
		if (flag && (e->lchild != NULL || e->rchild != NULL))
			return FALSE;
		if (e->rchild == NULL) 
			flag = 1;
		if (e->lchild != NULL)
			Q.push (T->lchild);
		if (e->rchild != NULL)
			Q.push (T->rchild);
	}
	
	return TRUE;
}

Status main (void) {
	BiTree T;

	T = CreateBiTree (T);
	isCompleteBiTree (T)? printf ("Complete BiTree!"): printf ("Incomplete BiTree!");
	
	return 0;
}
