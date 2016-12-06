#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class queue {
public:
	queue();
	~queue();
	queue(const queue<T>& q);
	queue<T>& operator=(const queue<T>& q);
	T front();
	void push(const T&);
	void pop();
	bool empty();
	void print();
private:
	void increase_capacity();
	
	T* array;
	int capacity = 0;
	int size = 0;
	int first = 0;
	int last = 0;	// 1 after the last element in the array
};
#include "queue.cpp"


#endif