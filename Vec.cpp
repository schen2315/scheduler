#include <iostream>
template <typename T>
Vec<T>::Vec() {
	array = NULL;
}
template <typename T>
Vec<T>::~Vec() {
	if(array != NULL) {
		delete [] array;
	}
}
template <typename T>
Vec<T>::Vec(const Vec &v) {
	capacity = v.capacity;
	length = v.length;
	array = new T[capacity];
	for(int i=0; i < length; i++) {
		array[i] = v.array[i];
	}
};
template <typename T> 
Vec<T>& Vec<T>::operator=(const Vec &v) {
	if(this == &v) return (*this);
	if(array != NULL) delete array;
	capacity = v.capacity;
	length = v.length;
	array = new T[capacity];
	for(int i=0; i < length; i++) {
		array[i] = v.array[i];
	}
	return *this;
};
template <typename T>
void Vec<T>::push_back(const T& element) {
	if(length >= capacity) increase_capacity();
	//add the element
	array[length++] = element;
}
template <typename T>
void Vec<T>::increase_capacity() {
	if(array == NULL) {
		array = new T[1];
		capacity = 1;
	} 
	else {
		//double the capacity
		T* temp = new T[2*capacity];
		capacity = 2*capacity;
		//copy elements
		for(int i=0; i < length; i++) {
			temp[i] = array[i];
		}
		//delete the original
		delete [] array;
		array = temp;
	}
}
template <typename T> 
void Vec<T>::print() {
	for(int i=0; i < length; i++) {
		std::cout << array[i] << " ";
	}
}
template <typename T>
int Vec<T>::size() {
	return length;
}
template <typename T>
T& Vec<T>::operator[](int i) {
	if(i < length && i >= 0) {
		return array[i];
	}
	else return 0;
};



