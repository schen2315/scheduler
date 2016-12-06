#include <iostream>
template <typename T>
queue<T>::queue() {
	array = NULL;
}
template <typename T>
queue<T>::~queue() {
	if(array != NULL) {
		delete [] array;
	}
}
template <typename T>
queue<T>::queue(const queue<T>& q) {
	capacity = q.capacity;
	size = q.size;
	first = q.first;
	last = q.last;
	array = new T[capacity];
	for(int i = 0; i < last; i++) {
		array[i] = q.array[i];
	}
};
template <typename T>
queue<T>& queue<T>::operator=(const queue<T>& q) {
	if(this == &q) return *this;
	if(array != NULL) delete array;
	capacity = q.capacity;
	size = q.size;
	first = q.first;
	last = q.last;
	array = new T[capacity];
	for(int i = 0; i < last; i++) {
		array[i] = q.array[i];
	}
	return *this;
};
template <typename T>
bool queue<T>::empty() {
	if(size == 0) return true;
	return false;
}
template <typename T>
void queue<T>::push(const T& element) {
	if(last >= capacity) increase_capacity();
	array[last++] = element;
	size++;
}
template <typename T>
void queue<T>::pop() {
	if(empty()) return;
	else {
		first++;
		size--;
	}
}
template <typename T>
void queue<T>::increase_capacity() {
	if(array == NULL) {
		array = new T[1];
		capacity = 1;
	} else {
		//double the capacity
		T* temp = new T[2*capacity];
		capacity = 2*capacity;
		int j=0;
		for(int i = first; i < last; i++) {
			temp[j] = array[i];
			j++;
		}
		delete [] array;
		array = temp;
		first = 0;
		size = j;
		last = j;
	}
}
template <typename T>
T queue<T>::front() {
	return array[first];
}
template <typename T>
void queue<T>::print() {
	for(int i=first; i < last; i++) {
		std::cout << array[i] << " ";
	}
}




