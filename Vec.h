#ifndef VEC_H
#define VEC_H

#include <fstream>
template <typename T>
class Vec {
public:
	Vec();
	~Vec();
	Vec(const Vec &v);
	Vec<T>& operator=(const Vec &v);
	T& operator[](int i);
	void push_back(const T&);
	int size();
	void print();
private:
	void increase_capacity();

	T* array;
	int capacity = 0;	//maximum # of elements that can be stored
	int length = 0;		//current # of elements inside the array
};

#include "Vec.cpp"


#endif