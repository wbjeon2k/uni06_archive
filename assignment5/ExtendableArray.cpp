#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include "ExtendableArray.h"

using namespace std;

ExtendableArray::ExtendableArray() {
	size = 2;//default size ==2
	arrayPointer = new int[2];

	arrayPointer[0] = 0;//initialize as 0
	arrayPointer[1] = 0;
}

ExtendableArray::ExtendableArray(const ExtendableArray& other) {

	size = other.size;
	
	arrayPointer = new int[size];
	for (int i = 0;i < size;i++) {
		arrayPointer[i] = other.arrayPointer[i];//copy elements
	}
}

ExtendableArray::~ExtendableArray() {
	delete [] arrayPointer;
	//arrayPointer = nullptr;//disable memory block
}

ExtendableArray& ExtendableArray::operator=(const ExtendableArray& rhs) {
	int s = rhs.size;
	delete[] arrayPointer;
	arrayPointer = new int[s];
	for (int i = 0;i < s;i++) {
		arrayPointer[i] = rhs.arrayPointer[i];//copy elements
	}

	size = s;
	return *this;
}




ElementRef ExtendableArray::operator[](int i) {

	return ElementRef(*this, i);//return ElementRef object
}

ElementRef::ElementRef(ExtendableArray& theArray, int i) {

	intArrayRef = new ExtendableArray;
	intArrayRef = &theArray;//points to same arrayPointer
	index = i;//same index
}

ElementRef::ElementRef(const ElementRef& other) {
	intArrayRef = new ExtendableArray;
	*intArrayRef = *other.intArrayRef;//copy elements
	index = other.index;//copy index
}

ElementRef::operator int()const {
	if (index + 1 > intArrayRef->size) {//if index is bigger than size
		return 0;
	}
	else if (index < 0) {//if index is negative
		return 0;
	}
	else if (index == INT_MAX) {//if index is the maximum value of int
		return 0;
	}
	else {//return value
		return (intArrayRef->arrayPointer[index]);
	}
}

ElementRef& ElementRef::operator=(const ElementRef& rhs) {
	int p = rhs.intArrayRef->arrayPointer[rhs.index];
	if (this != &rhs) {//do not copy self
		*this = p;//change the value as p
	}
	return *this;
}

ElementRef& ElementRef::operator=(int val) {//assign int value val to index
	int s = intArrayRef->size;
	int i = index;
	if (i + 1 > s) {//if new index is bigger than the current size
					/*https://www.daniweb.com/programming/software-development/threads/118566/infinite-array*/
		intArrayRef->size = i + 1;
		int *tmp = new int[i + 1];//make temp with i+1 memory
		for (int j = 0;j < s;j++) {//copy original values
			tmp[j] = (intArrayRef->arrayPointer)[j];
		}
		for (int j = s;j < i;j++) {//initialize rest of the part as 0
			tmp[j] = 0;
		}
		
		delete[] intArrayRef->arrayPointer;//free memory
		intArrayRef->arrayPointer = tmp;//point to new memory
		
	}

	intArrayRef->arrayPointer[i] = val;
	return *this;


}

ElementRef::~ElementRef() {
	//delete intArrayRef;
	//intArrayRef = nullptr;
}
