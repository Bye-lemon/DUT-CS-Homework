#include"iostream"
#define N 10
#define MAX 65536

using namespace std;

class nIntArray {
private:
	int array[N];
public:
	nIntArray(void);
	void input(void);
    void disp(void);
	int max(int *p);
	void find(void);
};

void sort(int array[N]) {
	for(int i = 0; i < N - 1; i ++) {
		for(int j = 0; j < N - i - 1; j ++) {
            if(array[j] < array[j+1]) {
				int temp = array[j+1];
				array[j+1] = array[j];
				array[j] = temp;
			}
		}
	}
}

nIntArray::nIntArray(void) {
	for(int i = 0; i < N; i ++)
		array[i] = 0;
	cout<<"初始化对象完毕\n";
}

void nIntArray::input(void) {
	cout<<"请您依次输入数组的"<<N<<"个元素：\n";
	for(int i = 0; i < N; i ++)
		cin>>array[i];
    cout<<"数组数据输入完毕\n";
}

void nIntArray::disp(void) {
    cout<<"您输入的数组元素为：\n";
	for(int i = 0; i < N; i ++)
		cout<<array[i]<<' ';
}

int nIntArray::max(int *p) {
	int copy[N];

	for(int i = 0; i < N; i ++)
		copy[i] = array[i];
    sort(copy);
	for(int cnt = 0; copy[cnt] == copy[0]; cnt ++);
	*p = cnt;

	return copy[0];
}

void nIntArray::find(void) {
	int copy[N];

	for(int i = 0; i < N; i ++)
		copy[i] = array[i];
    sort(copy);
	int *data = new int[N];
	int max = 0, counter = 0;
	for(i = 0; i < N; ) {
		for(int cnt = 0, j = i; copy[i] == copy[j] && i < N; cnt ++, i ++);
		if(cnt > max) {
			delete []data;
			int *data = new int[N];
			*(data ++) = copy[j];
			counter = 1;
			max = cnt;
		}
		else if(cnt == max) {
			*(++ data) = copy[j];
			counter ++;
		}
        else
			continue;
	}
	cout<<"重复次数最多的元素有：";
    while(counter --)
		cout<<*(data --)<<' ';
    cout<<"它们的重复次数是"<<max<<'\n';
}

int main(void) {
    cout<<"开始创建对象\n";
	nIntArray foo;
	foo.input();
	foo.disp();
	int bar;
	int baz = foo.max(&bar);
	cout<<"数组最大元素为"<<baz<<"出现了"<<bar<<"次\n";
    foo.find();

	return 0;
}