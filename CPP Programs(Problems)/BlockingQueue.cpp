/*
* BlockingQueue.cpp: Implementation of blocking queue using condition variable, mutex, and unique_lock
* Author: Ramakrishna Sayee Meka, Syracuse University
*/

#include <iostream>
#include <deque>  //deque combines the functionality of vector and list.  Supports index based random access
		  //and pop and push at both ends
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

class blocking_queue {
private:
	mutex m1;
	condition_variable cv1, cv2;
	deque<int> queue;
public:
	void push(int k) {
		unique_lock<mutex> ulock(m1);
		while (queue.size() == 10) cv1.wait(ulock);
		queue.push_back(k);
		cv2.notify_one();
	}
	int pop() {
		{
			unique_lock<mutex> ulock(m1);
			while (queue.empty()) cv2.wait(ulock);
			int temp;
			temp = queue.front();
			queue.pop_front();
			cv1.notify_one();
			return temp;
		}
	}
};

void put(blocking_queue &b_queue, int i, int k) {

	b_queue.push(k);
	cout << "putter " << i << " push value " << k << " to the blocking_queue" << endl;
}

void get(blocking_queue  &b_queue, int i) {
	cout << "getter " << i << " pop value " << b_queue.pop() << endl;;

}

int main() {

	blocking_queue b_queue;
	thread putter[30];
	thread getter[30];

	for (int i = 0; i < 30; i++) {
		putter[i] = thread(put, ref(b_queue), i, 10 * i);
		getter[i] = thread(get, ref(b_queue), i);
	}

	for (int i = 0; i < 30; i++) {

		putter[i].join();
		getter[i].join();
	}

	getchar();
	getchar();
	return 0;

}