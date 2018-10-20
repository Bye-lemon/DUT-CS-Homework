#include "iostream"
#include "string.h"

using namespace std;

class cString {
private:
	char *s;
public:
	cString(int length);
	void input(void);
	void exchange(void);
	void disp(void);
	friend int operator ==(const cString &x, const cString &y) {
		return !strcmp(x.s, y.s);
	};
};

cString::cString(int length) {
	s = new char[length];
	cout<<"A object build complete!\n";
}

void cString::input(void) {
	cout<<"Please input a string:";
	cin>>s;
}

void cString::exchange(void) {
	char max = *s;
	char min = *s;
	for(int i = 0; *(s+i) != '\0'; i ++) {
		min = (*(s+i) < min)? *(s+i): min;
		max = (*(s+i) > min)? *(s+i): max;
	}
	for(i = 0; *(s+i) != '\0'; i ++)
		*(s+i) = (*(s+i) == min)? max: (*(s+i) == max)? min: *(s+i);
}

void cString::disp(void) {
	cout<<s<<'\n';
}

int main(void) {
	cString str1(10);
	str1.input();
	cout<<"String 1 is ";
	str1.disp();
	cString str2(10);
	str2.input();
	cout<<"String 2 is ";
	str2.disp();
	if(str1 == str2)
		cout<<"They are the same.\n";
	else
		cout<<"They are different!\n";
	cout<<"Now exchange String2, then display it.\n";
	str2.exchange();
	str2.disp();

	return 0;
}
