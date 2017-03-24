// File: NList.hpp
// Compilers Used: MS Visual Studio 2015 && Xcode 8.2.1
// Created by Christian Broms on 2/23/17

/* CLASS INFORMATION:
 *
 * This list class is built on a doubly-linked list using
 * a basic Node structure. It accepts any simple
 * arithmetic type T or any complex class T.
 *
 * For proper functionality when using this list class with
 * any complex class T, a limit template should be included in
 * the class' header. Instructions for adding this template
 * are in the README.md.
 *
 * OTHER INFORMATION:
 *
 * This file and all others found with it are a part of the public
 * repository that can be found at https://github.com/CBR0MS/DLinkedList
 * Licensed with the MIT License. 
 *
 */

#include <iostream>
#include <limits>
#include <list>
#include <assert.h>

#ifndef LIST_HPP
#define LIST_HPP

template<class T> class NList {

public:

	/***** CONSTRUCTOR & DECONSTRUCTOR *****/

	NList();
	~NList();

	/***** ACCESSORS *****/

	int size() const;
	unsigned long currentCapacity() const;
	unsigned long maxCapacity() const;
	unsigned long maxtCapacity() const;
	bool isEmpty();
	void displayList();
	T at(const int& index);
    
    /***** OPERATORS *****/
    
    //	friend List operator+(const List& lhs, const List& rhs);
    T operator[](const int& index);

	/***** MUTATORS *****/

	void assign(const T& p_newValue);
	void push_front(const T& p_newValue);
	void push_back(const T& p_newValue);
	void pop_front();
	void pop_back();
	void enableIndexing();
	void disableIndexing();
	void erase(const T& p_eraseItem);
	void expandCapacity();
	void sortAscending();
	void sortDescending();
	void clear();
	void clearAllExcept(const T& keepVal);
	
private:

	struct Node {

		T data;
		Node* llink;
		Node* rlink;
	};

	Node* hPtr = nullptr;
	Node* tPtr = nullptr;
	Node* mPtr = nullptr;
	Node* temp = nullptr;
	Node** arrInd = nullptr;
	
	int m_size = 0;
	bool firstIndexSet = false;
	bool indexing = false;
	bool overCap = false;

	unsigned long m_workingCapacity = 1000;
	unsigned long m_maxCapacity;
	unsigned long m_maxtCapacity;
	unsigned long DIVISOR = 1000;
	unsigned long NODE_SIZE = sizeof(Node);
	unsigned long CLASS_SIZE = sizeof(T);
	unsigned long MAX_SIZE_OF_LIST;


	/***** PRIVATE HELPER FUNCTIONS *****/
	
	void bubbleSort(NList<T>::Node* arr[], int arrSize, bool desc);
	void calcMemReqs();
	void refreshIndex();
};

/***** CONSTRUCTOR & DECONSTRUCTOR *****/

template<class T> NList<T>::NList() {

	hPtr = new Node;
	tPtr = new Node;
	hPtr->llink = nullptr;

	if (std::numeric_limits<T>::is_specialized) {
		hPtr->data = std::numeric_limits<T>::min();
		
	} else {
		hPtr->data = T();
	}
	hPtr->rlink = tPtr;
	tPtr->llink = hPtr;

	if (std::numeric_limits<T>::is_specialized) {
		tPtr->data = std::numeric_limits<T>::max();
		
	} else {
		tPtr->data = T();
	}
	tPtr->rlink = nullptr;
	calcMemReqs();
}

template<class T> NList<T>::~NList() {
	clear();
}

/***** ACCESSORS *****/

template<class T> int NList<T>::size() const {
	return m_size;
}

template<class T> unsigned long NList<T>::maxCapacity() const {
	return m_maxCapacity;
}

template<class T> unsigned long NList<T>::maxtCapacity() const {
	return m_maxtCapacity;
}

template<class T> unsigned long NList<T>::currentCapacity() const {
	return m_workingCapacity;
}

template<class T> bool NList<T>::isEmpty() {

	if (m_size == 0) {
		return true;
		
	} else { return false; }
}

template<class T> void NList<T>::displayList() {

	if (std::numeric_limits<T>::is_specialized) {

		mPtr = hPtr;

		while (mPtr != nullptr) {

			if (mPtr->data != std::numeric_limits<T>::max() && mPtr->data != std::numeric_limits<T>::min()) {
				std::cout << mPtr->data << ' ';
			}
			mPtr = mPtr->rlink;
		}
		
	} else {
		static_assert(std::numeric_limits<T>::is_specialized, "ERROR: cannot display list without class<T> numeric limits");
	}
}

template<class T> T NList<T>::at(const int& index) {

	if (indexing) {
		return arrInd[index]->data;
		
	} else {
		assert(("ERROR: indexing must be enabled for use of NList::operator[]", indexing));
		return T();
	}
}

/***** OPERATORS *****/

template<class T> T NList<T>::operator[](const int& index) {

	if (indexing) {
		return arrInd[index]->data;
		
	} else {
		assert(("ERROR: indexing must be enabled for use of NList::operator[]", indexing));
		return T();
	}
}

/***** MUTATORS *****/

template<class T> void NList<T>::assign(const T& p_newValue) {

	if (m_size < 1) {
		push_back(p_newValue);
		
	} else {
		mPtr = hPtr->rlink;

		while (mPtr->rlink != nullptr) {
			mPtr->data = p_newValue;
			mPtr = mPtr->rlink;
		}
	}
}

template<class T> void NList<T>::push_front(const T& p_newValue) {

	m_size++;
	mPtr = hPtr;
	temp = new Node;
	temp->data = p_newValue;
	temp->llink = mPtr;
	temp->rlink = mPtr->rlink;
	mPtr->rlink->llink = temp;
	mPtr->rlink = temp;

	if (indexing) {
		refreshIndex();
	}
}

template<class T> void NList<T>::push_back(const T& p_newValue) {

	m_size++;
	mPtr = tPtr->llink;
	temp = new Node;
	temp->data = p_newValue;
	temp->llink = mPtr;
	temp->rlink = mPtr->rlink;
	mPtr->rlink->llink = temp;
	mPtr->rlink = temp;

	if (indexing) {

		if (!firstIndexSet) {
			refreshIndex();
			
		} else {
			arrInd[m_size - 1] = temp;
		}
	}
}

template<class T> void NList<T>::pop_front() {

	mPtr = hPtr->rlink;
	mPtr->llink->rlink = mPtr->rlink;
	mPtr->rlink->llink = mPtr->llink;
	m_size--;

	if (indexing) {
		refreshIndex();
	}
}

template<class T> void NList<T>::pop_back() {

	mPtr = tPtr->llink;
	mPtr->llink->rlink = mPtr->rlink;
	mPtr->rlink->llink = mPtr->llink;
	m_size--;

	if (indexing) {
		arrInd[m_size] = nullptr;
	}
}

template<class T> void NList<T>::enableIndexing() {

	indexing = true;
	refreshIndex();
}

template<class T> void NList<T>::disableIndexing() {

	indexing = false;
}

template<class T> void NList<T>::erase(const T& p_eraseItem) {

	mPtr = hPtr;

	for (int i = 0; i < m_size + 1; i++) {

		if (mPtr->data == p_eraseItem) {
			
			mPtr->llink->rlink = mPtr->rlink;
			mPtr->rlink->llink = mPtr->llink;
			m_size--;
		}
		mPtr = mPtr->rlink;
	}
	refreshIndex();
}

template<class T> void NList<T>::clear() {

	mPtr = hPtr->rlink;

	while (mPtr->rlink != nullptr) {

		temp = mPtr;
		mPtr = mPtr->rlink;
		delete temp;
		m_size--;
	}

}

template<class T> void NList<T>::clearAllExcept(const T& keepVal) {

	mPtr = hPtr->rlink;

	int OGsize = m_size;

	for (int i = 0; i < OGsize; i++) {

		if (mPtr->data != keepVal) {
			mPtr->llink->rlink = mPtr->rlink;
			mPtr->rlink->llink = mPtr->llink;
			m_size--;
		}
		mPtr = mPtr->rlink;
	}
	refreshIndex();
}

template<class T> void NList<T>::sortAscending(){
	
	if (std::numeric_limits<T>::is_specialized){
		
		if(!indexing){
			refreshIndex();
		}
		bubbleSort(arrInd, m_size, false);
		mPtr = hPtr;
		
		for (int i = 0; i < m_size; i++) {
			
			mPtr = mPtr->rlink;
			mPtr->data = arrInd[i]->data;
		}
		refreshIndex();
		
	} else {
		
		static_assert(std::numeric_limits<T>::is_specialized, "ERROR: cannot sort list without class<T> numeric limits");
	}
}
template<class T> void NList<T>::sortDescending(){
	
	if (std::numeric_limits<T>::is_specialized){
		
		if(!indexing){
			refreshIndex();
		}
		bubbleSort(arrInd, m_size, true);
		mPtr = hPtr;
		
		for (int i = 0; i < m_size; i++) {
			
			mPtr = mPtr->rlink;
			mPtr->data = arrInd[i]->data;
		}
		refreshIndex();
		
	} else {
		
		static_assert(std::numeric_limits<T>::is_specialized, "ERROR: cannot sort list without class<T> numeric limits");
	}
}template<class T> void NList<T>::expandCapacity() {

	if (m_workingCapacity + 1000 < m_maxCapacity) {
		m_workingCapacity += 1000;
		
	} else  {
		assert(("ERROR: Capacity of list cannot exceed capacity defined in NList::maxCapacity()", overCap));
	}
	firstIndexSet = false;
	refreshIndex();
}

/***** PRIVATE HELPER FUNCTIONS *****/

template<class T> void NList<T>::bubbleSort(NList<T>::Node* arr[], int arrSize, bool desc){
	
	if (arrSize == 1) {
		return;
		
	} else {
		
		for (int i = 0; i < arrSize - 1; i++) {
			
			if (desc){
				
				if (arr[i + 1]->data > arr[i]->data) {
					std::swap(arr[i]->data, arr[i + 1]->data);
				}
			} else {
				
				if (arr[i + 1]->data < arr[i]->data) {
					std::swap(arr[i]->data, arr[i + 1]->data);
				}
			}
		}
		bubbleSort(arr, arrSize - 1, desc);
	}
}

template<class T> void NList<T>::refreshIndex() {

	if (!firstIndexSet) {
		arrInd = nullptr;
		arrInd = new Node*[m_workingCapacity];
		firstIndexSet = true;
	}
	mPtr = hPtr->rlink;

	for (int i = 0; i < m_size; i++) {
		arrInd[i] = mPtr;
		mPtr = mPtr->rlink;
	}
}

template<class T> void NList<T>::calcMemReqs() {

	std::list<T> tempList;
	unsigned long MAX_SIZE_OF_LIST = tempList.max_size();
	m_maxtCapacity = MAX_SIZE_OF_LIST / (NODE_SIZE + CLASS_SIZE);

	if (m_maxtCapacity > 100000) {
		m_maxtCapacity = 1000000;
	}
	m_maxCapacity = 10000;
}

#endif /* NLIST_HPP */
