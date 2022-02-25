#ifndef __GENERICSET_H__
#define __GENERICSET_H__
#define CRT_NO_SECURE_WARNINGS
#define MAX_ITEMS 30

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

typedef int ItemType;

template <class T> class GenericSet
{
protected:
	int size;
	T values[MAX_ITEMS];

public:
	// Default Constructor
	// Post condition: an Empty generic set is created
	GenericSet();

	// Insert function
	virtual void Insert(T item) = 0;

	// Delete function
	virtual void Delete(T item) = 0;

	// Clear function
	// Post condition: all items are removed from the generic set, and the
	//                 size of the generic set becomes 0.
	void Clear();

	// GetSize function
	// Return value is the number of items in the generic set
	int GetSize();

	// IsFull function
	// Return true if there is no more space in the generic set,
	//        false otherwise.
	bool IsFull();

	// IsEmpty function
	// Return true if the generic set is empty,
	//        false otherwise.
	bool IsEmpty();

	friend std::ostream& operator<<(std::ostream& out, const GenericSet& s) {
		out << "{";
		for (int i = 0;i<s.size;i++) {
			ostringstream ss;
			ss << s.values[i];
			string str = ss.str();
			out << str;
		
			if (i < s.size - 1) out << ", ";
		}
		out << "}";
		return out;
	}
};

template <class T> class Set : public GenericSet< T> {

protected:

public:
	Set();
	//int GetSize();
	void Insert(T item);
	void Delete(T item) ;

};

template <class T> class Bag: public GenericSet < T > {
protected:

public:
	Bag();

	void Insert(T item) ;
	void Delete(T item) ;

};

template <class T>
void GenericSet<T>::Clear() {
	
	size = 0;
}

template <class T> int GenericSet<T>::GetSize() {
	return size;
}

template <class T>
bool GenericSet<T>::IsFull() {
	if (this->size == MAX_ITEMS) {
		return true;
	}
	else {
		return false;
	}
}

template <class T>
bool GenericSet<T>::IsEmpty() {
	if (this->size == 0) {
		return true;
	}
	else {
		return false;
	}
}

template< class T> GenericSet<T>::GenericSet() {
	
	size = 0;
}

template< class T> Set<T>::Set() {
	//GenericSet<T>();
}

template< class T> Bag<T>::Bag() {
	//GenericSet<T>();
}

template<class T> void Set<T>::Insert(T item) {
	if (this->size == 30) {
		throw "Set Exception: No more space";
	}
	else {
		for (int i = 0;i < this->size;i++) {
			if (item == this->values[i]) {
				return;
			}
		}
		this->values[this->size] = item;
		this->size += 1;
	}
}

template<class T>void Bag<T>::Insert(T item)
{
	if (this->size==MAX_ITEMS) {
		throw "Set Exception: No more space";
	}
	else {
		this->values[this->size] = item;
		this->size += 1;
	}
}

template<class T>void Bag<T>::Delete(T item)
{
	if (this->size==0) {
		throw "Set Exception: Not found";
	}
	else {
		int a = this->size;
		for (int i = this->size;i >0;i--) {
			if (item == this->values[i - 1]) {
				if (i == this->size) {
					this->size = this->size - 1;
					break;
				}
				else {
					for (int j = i;j < this->size ;j++) {
						this->values[j - 1] = this->values[j];
					}
					this->size -= 1;
					break;
				}
				
			}
		}
		if (a == this->size) {
			throw "Set Exception: Not found";
		}

	}
}

template<class T> void Set<T>::Delete(T item)
{
	if (this->size == 0) {
		throw "Set Exception: Not found";
		//return;
	}
	else {
		int a = this->size;
		for (int i = 0;i <this->size;i++) {
			if (item == this->values[i]) {
				this->size = this->size - 1;
				for (int j = i;j < this->size;j++) {
					this->values[j] = this->values[j + 1];
				}
				
			}
		}
		if (a == this->size) {
			throw "Set Exception: Not found";
		}

	}
}



#endif


