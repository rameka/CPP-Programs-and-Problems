/*
Copy_Move_Constructor.cpp: This program illustrates how to define copy constructor, move constructor, Left-Reference and Right-Reference.
Author: Ramakrishna Sayee Meka
*/

#include <iostream>
using namespace std;

class big_data {
public:
	int size;//num of elements in big_array
	int * big_array;
	big_data() {
		size = 0;
		big_array = nullptr;
	}
	big_data(int s) {
		size = s;
		//******************************
		//int * big_array = new int[s];
		big_array = new int[s];  //the above error was corrected.
		for (int i = 0; i < s; i++) big_array[i] = 0;
	}
	~big_data() {  //destructor
		delete[] big_array;
		cout << "Leaving destructor" << endl;
	}

	//copy constructor
	big_data(const big_data &B) {//read only
								 //left ref version of copy constructor
		size = B.size;
		big_array = new int[size];
		for (int i = 0; i < size; i++) big_array[i] = B.big_array[i];
		cout << "Leaving copy constructor" << endl;
	}
	big_data(big_data &&B) { //move constructor
							 //or right ref version of copy constructor
		size = B.size;
		big_array = B.big_array;
		B.big_array = nullptr;
		cout << "Leaving move constructor" << endl;
	}


	void create_random_array(int k, int m);
	big_data three_times();
	void print();
	void operator=(big_data &B);
	void operator=(big_data &&B);

};

void big_data::operator=(big_data &&B) {
	delete [] big_array;
	size = B.size;
	big_array = B.big_array;
	B.big_array = nullptr;
	cout << "Leaving right ref version operator=" << endl;
}
void big_data::operator=(big_data &B) {
	delete [] big_array;
	size = B.size;
	big_array = new int[size];
	for (int i = 0; i < size; i++) big_array[i] = B.big_array[i];
	cout << "Leaving left ref version operator=" << endl;
}

void big_data::print() {
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << big_array[i] << " ";
	}
	cout << endl;

}
big_data big_data::three_times() {
	big_data temp(size);
	for (int i = 0; i < size; i++) {
		temp.big_array[i] = big_array[i] * 3;
	}
	return move(temp);//move forces compiler to treat temp as right ref
}
void big_data::create_random_array(int k, int m) {
	size = k;
	big_array = new int[k];
	for (int i = 0; i < k; i++) {
		big_array[i] = rand() % m; // 0 ... m-1
	}
}

void f1(big_data B) {
	cout << B.big_array[5] << endl;

}
void f2(big_data &B) {
	cout << B.big_array[5] << endl;
}
void f2(big_data &&B) {

	B.big_array[3] = 1000;
}

int main() {
	big_data B1, B2, B3;
	B1.create_random_array(30, 20);
	B1.print();
	B2 = B1; //compiler will chnage it into B2.operator=(B1);  left ref version
	B3 = B1.three_times(); //compiler will change it into
						   //B3.operator=(B1.three_times()); //right ref vesion of operator=
	B3.print();

	f1(B1);
	f2(B2);
	f2(move(B2));
	cout << B2.big_array[3] << endl;
	getchar();
	getchar();
	return 0;

}