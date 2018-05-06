
/*
ProducerConsumer.cpp : Threaded application for Part Worker and Product Worker
Author: Ramakrishna Sayee Meka, Syracuse University
Date: 4/26/2018
*/

#include "stdafx.h"
#include<thread>
#include<iostream>
#include<mutex>
#include<stdlib.h>
#include <condition_variable>

using namespace std;

mutex mutx, cnt; // for Buffer - which is the critical section of the problem
condition_variable cond_var1, cond_var2; // One variable for Part worker and another for product worker 
										 //to establish synchronization
int randSeed = 0; // for generating random combinations

class PartsTuple {
public:
	int A, B, C, D;
	PartsTuple() {
		A = 0;
		B = 0;
		C = 0;
		D = 0;
	};
	PartsTuple(int a, int b, int c, int d) {
		A = a;
		B = b;
		C = c;
		D = d;
	};
};


PartsTuple buffer; // Buffer has the maximum capacity of (A = 6), (B = 5), (C = 4), (D = 3)
int count1 = 0, count2 = 0;
int sleep1 = 0, sleep2 = 0;

PartsTuple  getPartWorkerCombinations() {
	PartsTuple combinations[20] = {
		PartsTuple(0,0,1,2), PartsTuple(0,0,2,1), PartsTuple(0,1,0,2), PartsTuple(0,1,2,0),
		PartsTuple(0,2,0,1), PartsTuple(3,0,0,0), PartsTuple(0,3,0,0), PartsTuple(0,0,3,0),
		PartsTuple(0,0,0,3), PartsTuple(1,2,0,0), PartsTuple(2,0,1,0), PartsTuple(2,0,0,1),
		PartsTuple(1,0,1,1), PartsTuple(1,1,0,1), PartsTuple(1,1,1,0), PartsTuple(0,2,1,0),
		PartsTuple(0,1,1,1), PartsTuple(1,0,2,0), PartsTuple(1,0,0,2), PartsTuple(2,1,0,0)
	};
	srand(randSeed++);
	return combinations[rand() % 20];
}

PartsTuple  getProductWorkerCombinations() {
	PartsTuple combinations[18] = {
		PartsTuple(2,2,0,0), PartsTuple(2,0,2,0),PartsTuple(2,0,0,2), PartsTuple(0,2,2,0),
		PartsTuple(0,2,0,2), PartsTuple(0,0,2,2),PartsTuple(3,1,0,0), PartsTuple(3,0,1,0),
		PartsTuple(0,1,3,0), PartsTuple(0,1,0,3),PartsTuple(0,3,1,0), PartsTuple(0,3,0,1),
		PartsTuple(1,0,3,0), PartsTuple(1,0,0,3),PartsTuple(0,0,1,3), PartsTuple(0,0,3,1),
		PartsTuple(3,0,0,1), PartsTuple(1,3,0,0)
	};
	srand(randSeed++);
	return combinations[rand() % 18];
}

void PartWorker(int i);
void ProductWorker(int i);
void placeRequest(PartsTuple &parts, char type, int maxCapacity);
void pickRequest(PartsTuple &parts, char type);


void PartWorker(int i)
{
	cnt.lock();
	count1 = count1 + 1;
	cnt.unlock();
	for (int iter = 0; iter<5; iter++)
	{
		
		PartsTuple parts = getPartWorkerCombinations();
		
		unique_lock<mutex> lock(mutx);
		while (buffer.A < 6 || buffer.B < 5 || buffer.C < 4 || buffer.D <3) {
			cout << "PartWorker ID: " << i << "\n";
			cout << "Iteration: " << iter + 1<<"\n";
			cout << "Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
			cout << "Place Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
			placeRequest(parts, 'a', 6);
			placeRequest(parts, 'b', 5);
			placeRequest(parts, 'c', 4);
			placeRequest(parts, 'd', 3);
			cout << "Updated Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
			cout << "Updated Place Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n\n";

			if (parts.A == 0 && parts.B == 0 && parts.C == 0 && parts.D==0) {
				break;
			}

			/*if (parts.A != 0 || parts.B != 0 || parts.C != 0 || parts.D != 0) {
				while (buffer.A == 6 || buffer.B == 5 || buffer.C == 4 || buffer.D == 3) {
					cond_var1.wait(lock);
					
				}
				cond_var2.notify_one();
				continue;
			}*/

			if (parts.A != 0) {
				while (buffer.A == 6) {
					if (count2 == 0 || (count2 == sleep2) )
					{
						cout << "PartWorker ID: " << i << "\n";
						cout << "Iteration: " << iter + 1 << "\n";
						cout << "Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "Place Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Updated Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "Updated Place Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Return\n\n";

						count1--;
						cond_var1.notify_one();
						cond_var2.notify_one();
						return;
					}
					sleep1++;
					cond_var1.wait(lock);
					sleep1--;
				}
				
				cond_var2.notify_one();
				continue;
			}
			if (parts.B != 0) {
				while (buffer.B == 5) {
					if (count2 == 0 || (count2 == sleep2))
					{
						cout << "PartWorker ID: " << i << "\n";
						cout << "Iteration: " << iter + 1 << "\n";
						cout << "Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "Place Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Updated Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "Updated Place Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Return\n\n";

						count1--;
						cond_var1.notify_one();
						cond_var2.notify_one();
						return;
					}
					sleep1++;
					cond_var1.wait(lock);
					sleep1--;

				}
				
				cond_var2.notify_one();
				continue;
			}
			if (parts.C != 0) {
				while (buffer.C == 4) {
					if (count2 == 0 || (count2 == sleep2))
					{
						cout << "PartWorker ID: " << i << "\n";
						cout << "Iteration: " << iter + 1 << "\n";
						cout << "Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "Place Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Updated Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "Updated Place Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Return\n\n";

						count1--;
						cond_var1.notify_one();
						cond_var2.notify_one();
						return;
					}
					sleep1++;
					cond_var1.wait(lock);
					sleep1--;
				}
				
				cond_var2.notify_one();
				continue;
			}
			if (parts.D != 0) {
				while (buffer.D == 3) {
					if (count2 == 0 || (count2 == sleep2))
					{
						cout << "PartWorker ID: " << i << "\n";
						cout << "Iteration: " << iter + 1 << "\n";
						cout << "Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "Place Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Updated Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "Updated Place Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Return\n\n";

						count1--;
						cond_var1.notify_one();
						cond_var2.notify_one();
						return;
					}
					
					sleep1++;
					cond_var1.wait(lock);
					sleep1--;
				}
				
				cond_var2.notify_one();
				continue;
			}
		}

		cond_var2.notify_all();
	}

	cnt.lock();
	count1 = count1 - 1;
	cnt.unlock();
}

void ProductWorker(int i)
{
	cnt.lock();
	count2 = count2 + 1;
	cnt.unlock();
	for (int iter = 0; iter<5; iter++)
	{
		
		PartsTuple parts = getProductWorkerCombinations();
		unique_lock<mutex> lock(mutx);
		do
		{
			cout << "ProductWorker ID:" << i << "\n";
			cout << "Iteration:" << iter+1 << "\n";
			cout << "Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D<<")\n";
			cout << "PickUp Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D<< ")\n";
			pickRequest(parts, 'a');
			pickRequest(parts, 'b');
			pickRequest(parts, 'c');
			pickRequest(parts, 'd');
			cout << "Updated Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D <<")\n";
			cout << "Updated PickUp Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D <<")\n\n";

			if (parts.A == 0 && parts.B == 0 && parts.C == 0 && parts.D == 0) {
				break;
			}

	/*		if (parts.A != 0 || parts.B != 0 || parts.C != 0 || parts.D != 0) {
				while (buffer.A == 0 || buffer.B == 0 || buffer.C == 0 || buffer.D == 0) {
					
					cond_var2.wait(lock);
				}
				
				cond_var1.notify_one();
				continue;
			}*/
			if (parts.A != 0) {
				while (buffer.A == 0) {
					
					if (count1 == 0 || (count1 == sleep1))
					{
						cout << "ProductWorker ID:" << i << "\n";
						cout << "Iteration:" << iter + 1 << "\n";
						cout << "Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "PickUp Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Updated Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "Updated PickUp Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Return" << endl<<endl;
						count1--;
						cond_var1.notify_one(); 
						cond_var2.notify_one();
						return;
					}
					sleep2++;
					cond_var2.wait(lock);
					sleep2--;
				}
				
				cond_var1.notify_one();
				continue;
			}
			if (parts.B != 0) {
				while (buffer.B == 0) {
					
					if (count1 == 0 || (count1 == sleep1))
					{
						cout << "ProductWorker ID:" << i << "\n";
						cout << "Iteration:" << iter + 1 << "\n";
						cout << "Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "PickUp Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Updated Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "Updated PickUp Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Return" << endl<<endl;
						count1--;
						cond_var1.notify_one();
						cond_var2.notify_one();
						return;
					}
					sleep2++;
					cond_var2.wait(lock);
					sleep2--;
				}
				
				cond_var1.notify_one();
				continue;
			}
			if (parts.C != 0) {
				while (buffer.C == 0) {
					
					if (count1 == 0 || (count1 == sleep1))
					{
						cout << "ProductWorker ID:" << i << "\n";
						cout << "Iteration:" << iter + 1 << "\n";
						cout << "Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "PickUp Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Updated Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "Updated PickUp Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Return" << endl<<endl;
						count1--;
						cond_var1.notify_one();
						cond_var2.notify_one();
						return;
					}
					sleep2++;
					cond_var2.wait(lock);
					sleep2--;
				}
				
				cond_var1.notify_one();
				continue;
			}
			if (parts.D != 0) {
				while (buffer.D == 0) {
					
					if (count1 == 0 || (count1 == sleep1))
					{
						cout << "ProductWorker ID:" << i << "\n";
						cout << "Iteration:" << iter + 1 << "\n";
						cout << "Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "PickUp Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Updated Buffer State: (" << buffer.A << "," << buffer.B << "," << buffer.C << "," << buffer.D << ")\n";
						cout << "Updated PickUp Request: (" << parts.A << "," << parts.B << "," << parts.C << "," << parts.D << ")\n";
						cout << "Return" << endl<<endl;
						count1--;
						cond_var1.notify_one();
						cond_var2.notify_one();
						return;
					}
					sleep2++;
					cond_var2.wait(lock);
					sleep2--;
				}
				
				cond_var1.notify_one();
				continue;
			}

	

		} while (buffer.A > 0 || buffer.B > 0 || buffer.C > 0 || buffer.D > 0);
	
		
		cond_var1.notify_one();
	}

	cnt.lock();
	count2 = count2 - 1;
	cnt.unlock();
}

// Placing the part worker request to the buffer so that the product workers could consume it.
void placeRequest(PartsTuple &parts, char type, int maxCapacity)
{
	int currentPart, currentBuffer;

	//Setting the current part value and buffer value of that part based on type
	switch (type) {

	case 'a':
		currentPart = parts.A;
		currentBuffer = buffer.A;
		break;
	case 'b':
		currentPart = parts.B;
		currentBuffer = buffer.B;
		break;
	case 'c':
		currentPart = parts.C;
		currentBuffer = buffer.C;
		break;
	case 'd':
		currentPart = parts.D;
		currentBuffer = buffer.D;
		break;
	}

	//Placing the parts in buffer and updating the remaining parts to the place request 
	if (currentPart + currentBuffer <= maxCapacity) {
		currentBuffer += currentPart;
		currentPart = 0;
	}
	else {
		int temp = currentBuffer;
		currentBuffer = maxCapacity;
		currentPart -= (maxCapacity - temp);
	}

	//Updating the original request with the remaining parts of that type
	switch (type) {

	case 'a':
		parts.A = currentPart;
		buffer.A = currentBuffer;
		break;
	case 'b':
		parts.B = currentPart;
		buffer.B = currentBuffer;
		break;
	case 'c':
		parts.C = currentPart;
		buffer.C = currentBuffer;
		break;
	case 'd':
		parts.D = currentPart;
		buffer.D = currentBuffer;
		break;
	}
}

void pickRequest(PartsTuple &parts, char type)
{
	int currentPart, currentBuffer;

	//Setting the current part value and buffer value of that part based on type
	switch (type) {

	case 'a':
		currentPart = parts.A;
		currentBuffer = buffer.A;
		break;
	case 'b':
		currentPart = parts.B;
		currentBuffer = buffer.B;
		break;
	case 'c':
		currentPart = parts.C;
		currentBuffer = buffer.C;
		break;
	case 'd':
		currentPart = parts.D;
		currentBuffer = buffer.D;
		break;
	}

	//Picking up function from buffer and updating the parts remaining

	if (currentBuffer - currentPart >= 0) {
		currentBuffer -= currentPart;
		currentPart = 0;
	}
	else {
		currentPart -= currentBuffer;
		currentBuffer = 0;
	}

	//Updating the original request with the remaining parts of that type
	switch (type) {

	case 'a':
		parts.A = currentPart;
		buffer.A = currentBuffer;
		break;
	case 'b':
		parts.B = currentPart;
		buffer.B = currentBuffer;
		break;
	case 'c':
		parts.C = currentPart;
		buffer.C = currentBuffer;
		break;
	case 'd':
		parts.D = currentPart;
		buffer.D = currentBuffer;
		break;
	}
}


int main() {
	const int m = 16, n = 12; //m: number of Part Workers
							  //n: number of Product Workers
	thread partW[m];
	thread prodW[n];
	for (int i = 0; i < n; i++) {
		partW[i] = thread(PartWorker, i);
		prodW[i] = thread(ProductWorker, i);
	}
	for (int i = n; i < m; i++) {
		partW[i] = thread(PartWorker, i);
	}
	/* Join the threads to the main threads */
	for (int i = 0; i < n; i++) {
		partW[i].join();
		prodW[i].join();
	}
	for (int i = n; i < m; i++) {
		partW[i].join();
	}
	cout << "Finish!" << endl;
	getchar();
	getchar();
	return 0;}

