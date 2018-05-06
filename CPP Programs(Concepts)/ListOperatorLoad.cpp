/*
ListOperatorLoad.cpp: This program to demonstrates the use of operator overloading and how to reverse and linked list.
Author: Ramakrishna Sayee Meka
*/

#include <iostream>

using namespace std;


class ThreeD {
public:
	int wid;
	int ht;
	int dep;
	//constructor: for object initialization
	ThreeD() { wid = ht = dep = 0; } //default constructor
	ThreeD(int i) { wid = ht = dep = i; }
	ThreeD(int i, int j, int k) { wid = i; ht = j; dep = k; }
	int vol() { return ht * wid*dep; }
	ThreeD operator+(ThreeD T);
	int operator*(ThreeD T);
	int & operator[](int k);  //return a reference to int
	ThreeD operator++(); //prefix ++t11
	ThreeD operator++(int never_used); //postfix t11++
};


ThreeD ThreeD::operator++(int never_used) { //postfix t11++
	ThreeD temp = *this;
	ht++;
	wid++;
	dep++;
	return temp;
}
ThreeD ThreeD::operator++() { //prefix
	++ht;
	++wid;
	++dep;
	return *this; //this is a pointer pointing to the current object
}

int & ThreeD::operator[](int k) {
	switch (k) {
	case 0: return ht;
	case 1: return wid;
	case 2: return dep;
	}

}

ThreeD ThreeD::operator+(ThreeD T)
{
	ThreeD temp;
	temp.ht = ht + T.ht;
	temp.wid = wid + T.wid;
	temp.dep = dep + T.dep;
	return temp;
}

int ThreeD::operator*(ThreeD T) {
	return vol() *T.vol();
}

class node {
public:
	int value;
	node * next;
	node() { next = nullptr; }
	node(int i) { value = i; next = nullptr; }
};


class linked_list {
public:
	int num_nodes;
	node * head;
	linked_list() { num_nodes = 0;  head = nullptr; }
	void create_linked_list(int k); //functionn prototype
	void create_random_linked_list(int k, int r);// create a linked list of k nodes
												 //with value between 0 and r-1
	void print_linked_list();
	void reverse();
};

void linked_list::reverse() {
	if (num_nodes <= 1) return;
	node *p1 = head, *p2 = p1->next, *p3;
	while (p2 != nullptr) {
		p3 = p2->next;
		p2->next = p1;
		if (p1 == head) p1->next = nullptr;
		p1 = p2;
		p2 = p3;
	}
	head = p1;
}

void linked_list::create_linked_list(int k) {
	for (int i = 0; i < k; i++) {
		node * p = new node(i); //node(k-1 -i) will reverse the list
		p->next = head;
		head = p;
		num_nodes++;
	}
}
void linked_list::create_random_linked_list(int k, int r) {

	for (int i = 0; i < k; i++) {
		node * p = new node(rand() % r);
		p->next = head;
		head = p;
	}

}


void linked_list::print_linked_list() {
	cout << endl;
	node * p = head;
	while (p != nullptr) {
		cout << p->value << " ";
		p = p->next;
	}
}



int main() {
	/* //(Uncoment the code and try running it)
	linked_list L1;
	L1.create_linked_list(10);
	L1.print_linked_list();

	L1.create_random_linked_list(20, 100);
	L1.print_linked_list();

	L1.reverse();
	L1.print_linked_list();
	*/

	// Operator overloading starts here..
	ThreeD t11(5), t12(7, 8, 9), t13;

	//Operator overloading
	t13 = t11 + t12;
	//t13 = t11.operator+(t12);

	//int k;
	//k = t11 * t12;

	cout << t11[2];
	t11[2] = 200;


	int w = 200;
	int & k = w;
	k = 5;

	cout << w << endl;


	ThreeD t15, t16;
	t15 = t11++;//postfix, unary operator
	t16 = ++t12; //prefix, unary operator
	t11++;

	getchar();
	getchar();
	return 0;
}