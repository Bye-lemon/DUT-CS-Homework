#include "iostream"
#include "string.h"
#define N 10
#define LENGTH 100

using namespace std;

class nString {
private:
	char string[N][LENGTH];
public:
	nString(void);
	nString(const nString &another);
	nString(char str[N][LENGTH]);
	void setAString(int index);
	void dispAString(int index);
	char findMinASCIIChar(int index, int *p);
	void sort(void);
	void dispAllString(void) {
		for(int i = 0; i < N; i ++)
			dispAString(i);
	}
	void setAllString(void) {
		for(int i = 0; i < N; i ++)
			setAString(i);
	}
};

nString::nString(void) {
	for(int i = 0; i < N; i ++)
		strcpy(string[i], "\0");
}

nString::nString(const nString &another) {
	for(int i = 0; i < N; i ++)
		strcpy(string[i], another.string[i]);
}

nString::nString(char str[N][LENGTH]) {
	for(int i = 0; i < N; i ++)
		strcpy(string[i], str[i]);
}

void nString::setAString(int index) {
	cout<<"Please input the "<<index+1<<"th string:";
	cin>>string[index];
}

void nString::dispAString(int index) {
	cout<<string[index]<<'\n';
}

char nString::findMinASCIIChar(int index, int *p) {
	char min = string[index][0];
	for(int i = 0; string[index][i] != '\0'; i ++)
		min = (string[index][i] < min)? string[index][i]: min;
	for(i = 0; string[index][i] != '\0'; i ++)
		*p += (string[index][i] == min)? 1: 0;
	
	return min;
}

void nString::sort(void) {
	char p[LENGTH];
	for(int i = 0; i < N; i ++) {
		for(int j = 0; j < N-i-1; j ++) {
			if(strcmp(string[j], string[j+1]) > 0) {
				strcpy(p, string[j+1]);
				strcpy(string[j+1], string[j]);
				strcpy(string[j], p);
			}
		}
	}
}

int main(void) {
	char str[N][LENGTH] = {
		"Hello,world!",
		"Hello,programing!",
		"Hello,C-family Language!",
		"Hello,Bell Labs!",
		"Hello,Bjarne Stroustrup!",
		"Hello,C++!",
		"Hello,Microsoft!",
		"Hello,VC6.0!",
		"Hello,nString!",
		"Goodbye all above!"
	};

	nString ob1;
	cout<<"Object 1 construct complete."<<'\n';
	cout<<"Object 1 is empty, now display it."<<'\n';
	ob1.dispAllString();
	cout<<"Set a string, for example the third string."<<'\n';
	ob1.setAString(2);
	cout<<"Copy Object 1 to build Object 2."<<'\n';
	nString ob2(ob1);
	cout<<"Object 2 construct complete."<<'\n';
	cout<<"Object 2's third string is tha same as Object 1's, now display it."<<'\n';
	ob2.dispAString(2);
	cout<<"Convert an array to Object 3."<<'\n';
	nString ob3 = str;
	cout<<"Object 2 construct complete."<<'\n';
	cout<<"Now display Object 3."<<'\n';
	ob3.dispAllString();
	int num = 0;
	char min = ob3.findMinASCIIChar(0, &num);
	cout<<"In Object 3's first string, the min character is "<<min<<'\n';
	cout<<"There are "<<num<<' '<<min<<" in this string\n";
	cout<<"Now sort Object 3, then display it.\n";
	ob3.sort();
	ob3.dispAllString();

	return 0;
}
