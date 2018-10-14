#include <stdio.h>
#include <stdlib.h>

#define K 10  //�ڴ˴��޸Ľ��� 
#define MAX 20000  //�ڴ˴��޸�����ֵ�����Ϊ65536�������޸�QElemType�������� 
#define OK 0

typedef int Status;
typedef int QElemType;
typedef struct {
    QElemType *base;
    int front;
    int rear;
} SqQueue;

SqQueue OneStepFibonacci (SqQueue Q);
SqQueue InitializalFibonacci (SqQueue Q);

SqQueue Q;

SqQueue InitializalFibonacci (SqQueue Q) {
    Q.base = (QElemType *) malloc (K * sizeof (QElemType));
    if (!Q.base)
        exit (-1);
    Q.front = Q.rear = 0;
    while (Q.rear < K-1) {
        Q.base[Q.rear] = 0;
        printf ("%d ", Q.base[Q.rear]);
        Q.rear += 1;
    }
    Q.base[Q.rear] = 1;
    Q.rear = 0;
    Q.front = K-1;
    
    return Q;
}

SqQueue OneStepFibonacci (SqQueue Q) {
    Q.front = (Q.rear + 1) % K;
    do {
        Q.base[Q.rear] += Q.base[Q.front];
        Q.front = (Q.front + 1) % K;
    } while (Q.front != Q.rear);
    Q.rear  = (Q.rear + 1) % K;
    
    return Q;
}

Status main (void) {
    int cnt;
    Q = InitializalFibonacci (Q);
    while (Q.base[Q.front] <= MAX) {
        printf ("%d ", Q.base[Q.front]);
        Q = OneStepFibonacci (Q);
    }
    printf ("\nPress Enter to Quit.");
    getchar ();
    
    return OK;
}
    
