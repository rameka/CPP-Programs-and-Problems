/*
STL_DB_Conversion.cpp: It illustrates how to design a databse using STL in C++ and converting one DB format to another.
Author: Ramakrishna Sayee Meka
*/

#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

void DB1_print(vector<list<int>> &DB1);
void DB1_to_DB2(vector<list<int>> &DB1, list<vector<int>> & DB2);
void DB2_print(list<vector<int>> &DB2);
void DB1_to_DB3(vector<list<int>> &DB1, list< list<int> *>  &DB3);
void DB3_print(list < list<int> * > & DB3);
void DB2_to_DB4(list< vector<int>> &DB2, list< list<int *> *> &DB4);
void DB4_print(list< list< int *> *> &DB4);


int main() {
	vector<list<int>> DB1 = { { 1,2,3 },{ 4, 5 },{ 6,7,8,9 } };
	DB1_print(DB1);
	list<vector<int>> DB2;
	DB1_to_DB2(DB1, DB2);
	DB2_print(DB2);

	list< list<int> * > DB3;
	DB1_to_DB3(DB1, DB3);
	DB3_print(DB3);
	list< list<int *> *> DB4;
	DB2_to_DB4(DB2, DB4);
	DB4_print(DB4);

	getchar();
	getchar();
	return 0;
}

void DB1_print(vector<list<int>> &DB1) {
	cout << endl;
	list<int>::iterator it1;

	for (size_t i = 0; i < DB1.size(); i++) {
		it1 = DB1[i].begin();

		while (it1 != DB1[i].end()) {
			cout << *it1 << " ";
			it1++;
		}
		cout << endl;
	}

}

void DB1_to_DB2(vector<list<int>> &DB1, list<vector<int>> & DB2) {

	list<int>::iterator it1;
	for (size_t i = 0; i < DB1.size(); i++) {
		it1 = DB1[i].begin();
		vector<int> V1;
		while (it1 != DB1[i].end()) {
			V1.push_back(*it1);
			it1++;
		}
		DB2.push_back(V1);
	}
}

void DB2_print(list<vector<int>> &DB2) {
	cout << endl;
	auto it1 = DB2.begin(); //list<vector<int>>::iterator it1 = DB2.begin();
	while (it1 != DB2.end()) {
		for (size_t i = 0; i < it1->size(); i++) {
			cout << (*it1)[i] << " ";
		}

		it1++;
		cout << endl;
	}



}

void DB1_to_DB3(vector<list<int>> &DB1, list< list<int> *>  &DB3) {

	list<int>::iterator it1;
	for (size_t i = 0; i < DB1.size(); i++) {
		it1 = DB1[i].begin();
		/* the following is incorrect
		list<int> temp;
		while (it1 != DB1[i].end()) {
		temp.push_back(*it1);
		it1++;
		}
		DB3.push_back(&temp);
		*/
		list<int> * p = new list<int>;
		while (it1 != DB1[i].end()) {
			p->push_back(*it1);
			it1++;
		}
		DB3.push_back(p);
	}
}

void DB3_print(list < list<int> * > & DB3) {
	auto it1 = DB3.begin();//list<lit <int> *>::iterator it1
	while (it1 != DB3.end()) {
		list<int>::iterator it2 = (*it1)->begin();
		cout << endl;
		while (it2 != (*it1)->end()) {
			cout << *it2 << " ";
			it2++;
		}
		it1++;
	}
}

void DB2_to_DB4(list< vector<int>> &DB2, list< list<int *> *> &DB4) {
	auto it1 = DB2.begin();
	while (it1 != DB2.end()) {
		list<int * > * p = new list<int *>;
		for (size_t i = 0; i < it1->size(); i++) {
			p->push_back(new int ((*it1)[i]));
		}
		DB4.push_back(p);
		it1++;
	}
}

void DB4_print(list< list< int *> *> &DB4) {
	cout << endl;
	auto it1 = DB4.begin();
	while (it1 != DB4.end()) {
		auto it2 = (*it1)->begin();
		while (it2 != (*it1)->end()) {
			cout << **it2 << " ";
			it2++;
		}
		cout << endl;
		it1++;
	}
}