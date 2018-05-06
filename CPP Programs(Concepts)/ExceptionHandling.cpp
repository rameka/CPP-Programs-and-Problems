/*
ExceptionHandling.cpp: Simple program to demonstrate excention handling .
Author: Ramakrishna Sayee Meka
*/

#include <iostream>
using namespace std;



void test(double x) {

	if (x == 0) throw "Error";

}

int main() {
	try {
		int dadsage = 35, sonsage = 4;
		if (dadsage < sonsage) throw 99;
		else cout << "Fine" << endl;

		double i = 20.5, j = 0;
		if (j == 0) throw "Error";
		cout << i / j;


	}
	catch (int x) {
		cout << "Son can't be older than Dad!" << "Error code : " << x << endl;
	}
	catch (char * s) { cout << "cannot divide by 0" << endl; }
	catch (...) {};



	try {
		double jj = 45.2, k = 0;
		test(k);
		cout << "OK";
	}
	catch (char * s) { cout << "New cannot divide by 0" << endl; }
	getchar();
	getchar();
}