/* DoubleLinkedListOperations.cpp : Performing operations on doubly linked list like sorting values based on links(not values itself), reversing
 printing, removing, inserting.
 Author: Ramakrishna Sayee Meka, Syracuse University
 */

#include <iostream>
using namespace std;

class node {
public:
	int value;
	node * next;
	node * previous;
	node() { next = previous = nullptr; }
	node(int k) { value = k; next = previous = nullptr; }
};

class linked_list {
public:
	node * head;
	node * tail;
	linked_list() { head = tail = nullptr; }
	void make_random_list(int k, int m);//create a linked list of 
										//k nodes with values in 0 ..m-1 randomly
	void print_forward(); //Print values of all nodes from head node
	void print_reverse(); //Print values of all nodes reversely from tail node
	void reverse(); //Reverse the order of nodes of linked list				
	void sort(); //Sort the nodes, based on ascending order of node values

	void insert(int k); //Create a new node with values k, and properly add it to an already sorted list
						//After the insertion, the entire linked list is still sorted.
						//You are not allowed to invoke the function sort()

	void remove_all(int k); //Remove all nodes whose node values are equal to k

};
void linked_list::make_random_list(int k, int m) { //create linked list of k nodes with
												   //values randomly in 0 ... m-1
	node * p;
	for (int i = 0; i < k; i++) {
		p = new node(rand() % m);
		p->next = head;
		if (head == nullptr) {
			tail = p; head = p;
		}
		else {
			head->previous = p;
			head = p;
		}
	}
}

void linked_list::print_forward() {
	node * p = head;
	cout << endl;
	while (p != nullptr) {
		cout << p->value << " ";
		p = p->next;
	}
}

void linked_list::print_reverse() {
	node * p = tail;
	cout << endl;
	while (p != nullptr) {
		cout << p->value << " ";
		p = p->previous;
	}
}

void linked_list::reverse() {
	node * temp = head, *swapRef;

	// If there are no elements to reverse and there is only one element in the list, no need to reverse
	if (head == tail) {
		return;
	}
	//just swapping the next and previous of each node will reverse the list
	while (temp!=nullptr){
		if (temp->previous == nullptr) {
			tail = temp;
		}
		if (temp->next == nullptr) {
			head = temp;
		}
		swapRef = temp->previous;
		temp->previous = temp->next;
		temp->next = swapRef;
		temp = temp->previous;
	}

}
void linked_list::sort() {
	node *temp1,*temp2;
	int tempVal;
	if (head == nullptr||head==tail)
		return;
	for (node *i = head;i->next!=nullptr; i = i->next) {
		
		for (node *j = i->next; j != nullptr; j = j->next) {
			
			if (i->value > j->value) {
				//if the two nodes are adjacent

				if (j == i->next) {
					//six links has to be changed
					temp1 = i->previous;
					if (i->previous != nullptr) {
						i->previous->next = j;
					}
					if (j->next!=nullptr) {
						j->next->previous = i;
					}
					i->next = j->next;
					i->previous = j;
					j->previous = temp1;
					j->next = i;
					i = i->previous;
					j = j->next;
				}
				//two nodes are non adjacent
				else
				{
					i->previous != nullptr ? i->previous->next = j : head = j;
					j->next != nullptr ? j->next->previous = i : tail = i;

					temp1 = i->previous;
					temp2 = i->next;
					i->previous = j->previous;
					j->previous->next = i;
					i->next->previous = j;
					j->previous = temp1;
					i->next = j->next;
					j->next = temp2;
					//Swapping i and j pointers
					temp1 = i;
					i = j;
					j = temp1;
				}
	
			}
	
		}

	}
	
}
void linked_list::insert(int k) {
	node * temp = head;
	node *p = new node(k);//creating node
	// If the linked list is empty
	if (head==nullptr && tail == nullptr) {
		head = (tail = p);
		return;
	}
	// Inserting at the beginning
	if (k < head->value) {
		p->previous = head->previous;
		p->next = head;
		head->previous = p;
		head = p;
		return;
	}
	// Inserting in the middle
	while (temp->next!= nullptr) {
		if (k>=temp->value && k<temp->next->value) {
			p->previous = temp;
			p->next = temp->next;
			temp->next->previous = p;
			temp->next = p;
			return;
		}
		temp = temp->next;
	}
	//Inserting at the end
	if (temp->next == nullptr) {
		p->previous = temp;
		temp->next = p;
		tail = p;
		return;
	}
	
	
}
void linked_list::remove_all(int k) {
	node *temp = head;
	node *delNode;
	if (head == nullptr){
		return;
	}
	if (head == tail && head->value == k) {
		delNode = head;
		head = tail = nullptr;
		delete delNode;
		return;
	}
	while (temp!=nullptr){
		//deleting values when they match
		if (temp->value == k) {
			delNode = temp;
			//deleting from the begnning of the list
			if (temp->previous == nullptr) {
				temp->next->previous = head->previous;
				head = temp->next;
				temp = temp->next;
				delete delNode;
				continue;
			}
			//deleting from the end of the list
			if (temp->next==nullptr) {
				temp->previous->next = nullptr;
				delete delNode;
				return;
			}
			temp->previous->next = temp->next;
			temp->next->previous = temp->previous;
			temp = temp->next;
			delete delNode;
			continue;
		}
		temp = temp->next;
	}
}

int main() {

	linked_list L1;
	L1.make_random_list(60, 15);
	L1.print_forward();
	L1.print_reverse();
	L1.reverse();
	L1.print_forward();
	L1.print_reverse();
	L1.remove_all(11);
	L1.print_forward();
	L1.print_reverse();
	L1.sort();
	L1.print_forward();
	L1.print_reverse();
	L1.insert(0);
	L1.insert(10);
	L1.insert(16);
	L1.print_forward();
	L1.print_reverse();
	getchar();
	getchar();
	return 0;
}


