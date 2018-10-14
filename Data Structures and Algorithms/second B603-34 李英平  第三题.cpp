#include <stdio.h>
#include <stdlib.h>

#define OK 0

typedef int Status;
typedef struct BiTNode {
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
typedef BiTree QElemType;
typedef struct QNode {
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;
typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

BiTree T;
char ch;

LinkQueue InitializalNewQueue (LinkQueue Q) {
    Q.front = Q.rear = (QueuePtr) malloc (sizeof (QNode));
    if (!Q.front)
        exit (-1);
    Q.front->next = NULL;
    return Q;
}

LinkQueue PushElement (LinkQueue Q, QElemType T) {
    QueuePtr p;
    
    p = (QueuePtr) malloc (sizeof (QNode));
    if (!p)
        exit (-1);
    p->data = T;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    
    return Q;
}

QElemType PopElement (LinkQueue Q) {
    QueuePtr p;
    QElemType e;
          
    if (Q.front == Q.rear)
        return NULL;
    p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front;
    free (p);
    
    return e;
}

void CreateNewBiTree (BiTree &T) {
    scanf ("%c", &ch);
    if(ch == '#')
        T = NULL;
    else {
        T = (BiTree) malloc (sizeof (BiTNode));
        T->data = ch;
        CreateNewBiTree (T->lchild);
        CreateNewBiTree (T->rchild);
    }
}

void NoRecursionLevelTravel (BiTree T) {
    LinkQueue Q; 
    BiTree tmp;
    
    Q = InitializalNewQueue (Q);
    if (T == NULL)
        return;
    Q = PushElement (Q, T);
    
    while (Q.front != Q.rear) {
        tmp = PopElement (Q);
        putchar (tmp->data);
        
        if (tmp->lchild != NULL)
            Q = PushElement (Q, tmp->lchild);
        if (tmp->rchild != NULL)
            Q = PushElement (Q, tmp->rchild); 
    }
}  

void NoRecursionBiTreeWidth (BiTree T) {
	LinkQueue Q;
	BiTree tmp;
	int Width = 0, thisWidth = 0;
	QueuePtr flag;
	
	Q = InitializalNewQueue (Q);
	flag = Q.rear;
    if (T == NULL)
        return;
    Q = PushElement (Q, T);
    
    while (Q.front != Q.rear) {
        tmp = PopElement (Q);
        thisWidth ++;
        
        if (tmp->lchild != NULL)
            Q = PushElement (Q, tmp->lchild);
        if (tmp->rchild != NULL)
            Q = PushElement (Q, tmp->rchild); 
        if (Q.front > flag) {
        	flag = Q.rear;
        	Width = (thisWidth > Width)? thisWidth: Width;
        	thisWidth = 0;
		}
    }
    
    printf ("This BiTree's Width is %d.", Width);
}

Status main (void) {
    CreateNewBiTree (T);
    printf ("haha");
    NoRecursionLevelTravel (T);
    NoRecursionBiTreeWidth (T);
	
    return OK;
}
    
