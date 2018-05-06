/*
PassValueRef.cpp: This is a program to demonstrate call by value vs call by reference.
Author: Ramakrishna Sayee Meka
*/

#include <iostream>

using namespace std;

void f1(int k) { // call by value
	cout << k << endl;
	k = 100;
}
void f2( int &k) { //call by reference
						
	cout << k << endl;
	k = 100;
}

void f3(const int &k) { //call by reference
	//const make it read-only
	cout << k << endl;
//	k = 100;  error
}

void f4(int C[], int s) {
	int sum = 0;
	for (int i = 0; i < s; i++) {
		sum += C[i];
	}
}

void f5(int * C, int s) {
	int sum = 0;
	for (int i = 0; i < s; i++) {
		sum += C[i];
	}
	C[3] = 999;
}


int main() {

	//call by value vs vall by reference
	int j = 15;
	f1(j);
	cout << j << endl;
	f2(j);
	cout << j << endl;


	int A[5] = { 10,20,30,40,50 };
	f5(A, 5); //array augument will be handled -- call by reference
	cout << A[3] << endl;

	getchar();
	getchar();
	return 0;
}
	
