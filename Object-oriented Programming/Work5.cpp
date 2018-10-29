#include"iostream"
#include"string.h"
#include"stdlib.h"

using namespace std;

typedef struct _Student {
	char name[20];
	unsigned int id;
	char gender; //Male is marked as 'M'; Female is marked as 'F' 
	char birth[11]; //Like "1970/01/01"
	int grade[3];
	int final; //Sum of grades
} Student;

class Link {
private:
	friend class List;
	Student info;
	Link *next;
public:
	Link(void);
	Link(
		char name[], int id, char gender, char birth[], 
		int grade1, int grade2, int grade3
		);
	void disp(void);
};

class List {
private:
	int size;
protected:
	Link* head;
	Link* ptr;
public:
	List(void);
	void nodeAppend(Link* node);
	void nodeSearch(char name[]);
	void nodeSearch(int id);
	void nodeDelete(char name[]);
	void nodeDelete(int id);
	void disp(void);
	void nodeCount(void);
	void estNodeFind(void);
	void sort(void);
};

Link::Link(void) {
	next = NULL;
	cout<<"Empty Link Construct Complete\n";
}

Link::Link(char name[], int id, char gender, char birth[], 
		   int grade1, int grade2, int grade3) {
	strcpy(info.name, name);
	info.id = id;
	info.gender = gender;
	strcpy(info.birth, birth);
	info.grade[0] = grade1;
	info.grade[1] = grade2;
	info.grade[2] = grade3;
	info.final = grade1 + grade2 + grade3;
	next = NULL;
	cout<<"Construction Complete\n";
}

void Link::disp(void) {
	cout<<"Name: "<<info.name<<'\n';
	cout<<"StudentID: "<<info.id<<'\n';
	cout<<"Gender: "<<info.gender<<'\n';
	cout<<"Birthday: "<<info.birth<<'\n';
	cout<<"Grades: "<<info.grade[0]<<' '<<info.grade[1]<<' '<<info.grade[2]<<'\n';
	cout<<"Sum: "<<info.final<<'\n';
}

List::List(void) {
	head = ptr = new Link;
	cout<<"LinkList Construct Complete\n";
}

void List::disp(void) {
	Link* p = head->next;
	while(p != NULL) {
		p->disp();
		cout<<'\n';
		p = p->next;
	}
}

void List::nodeCount(void) {
	size = 0;
	Link* p = head->next;
	while(p != NULL) {
		size ++;
		p = p->next;
	}
	cout<<size<<" Node in All\n";
}

void List::nodeAppend(Link* node) {
	ptr->next = node;
	ptr = node;
	cout<<"Student "<<ptr->info.name<<" Added\n";
}

void List::nodeSearch(char name[]) {
	Link* p = head;
	while(p != NULL) {
		if(!strcmp(p->info.name, name)) {
			p->disp();
			return ;
		}
		p = p->next;
	}
	cout<<"Student "<<name<<" Not Found\n";
}

void List::nodeSearch(int id) {
	Link* p = head;
	while(p != NULL) {
		if(p->info.id == id) {
			p->disp();
			return ;
		}
		p = p->next;
	}
	cout<<"Student "<<id<<" Not Found\n";
}

void List::nodeDelete(char name[]) {
	Link* p = head;
	Link* temp;
	while(p->next != NULL) {
		if(!strcmp(p->next->info.name, name)) {
			temp = p->next;
			p->next = p->next->next;
			if(temp == ptr)
				ptr = p;
			cout<<"Student "<<name<<" Delete\n";
			return ;
		}
		p = p->next;
	}
	cout<<"Student "<<name<<" Not Found\n";
}

void List::nodeDelete(int id) {
	Link* p = head;
	Link* temp;
	while(p->next != NULL) {
		if(p->next->info.id == id) {
			temp = p->next;
			p->next = p->next->next;
			if(temp == ptr)
				ptr = p;
			cout<<"Student "<<id<<" Delete\n";
			return ;
		}
		p = p->next;
	}
	cout<<"Student "<<id<<" Not Found\n";
}

void List::estNodeFind(void) {
	Link* p = head->next;
	int max = 0, min = 300;
	while(p != NULL) {
		max = (p->info.final > max)? p->info.final: max;
		min = (p->info.final < min)? p->info.final: min;
		p = p->next;
	}
	p = head->next;
	cout<<"Student with the Highest Score is as Follow:\n";
	while(p != NULL) {
		if(p->info.final == max) 
			p->disp();
		p = p->next;
	}
	p = head->next;
	cout<<"Student with the lowest Score is as Follow:\n";
	while(p != NULL) {
		if(p->info.final == min) 
			p->disp();
		p = p->next;
	}
}

void List::sort(void) {
	Link* p = head->next;
	this->nodeCount();
	cout<<"Now sorted it ......\n";
	for(int i = 0; i < size - 1; i ++, p = head->next) {
		for(int j = 0; j < size - i - 1; j ++, p = p->next) {
			if(p->info.final < p->next->info.final) {
				char str20[20], str10[10], str;
				int temp;
				strcpy(str20, p->next->info.name);
				strcpy(p->next->info.name, p->info.name);
				strcpy(p->info.name, str20);
				strcpy(str10, p->next->info.birth);
				strcpy(p->next->info.birth, p->info.birth);
				strcpy(p->info.birth, str10);
				str = p->next->info.gender;
				p->next->info.gender = p->info.gender;
				p->info.gender = str;
				temp = p->next->info.id;
				p->next->info.id = p->info.id;
				p->info.id = temp;
				temp = p->next->info.final;
				p->next->info.final = p->info.final;
				p->info.final = temp;
				for(int cnt = 0; cnt <3; cnt ++) {
					temp = p->next->info.grade[cnt];
					p->next->info.grade[cnt] = p->info.grade[cnt];
					p->info.grade[cnt] = temp;
				}
			}
		}
	}
	this->disp();
}

void Init(void) {
	cout<<"************ Student Information Management System Based on LinkList ************\n\n";
	cout<<"                    1. Insert Student Information\n";
	cout<<"                    2. Search Student Information\n";
	cout<<"                    3. Delete Student Information\n";
	cout<<"                    4. Display Student Information\n";
	cout<<"                    5. Show the Highest and Lowest\n";
	cout<<"                    6. Sort Student Information\n\n";
	cout<<"                    Q. Quit\n\n";
	cout<<"*********************************************************************************\n";
}

int main(void) {
	List list;

	while(1) {
		system("cls");
		Init();
		char choice;
		cout<<"Input Your Choice: ";
		cin>>choice;
		switch(choice) {
			case '1':
				system("cls");
				Student foo;
				cout<<"Enter student's name: ";
				cin>>foo.name;
				cout<<"Enter student's id(limited in 0 ~ 65536): ";
				cin>>foo.id;
				cout<<"Enter student's gender('F' or 'M'): ";
				cin>>foo.gender;
				cout<<"Enter student's birthday(like \"1970/01/01\"): ";
				cin>>foo.birth;
				cout<<"Enter student's grade: ";
				cin>>foo.grade[0]>>foo.grade[1]>>foo.grade[2];
				Link* link;
				link = new Link(foo.name, foo.id, foo.gender, foo.birth, foo.grade[0], foo.grade[1], foo.grade[2]);
				list.nodeAppend(link);
				break;
			case '2':
				system("cls");
				cout<<"Indexed by name or ID(1 for name and 0 for id):";
				int bar;
				cin>>bar;
				if(bar) {
					cout<<"Enter a name:";
					char name[20];
					cin>>name;
					list.nodeSearch(name);
				} else {
					cout<<"Enter an ID:";
					int id;
					cin>>id;
					list.nodeSearch(id);
				}
				break;
			case '3':
				system("cls");
				cout<<"Indexed by name or ID(1 for name and 0 for id):";
				int baz;
				cin>>baz;
				if(baz) {
					cout<<"Enter a name:";
					char name[20];
					cin>>name;
					list.nodeDelete(name);
				} else {
					cout<<"Enter an ID:";
					int id;
					cin>>id;
					list.nodeDelete(id);
				}
				break;
			case '4':
				system("cls");
				list.disp();
				break;
			case '5':
				system("cls");
				list.estNodeFind();
				break;
			case '6':
				system("cls");
				list.sort();
				break;
			case 'q':
			case 'Q':
				return 0;
				break;
			default:
				break;
		}
		system("pause");
	}
	
	return 0;
}
