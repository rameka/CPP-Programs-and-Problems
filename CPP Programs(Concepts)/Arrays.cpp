/*
Arrays.cpp: This is a program on arrays initialization, decleration and basics on pointers and using it with array
Author: Ramakrishna Sayee Meka
*/

#include <iostream> 

using namespace std;

int main() {

	int i = 0;
	char c = 'Y';
	cout << i << "  " << c << endl;
	int * p = &i;  //declare p be a pointer to int; whose value is initializaed to the add of i
	//int * p; int* p ; int *p; are the same
	//&v is the address of the memory location for variable v

	cout << i << endl;
	cout << *p << endl; //will give the same result.
	
	//*p returns the content (or value) in the memory locations whose address os carried by p
	//the * function here is referred to as a dereferencing function


	int A[5] = { 0,1,2,3,4 };

	cout << A[0] << endl;
	cout << *A << endl; //*A is the same as A[0].
	// Array name without index is the same as the address of the first element of the array
	//In our example, A is the same as &A[0]

	cout << A[2] << endl;
	cout << *(A + 2) << endl;

	cout << A[10] << endl; //out of bound will not lead to error, but the value will be meaningless
	//C++ compiler will not check for out of bound error

	int B[3][4] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12} };

	cout << B[2][1] << endl;
	cout << *(*(B + 2) + 1) << endl;
	cout << *(B[2] + 1) << endl;
	cout << *(&B[0][0] + 2 * 4 + 1) << endl;

	getchar();//Waiting for input
	return 0;
}