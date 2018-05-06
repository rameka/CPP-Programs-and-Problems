/*
LinkedListIntro.cpp: This is a program on creating and printing a linked list, also introduces to dynmic memory allocation by using pointers with Linked List.
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
};

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
	void create_linked_list(int k) {
		for (int i = 0; i < k; i++) {
			node * p = new node(i);
			p->next = head;
			head = p;
		}
	}
	void print_linked_list();
};

void linked_list::print_linked_list() {
	node * p = head;
	while (p != nullptr) {
		cout << p->value << " ";
		p = p->next;
	}
}



int main() {
	/*
	//(Uncomment the code and try running it)
	//Dynamic memory allocation

	int w = 10; //static allocation
	int * p1 = &w;
	int * p2 = new int(20);
	//the function new asks system to allocate a storage space
	//for int and returns the address of the storage space
	*p2 = 35;
	delete p2; //*p2 is deleted, but not p2
	cout << *p2 << endl;
	p2 = new int;

	int * C; //Let's create an array
	C = new int[25];
	delete[] C;

	//select ->

	ThreeD t1, t2(5), t3(3, 4, 5);

	cout << t1.ht << " " << t1.wid << " " << t1.dep << endl;
	//cin >> t1.ht >> t1.wid >> t1.dep;

	ThreeD * p5 = new ThreeD(55, 66, 77);
	cout << (*p5).ht << "  " << (*p5).wid << " " << (*p5).dep << endl;
	cout << p5->ht << "  " << p5->wid << "  " << p5->dep << endl;
	//careful using '*', '.', and '->'
	

	//Intro to linked list
	node n1(5), n2(6), n3(7);
	node * h1;
	h1 = &n1;
	n1.next = &n2;
	n2.next = &n3;

	node * p1 = h1;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->next;  //the same as p1 = (*p1).next;
	}
	*/


	linked_list L1;
	L1.create_linked_list(10);
	L1.print_linked_list();

	getchar();
	getchar();
	return 0;
}