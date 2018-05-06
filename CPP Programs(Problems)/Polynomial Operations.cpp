/*
 * Polynomial Operations.cpp : This program adds terms to the polynomial and performs operations like
 *							   polynomial addition and multiplication
 * Author: Ramakrishna Sayee Meka, Syracuse University
 */


#include <iostream>

using namespace std;

// Structure for the term in the polynomial expression
class term {
public:
	int power;
	int coef;
	term * next;
	term() { next = nullptr; }
	term(int c, int p) { power = p; coef = c; next = nullptr; }
};


class polynomial {
public:
	int num_terms;
	term * head;
	polynomial() { num_terms = 0; head = nullptr; }

	void add_term(int c, int p);
	//If the polynomial does not contain a term with power p, 
	//then add this new term.
	//If the polynomial contains a term with power p,
	//then add c to the existing coef.

	polynomial operator+(polynomial P);
	polynomial operator*(polynomial P);
	void print_polynomial();
};

// Displaying terms in the polynomial
void polynomial::print_polynomial() {
	cout << endl;
	term * p = head;
	while (p != nullptr) {
		cout << p->coef << " " << p->power << "   ";
		p = p->next;
	}
}

// Adds terms to the polynomial when an input is given
void polynomial::add_term(int c, int p) {

	if (c == 0) { return; }
	
	term * node, *temp, *del;
	temp = head;
	node = new term(c, p);
	
	//Checking and updating whether first element has the same power as new node
	if (head!=nullptr && temp->power == p) {
		if (temp->coef + node->coef != 0) {
			temp->coef = temp->coef + node->coef;
		}
		else {
			del = temp;
			head = temp->next;
			free(del);
		}
	}
	//checking and updating whether any other element has the same power as the new node
	else if(head!=nullptr){
		temp = head;

		while (temp->next != nullptr) {
			if (temp->next->power == node->power) {
				if (temp->next->coef + node->coef != 0) {
					temp->next->coef = temp->next->coef + node->coef;
				}
				else {
					del = temp->next;
					temp->next = temp->next->next;
					delete del;
					num_terms--;
				}
				return;
			}
			temp = temp->next;
		}
	}


	//Inseting a term in a sorted way in terms of power when there is no element in a list and when elements are present, except when powers
	//of new node to be added and existing node are equal.
	if ((head == nullptr || head->power < node->power))
	{
		node->next = head;
		head = node;
		num_terms++;
	}
	else
	{
		term *current = head;
		while (current->next != nullptr &&
			current->next->power > node->power)
		{
			current = current->next;
		}
		node->next = current->next;
		current->next = node;
		num_terms++;
	}
	
}

// Polynomial Addition
polynomial polynomial::operator+(polynomial P) {
	polynomial temp_p;
	term * p1 = head, *p2 = P.head;
	while (p1 != nullptr || p2 != nullptr) {
		if (p1 == nullptr) { temp_p.add_term(p2->coef, p2->power); p2 = p2->next; }
		else if (p2 == nullptr) { temp_p.add_term(p1->coef, p1->power); p1 = p1->next; }
		else if (p1->power < p2->power) { temp_p.add_term(p2->coef, p2->power); p2 = p2->next; }
		else if (p1->power > p2->power) { temp_p.add_term(p1->coef, p1->power); p1 = p1->next; }
		else if (p1->power == p2->power) {
			if ((p1->coef + p2->coef) != 0) {
				temp_p.add_term(p1->coef + p2->coef, p1->power);
			}
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	return temp_p;
}

// Polynomial multiplication
polynomial polynomial::operator*(polynomial P) {
	polynomial tempPoly;

	//Multiplying terms and storing in new list
	for (term *i = head; i != nullptr; i = i->next) {
		for (term *j = P.head; j!=nullptr; j=j->next){
			tempPoly.add_term((i->coef) * (j->coef), i->power + j->power);
		}
	}
	return tempPoly;
}


int main() {
	polynomial P1, P2, P3;

	P1.add_term(3, 4);
	P1.add_term(7, 2);
	P1.add_term(6, 0);
	P1.add_term(-3, 3);
	P1.add_term(-5, 6);

	P2.add_term(5, 6);
	P2.add_term(-2, 3);
	P2.add_term(-3, 4);
	P2.add_term(1, 2);
	P2.add_term(3, 5);

	P3 = P1 + P2;
	
	P3.print_polynomial();
	getchar();
	getchar();
	return 0;
}


