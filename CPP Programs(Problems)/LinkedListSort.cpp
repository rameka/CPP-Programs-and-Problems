/*
LinkedListSort.cpp: This program to demonstrates the sorting of singly linked list using insertion sort.
Author: Ramakrishna Sayee Meka
*/

#include <iostream>

using namespace std;

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
	void sort();
};

void linked_list::sort() {

// This sorting logic is based on finding the min term for each iteration and placing in appropriate place.
	if (num_nodes <= 1) return;
	node * p_min, *p1 = head, *p2;
	int min;
	while (p1 != nullptr) {
		p_min = p1;
		min = p1->value;
		p2 = p1;
		while (p2 != nullptr) {
			if (p2->value < min) { p_min = p2; min = p2->value; }
			p2 = p2->next;
		}
		p_min->value = p1->value;
		p1->value = min;
		p1 = p1->next;
	}
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
		num_nodes++;
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
	
	linked_list L3;
	L3.create_random_linked_list(30, 20);
	L3.print_linked_list();
	L3.sort();
	L3.print_linked_list();

	getchar();
	getchar();
	return 0;
}