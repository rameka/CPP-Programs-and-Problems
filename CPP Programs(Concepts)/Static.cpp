/*
Static.cpp: Illustrates how to use static with class in c++.
Author: Ramakrishna Sayee Meka
*/


#include <iostream>
using namespace std;

class c {
	static int num_objects;//You need to initialize static data member in this way


public:
	c() { num_objects++; }
	static int get_num_objects() { return num_objects; }
};
int c::num_objects = 0;

int fun1(int &i) {
	static int num_calls = 1; //persistent local variable;
							  //static variable will only be initialized once.
							  //"Persistent" means that when a function ends, the variable still keeps its value.


	cout << i*i << " ";
	return num_calls++;
}

int main() {
	int k = 5;
	cout << fun1(k) << endl;
	cout << fun1(k) << endl;
	cout << fun1(k) << endl;
	cout << endl;

	c c1, c2, c3;
	//c1.func();
	cout << c::get_num_objects();//static member function and static data member belong to the class
								 //not "object"

								 //cout << c::get_num_objects << endl;
								 //cout << c1.mum_objects << endl;  will give you error.

	getchar();
	getchar();
	return 0;

}