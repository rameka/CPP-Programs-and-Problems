/*
IO_Overload_Template.cpp: This program elobrates on how to overload input and output operator, with templates.
Author: Ramakrishna Sayee Meka
*/

#include <iostream>

using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD(int i, int j, int k) { ht = i; wid = j; dep = k; }
	int vol() { return ht*wid* dep; }
	friend ostream & operator<<(ostream &stream, const ThreeD &T);
	friend istream & operator>>(istream & stream, ThreeD &T);
	//friend allows external funciton to access all members of this class
};

class ThreeD_2 {
public:
	double ht;
	double wid;
	double dep;
	ThreeD_2(double i, double j, double  k) { ht = i; wid = j; dep = k; }
	double vol() { return ht * wid* dep; }

};

template <class T> class ThreeD_3{
public:
	T ht;
	T wid;
	T dep;
	ThreeD_3(T i, T j, T  k) { ht = i; wid = j; dep = k; }
	T vol() { return ht * wid* dep; }
	T area();
	template <class U> 
	friend ostream & operator<<(ostream &stream, const ThreeD_3<U> &T1);

};
template <class T> T ThreeD_3<T>::area() {
	return ht * wid*dep;
}


class node {
public:
	int value;
	node * next;
	node(int i) { value = i; next = nullptr; }
	node() { next = nullptr; }
};
class linked_list {
public:
	node * head;
	linked_list() { head = nullptr; }
	void make_random_list(int c, int n) {
		for (int i = 0; i < n; i++) {
			node * p = new node(rand() % c);
			p->next = head;
			head = p;
		}
	}

	friend ostream & operator<<(ostream &stream, const linked_list & L);
};

template <class U> ostream & operator<<(ostream &stream, const ThreeD_3<U> &T1) {
	stream << "( " << T1.ht << ", " << T1.wid << ", " << T1.dep << " )";
	return stream;
}

ostream & operator<<(ostream &stream, const linked_list & L) {
	node * p = L.head;
	while (p != nullptr) {
		stream << p->value << " ";
		p = p->next;
	}
	return stream;
}

ostream & operator<<(ostream &stream, const ThreeD &T) {
	stream << "( " << T.ht << ", " << T.wid << ", " << T.dep << " )";
	return stream;
}
istream & operator>>(istream & stream, ThreeD &T) {
	stream >> T.ht >> T.wid >> T.dep;
	return stream;
}

template <class X, class Y> void func1(X i, Y j) {
	X k;
	k = i * i;
	Y w = j;
	cout << j << end;

}



int main() {
	/*
	ThreeD T1(3, 4, 5);
	cout << T1 << endl;;

	cout << "Enter values for T1" << endl;
	cin >> T1;
	cout << T1;
	linked_list L1;
	L1.make_random_list(10, 20);
	cout << L1 << endl;
	*/

	//template

	ThreeD T11(3, 4, 5);
	ThreeD_2 T12(3.3, 4.4, 5.5);
	ThreeD_3<int> T13(5, 6, 7);
	ThreeD_3<double> T14(5.5, 6.6, 7.7);
	cout << T14 << endl;


	getchar();
	getchar();
	return 0;

}