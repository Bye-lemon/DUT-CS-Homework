#include <iostream>
#define INPUTSIZE 20
//INPUTSIZE为输入数据个数
#define KERNELSIZE 5 
//KERNELSIZE为滑动队列容量 
#define OUTPUTSIZE (INPUTSIZE - KERNELSIZE + 1)
//INPUTSIZE为输出数据个数

void filter (float source[], float dest[]) {
	int cnt = OUTPUTSIZE;
	int foo;
	float sum;
	
	for (foo = 0; foo < KERNELSIZE - 1; foo ++)
		sum += source[foo];
	sum += source[0];
	foo = 0;
	while (cnt) {
		sum -= source[(foo - 1) < 0? 0: (foo -1)];
		sum += source[foo + KERNELSIZE - 1];
		dest[foo] = sum / KERNELSIZE;
		foo ++;
		cnt --;
	}
}

int main (void) {
	float testList[INPUTSIZE];
	float resultList[OUTPUTSIZE];
	int cnt;
	
	//用1~20初始化输入数据 
	for (cnt = 0; cnt < INPUTSIZE; cnt ++)
		testList[cnt] = cnt + 1.00;
	//滑动平均滤波 
	filter (testList, resultList);
	//滤波效果展示
	printf ("Input parameter:\n");
	for  (cnt = 0; cnt < INPUTSIZE; cnt ++)
		printf("%.2f ", testList[cnt]);
	printf ("\nOutput parameter:\n");
	for  (cnt = 0; cnt < OUTPUTSIZE; cnt ++)
		printf("%.2f ", resultList[cnt]);
	
	return 0;
}
