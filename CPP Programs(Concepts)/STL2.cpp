/*
STL2.cpp: This program illustrates the use of other STL's like queue, sstack, set and multiset. It also introduces templates.
Author: Ramakrishna Sayee Meka
*/

#include <iostream>
#include <stack> //LIFO
#include <queue> //FIFO
#include <set>
#include <map>
#include <string>

using namespace std;

template <class T> class ThreeD {//generic ThreeD class
public:
	T wid;
	T ht;
	T dep;
	ThreeD() { wid = ht = dep = (T)0; }
	ThreeD(T i, T j, T k) { wid = i; ht = j; dep = k; }
	T vol();

};

template <class T> T ThreeD<T>::vol() { return wid * ht * dep; }

class threeD {
public:
	int ht;
	int wid;
	int dep;
	threeD() { ht = wid = dep = 0; }
	threeD(int i, int j, int k) { ht = i; wid = j; dep = k; }

	//The following operator< is required for map to sort data
	//Note that the key word const is used in several places
	//The first const describes that T should not be modified by the funciton
	//and the second const describes that data of the current object should not be modified
	bool operator<(const threeD T) const { return ht*wid*dep < T.ht * T.wid * T.dep; }

};



int main() {
	/*
	ThreeD<int> t1(3,4,5);
	cout << t1.vol() << endl;
	ThreeD<double> t2(2.2, 3.3, 4.4);
	cout << t2.vol() << endl;
	*/
	stack<int> s;
	s.push(5);
	s.push(3);
	s.push(2);
	s.push(1);
	cout << s.top();//One can only access the top element of the stack
					//in this case, it will be value 1;
	s.pop();//remove the element on top of stack

	queue<int> q;
	q.push(5);
	q.push(3);
	q.push(2);
	q.push(1);
	cout << q.front();
	q.pop();

	cout << endl;
	map<int, string> m1;
	m1[4] = "Dave";
	m1[6] = "Pete";
	m1[4] = "Pat";

	map<int, string>::iterator it1 = m1.begin();
	while (it1 != m1.end()) {
		cout << it1->first << " " << it1->second << " ";
		it1++;
	}
	cout << endl;
	multimap<int, string> m4;  //multimap allow multiple data with the same key value, such as 4
	//m1[4] = "Dave"; //You cannot input data to multimap in this way
	//m1[6] = "Pete";
	//m1[4] = "Pat";
	//You need to input data to multimap in the following ways
	m4.insert(pair<int, string>(4, "Dave"));
	m4.insert(pair<int, string>(6, "Pete"));
	m4.insert(pair<int, string>(4, "Pat"));

	multimap<int, string>::iterator it13 = m4.begin();
	while (it13 != m4.end()) {
		cout << it13->first << " " << it13->second << " ";
		it13++;
	}
	cout << endl;



	threeD t5(3, 4, 5), t6(10, 20, 30), t7(50, 60, 70);

	map<threeD, string> m3;

	m3[t6] = " medium object";
	m3[t7] = " larage object";
	m3[t5] = "Small Oject";
	map<threeD, string>::iterator it2 = m3.begin();
	while (it2 != m3.end()) {
		cout << " " << it2->second << " ";
		it2++;
	}

	set<int> s1;
	s1.insert(5);
	s1.insert(3);
	s1.insert(6);
	s1.insert(5);
	multiset<int>::iterator it10 = s1.begin();
	while (it10 != s1.end()) {
		cout << *it10 << " ";
		it10++;
	}
	multiset<int> s2;  //allow multiple occurrances of the same value
	s2.insert(5);
	s2.insert(3);
	s2.insert(6);
	s2.insert(5);
	set<int>::iterator it11 = s2.begin();
	while (it11 != s2.end()) {
		cout << *it11 << " ";
		it11++;
	}

	getchar();
	getchar();
	return 0;


}