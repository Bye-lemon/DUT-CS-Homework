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
    
	cout<<"����������Ԫ�ص�ֵ��\n";
	intArrayBuild(p);
	cout<<"���鹹����ϣ�������������ǣ�\n";
	intArrayDisplay(p);
    cout<<"ִ�дδ�ֵ������ϣ����Ϊ��\n";
	intArraySecondLargeElemFind(p);

	return 0;
}

void intArrayBuild(int (*p)[C]) {
    for(int i = 0; i < R; i ++) {
		for(int j = 0; j < C; j ++) {
            cout<<"\t�������"<<i<<"��"<<j<<"�е�Ԫ�أ�";
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
            cout<<"\t��"<<i+1<<"�дδ�ֵΪ"<<second<<'\n';
		else
			cout<<"\t��"<<i+1<<"������Ԫ��ֵ����ȣ�Ϊ"<<max<<"�޴δ�ֵ\n";
	}
}