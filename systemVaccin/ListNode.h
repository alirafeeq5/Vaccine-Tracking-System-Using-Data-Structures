#pragma once

template <class T>
class ListNode
{
private:
	T* valueP;
	ListNode<T>* nextP;

public:
	ListNode();
	ListNode(T*);
	ListNode(T*, ListNode<T>*);

	T* getValue();
	ListNode<T>* getNextPointer();
	ListNode<T> getNext();

	void setValue(T*);
	void setNextPointer(ListNode<T>*);

	bool isNextNull();

	~ListNode(void);
};

template <class T>
ListNode<T>::ListNode() :
	valueP(NULL),
	nextP(nullptr) {}

template <class T>
ListNode<T>::ListNode(T* val) :
	valueP(val),
	nextP(nullptr) {}

template <class T>
ListNode<T>::ListNode(T* val, ListNode<T>* n) :
	valueP(val),
	nextP(n) {}

template <class T>
T* ListNode<T>::getValue() { return valueP; }

template <class T>
ListNode<T> ListNode<T>::getNext() { return *nextP; }

template <class T>
ListNode<T>* ListNode<T>::getNextPointer() { return nextP; }

template <class T>
void ListNode<T>::setValue(T* val) { valueP = val; }

template <class T>
void ListNode<T>::setNextPointer(ListNode<T>* n) { nextP = n; }

template <class T>
bool ListNode<T>::isNextNull() { return (nextP == nullptr); }

template <class T>
ListNode<T>::~ListNode(void) {}