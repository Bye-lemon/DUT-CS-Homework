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
	cout<<"��ʼ���������\n";
}

void nIntArray::input(void) {
	cout<<"�����������������"<<N<<"��Ԫ�أ�\n";
	for(int i = 0; i < N; i ++)
		cin>>array[i];
    cout<<"���������������\n";
}

void nIntArray::disp(void) {
    cout<<"�����������Ԫ��Ϊ��\n";
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
	cout<<"�ظ���������Ԫ���У�";
    while(counter --)
		cout<<*(data --)<<' ';
    cout<<"���ǵ��ظ�������"<<max<<'\n';
}

int main(void) {
    cout<<"��ʼ��������\n";
	nIntArray foo;
	foo.input();
	foo.disp();
	int bar;
	int baz = foo.max(&bar);
	cout<<"�������Ԫ��Ϊ"<<baz<<"������"<<bar<<"��\n";
    foo.find();

	return 0;
}