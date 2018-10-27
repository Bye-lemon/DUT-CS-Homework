#include"iostream"
#include"string.h"
#include"stdlib.h"

using namespace std;

typedef struct _Student {
	char name[20];
	unsigned int id; //Student id limited in 0 ~ 65536
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

int main(void) {
	List list;

/*	Link link1("Li Yingping", 12345, 'M', "1999/05/03", 99, 99, 99);
	Link link2("Xie Haixiang", 24680, 'M', "1998/06/04", 100, 98, 97);
	Link link3("Temp", 33333, 'M', "1997/07/05", 10, 90, 90);

	list.nodeAppend(&link1);
	list.nodeAppend(&link2);
	list.nodeAppend(&link3);*/
/*	Student foo;

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
	Link link(foo.name, foo.id, foo.gender, foo.birth, foo.grade[0], foo.grade[1], foo.grade[2]);
	link.disp();
	list.nodeAppend(&link);*/
	list.disp();
	list.nodeCount();
	list.estNodeFind();
	list.nodeSearch("Li Yingping");
	list.nodeSearch(24680);
	list.nodeDelete("Temp");
	list.disp();

	return 0;
}

void Init(void) {
	cout<<"************基于链表的学生信息管理系统************\n";
	cout<<"                1. 录入学生信息\n";
	cout<<"                2. 查找学生信息\n";
	cout<<"                3. 删除学生信息\n";
	cout<<"                4. 显示学生信息\n";
	cout<<"                5. 显示最高分和最低分同学信息\n";
	cout<<"                6. 退出系统\n";
}

int main(void) {
	Link list;

	while(1) {
		system("cls");
		Init();
		int choice;
		switch(choice) {
		case 1:
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
			Link link(foo.name, foo.id, foo.gender, foo.birth, foo.grade[0], foo.grade[1], foo.grade[2]);
			link.disp();
			list.nodeAppend(&link);

			break;
		case 2:
			cout<<"Indexed by name or ID(1 for name and 0 for id):";
			int foo;
			cin>>foo;
			if(foo){
				cout<<"Enter a name:";
				char name[20];
