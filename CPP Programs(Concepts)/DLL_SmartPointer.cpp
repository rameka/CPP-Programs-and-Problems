/*
DLL_SmartPointer.cpp: Demonstrates simple operations in doubly linked list using smart pointer(This code has no memory leak) .
Author: Ramakrishna Sayee Meka
*/

#include <iostream>
#include <memory>

using namespace std;

class node {
public:
	int value;
	shared_ptr<node> next; //default to empty
	//shared_ptr<node> previous; //default to empty
	//Using shared_ptr will lead to memory leak
	weak_ptr<node> previous
	node(int i) { value = i;  }
	node() { }
	~node(){cout << "Destructing"<< endl;}
};

class linked_list {
public:
	int num_nodes;
	shared_ptr<node> head;
	shared_ptr<node> tail;
	linked_list() { num_nodes = 0;  }
	linked_list(const initializer_list<int> &V);
	void push_back(int k);
	friend ostream & operator<<(ostream & stream, const linked_list &L);
};

void linked_list::push_back(int k) {
	shared_ptr<node> p = make_shared<node>(k);
	//p.reset(new int(k)); also works
	if (num_nodes == 0) {
		head = tail = p; num_nodes++; return;
	}
	p->previous = tail;
	tail->next = p;
	tail = p;
	num_nodes++;
}

linked_list::linked_list(const initializer_list<int> &V)  {
	num_nodes = 0;
	auto it1 = V.begin();
	while (it1 != V.end()) {
		push_back(*it1);
		it1++;
	}
}

ostream & operator<<(ostream & stream, const linked_list &L) {
	shared_ptr<node> p = L.head;
	while (p) {
		stream << p->value << " ";
		p = p->next;
	}
	return stream;
}


void f1(){
	linked_list L = { 1,2,3,4,5 };
	cout << L << endl;
}


int main() {
	f1();
	getchar();
	getchar();
	return 0;
}