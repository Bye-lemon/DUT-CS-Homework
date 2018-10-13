#include"iostream"
#define R 2
#define C 3
#define MAX 65536

using namespace std;

void intArrayBuild(int (*p)[C]);
void intArrayDisplay(int (*p)[C]);
void intArraySecondLargeElemFind(int (*p)[C]);

int main(void) {
    int (*p)[C];
	p = new int[R][C];
    
	cout<<"请输入数组元素的值：\n";
	intArrayBuild(p);
	cout<<"数组构建完毕，您输入的数组是：\n";
	intArrayDisplay(p);
    cout<<"执行次大值查找完毕，结果为：\n";
	intArraySecondLargeElemFind(p);

	return 0;
}

void intArrayBuild(int (*p)[C]) {
    for(int i = 0; i < R; i ++) {
		for(int j = 0; j < C; j ++) {
            cout<<"\t请输入第"<<i<<"行"<<j<<"列的元素：";
			cin>>*(*(p+i)+j);
		}
	}
}

void intArrayDisplay(int (*p)[C]) {
    for(int i = 0; i < R; i ++) {
		cout<<'\t';
		for(int j = 0; j < C; j ++)
            cout<<*(*(p+i)+j)<<' ';
	    cout<<'\n';
	}
}

void intArraySecondLargeElemFind(int (*p)[C]) {
	for(int i = 0; i < R; i ++) {
		for(int j = 1, max = *(*(p+i)+0), second = -MAX; j < C; j ++) {
			if(*(*(p+i)+j) >= second && *(*(p+i)+j) >= max) {
				second = max;
				max = *(*(p+i)+j);
			}
			else if(*(*(p+i)+j) >= second && *(*(p+i)+j) < max)
				second = *(*(p+i)+j);
			else
				continue;
		}
		if(max != second)
            cout<<"\t第"<<i+1<<"行次大值为"<<second<<'\n';
		else
			cout<<"\t第"<<i+1<<"行所有元素值均相等，为"<<max<<"无次大值\n";
	}
}