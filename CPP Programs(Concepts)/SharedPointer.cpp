/*
SharedPointer.cpp: Shared pointer functions - reset, swap.
Author: Ramakrishna Sayee Meka
*/


#include <iostream>
#include <memory>


using namespace std;
int main() {
	shared_ptr<int> sp;  // empty
	if (!sp) cout << "it is empty" << endl;

	sp.reset(new int);       // takes ownership of pointer
	*sp = 10;
	cout << *sp << '\n';

	sp.reset(new int);       // deletes managed object, acquires new pointer
	*sp = 20;
	cout << *sp << '\n';

	sp.reset();               // deletes managed object




	int* p = new int(10);
	shared_ptr<int> a(p);

	if (a.get() == p)
		cout << "a and p point to the same location\n";

	// three ways of accessing the same address:
	cout << *a.get() << "\n";
	cout << *a << "\n";
	cout << *p << "\n";



  	shared_ptr<int> foo (new int(10));
  	shared_ptr<int> bar (new int(20));

  	foo.swap(bar);

  	cout << "*foo: " << *foo << '\n';
  	cout << "*bar: " << *bar << '\n';

	getchar();
	return 0;
}