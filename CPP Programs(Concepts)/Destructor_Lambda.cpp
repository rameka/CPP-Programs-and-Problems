/*
Destructor_Lambda.cpp: This program illustrates the use of destructor, lambda functions, and sorting in STL
Author: Ramakrishna Sayee Meka
*/

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

class my_class {
public:
	map<int, list<vector<map<int, vector<int>>>>> map1;
	int * p;
	vector<list<int *>> vector1;

	vector<my_class> * v2;

	list<vector<int>> L1;

	~my_class() {  //pay attention to pointers
		delete p;
		for (size_t i = 0; i < vector1.size(); i++) {
			auto it1 = vector1[i].begin();
			while (it1 != vector1[i].end()) {
				delete *it1;
				//in HW3; you might also need 
				//vector1[i].erase(it1); is not needed here
				it1++;
			}
			//You also need to implement code
			//to take care of v2, which is not shown here
		}

	}
	//The rest of the class is not shown here
};
	class ThreeD {
	public:
		int ht;
		int wid;
		int dep;
		ThreeD(int i, int j, int k) { ht = i; wid = j; dep = k; }
		ThreeD() {}
		int vol() { return ht * wid*dep; }
		bool operator<(ThreeD T) { return vol() < T.vol(); }
	};

	bool cp1(ThreeD T1, ThreeD T2) { return T1.vol() < T2.vol(); }


	int main() {

		//The following all carry the nototation of a 2-dimensional array
		int A[5][5];
		A[2][3] = 45;
		vector<vector<int>> V1{ { 1,2 },{ 3,4,5 },{ 7, 8, 9, 10 } };
		V1[2][1] = 45;
		map<int, vector<int>> M1 = { { 2,{ 1, 2 } },{ 1,{ 3,4,5 } },{ 0,{ 4, 9, 10, 11 } } };
		M1[1][2] = 45;
		vector< map<int, int>> V2 = { { { 3, 3 },{ 4,4 },{ 5, 5 },{ 6,6 } },{ { 4,4 },{ 5,5 },{ 6,6 },{ 7,7 } } };
		V2[1][5] = 45;
		map<int, map<int, int>> M2 = {
		{ 1,{ { 3, 3 },{ 4,4 },{ 5, 5 },{ 6,6 } } },
		{ 2,{ { 3, 3 },{ 4,4 },{ 5, 5 },{ 6,6 } } } };

		M2[2][4] = 45;

		map<int, string> M3 = { {1, "Dave"}, {22, "John"}, {10, "Pat"} };
		auto it1 = M3.find(2);
		if (it1 != M3.end()) {
			cout << it1->second;
			cout << M3[2];//a bit slower
		}


		//Lambda functions

		int i = 10, j = 20, k = 30;


		auto func1 = [i, &k](int a, int b)-> int { //[...]: capture list
												   //(...) augument list 
												   //-> int : return int; optional
												   //i++;  Error!  i is read only
			k = 300;//k allows both read and write
			return (i + k + a + b);
		};

		cout << func1(4, 5) << endl;

		ThreeD t1(3, 4, 5), t2(6, 2, 1), t3(3, 3, 3), t4(2, 3, 6);
		vector<ThreeD> V10 = { t1, t2, t3, t4 };
		//The following three implementations are equivalent
		sort(V10.begin(), V10.end());
		sort(V10.begin(), V10.end(), cp1);
		sort(V10.begin(), V10.end(), [](ThreeD T1, ThreeD T2) {return T1.vol() < T2.vol(); });
		for (size_t i = 0; i < V10.size(); i++) { cout << endl; std::cout << V10[i].ht << " " << V10[i].wid << " " << V10[i].dep << " "; }
		getchar();
		getchar();
		return 0;
	}