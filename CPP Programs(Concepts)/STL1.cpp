/*
STL1.cpp: This program to demonstrates the use of vectors, lists, maps, arrays and alsso use of auto key word.
Author: Ramakrishna Sayee Meka
*/

//vector, list, map each is a container
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <array>
#include <string>

using namespace std;
class course {
public:
	string name;//such as "CIS554"
	int section;
	int credits;
	course(string n, int s, int c) : name(n), section(s), credits(c) {}
	//course(string n, int s, int c){name = n; section = s; credits = c;}
	bool operator==(const course &C) const { return (name == C.name); }  //find needs this
	bool operator<(const course &C) const { return (section < C.section); }  //sort needs this
	//map's internal sorting also needs this
};

int main() {

	//VECTOR
	vector<int> V1 = { 0,1,2,3,4 };
	vector<int> V2(V1), V3 = V1;

	//vector supports array index, or random access
	cout << endl;
	for (size_t i = 0; i < V1.size(); i++) //size_t is non_negative int;
		cout << V1[i] << " ";
	//only vector, deque, and array
	//iterator is "pointer" that you have to use within the scope of STL
	cout << endl;
	vector<int>::iterator it1(V1.begin()); //it1 = V1.begin();
	auto it2(V1.begin());

	//it2 += 3; it2 -= 2;

	int i1 = 10;
	auto j = i1;


	while (it1 != V1.end()) {
		cout << *it1 << " ";
		it1++;
	}
	//begin() returns the position of first element
	//end() returns the position following the last element

	V1.push_back(5);
	V1.pop_back();
	cout << endl;
	cout << V1.front() << " " << V1.back() << endl;
	//front() returns the first element
	//back() returns the last element

	//When passing a vector to a funciton, you can specify either
	//call by value or call by ref

	course c1("CIS554", 1, 3), c2("MAT296", 10, 4), c3("CSE581", 2, 3), c4("PSY205", 8, 3);
	vector<course> VC1 = { c2, c3, c4 };
	vector<course>::iterator it7 = find(VC1.begin(), VC1.end(), c3);
	//within the two specified range limits, search for c3   [l1,l2)

	VC1.erase(it7);//erase the element at a position
				   //if find does not have a match, end() will be returned
	it7 = find(VC1.begin(), VC1.end(), c1);
	if (it7 != VC1.end()) VC1.erase(it7); //You can't remove element at position end()

										  //LIST
	list<int> L1 = { 0,4, 2, 1,3 };
	L1.push_back(5);
	L1.push_front(-1);
	L1.pop_back();
	L1.pop_front();
	cout << L1.front() << " " << L1.back() << " " << L1.size();
	L1.sort(); //you can sort a list

	list<int>::iterator it9 = L1.begin();
	cout << endl;
	while (it9 != L1.end()) {
		cout << *it9 << " ";
		it9++;
	}


	//only support it9++, ++it9, it9--, --it9
	//it9 += 1;  error!
	list<course> LC1 = { c2, c4, c1 };
	list<course>::iterator it10 = find(LC1.begin(), LC1.end(), c1);
	if (it10 != LC1.end()) LC1.erase(it10); //find return end() if no match found

	auto it11 = LC1.begin();
	while (it11 != LC1.end()) {
		cout << it11->name << " " << it11->section << " " << it11->credits << endl;
		it11++;
	}
	LC1.sort();

	map<course, int> MC1 = { {c1, 1}, {c3,3} };
	MC1[c2] = 2;
	MC1[c4] = 4;
	//map requires the two const in operator< for course class


	int AA[5]; //built-in array
	array<int, 5> AAA = { 0,1,2,3,4 };
	cout << AAA[2] << " " << AAA.size() << " " << AAA.front() << " " << AAA.back() << endl;
	//You can use either call by value or call by ref to pass an STL array to a function

	getchar();
	getchar();
	return 0;
}