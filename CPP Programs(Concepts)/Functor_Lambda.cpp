/*
Functor_Lambda.cpp: This program introduces functors and elobrates on lambdas.
Author: Ramakrishna Sayee Meka
*/

//for_each, functor, lambda
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>//for each

using namespace std;

class X {
public:
	int j;
	X() {}
	X(int k) : j(k) {}//X(int k) { j = k;}
	void operator()(int i) { cout << j + i << endl; };
};

class ThreeD {
	int ht;
	int wid;
	int dep;
	ThreeD(int i, int j, int k) { ht = i; wid = j; dep = k; }
};


class Y {
public:
	int operator()(int i) { return i * i; }
};


void add3(int &i) { i += 3; }

int main() {
	list<int> L1 = { 1, 2, 3, 4, 5 };
	int s = 7;
	for_each(L1.begin(), L1.end(), [&s](int i) { s += i;  });//[ ...)
	
	//for_each(L1.begin(), L1.end(),add3);
	X f(s);
	f(6);
	cout << s << endl;
	cout << *(L1.begin());//4 if add3 in invoked

	auto f5 = []() {};

	int i = 5;
	int j = 10;
	int k = 40;

	auto LF1 = [i, &j, &k](int c, int d) -> int {
		return i + j + k + c + d;
	};

	X f10(5);
	f10(7);
	cout << LF1(20, 30) << endl;
	Y y;
	X x1;
	cout << y(25);
	vector<int> V11 = { 2, 4, 11, 5, 77,8,9 };
	for_each(V11.begin(), V11.end(), [](int &i) {i += 5; });
	cout << endl;
	for (size_t i = 0; i < V11.size(); i++) cout << V11[i] << " ";

	int Array1[6] = { 1,2,3,4,5,6 };

	for_each(Array1, Array1 + 6, add3);
	
	getchar();
	getchar();
	return 0;

}