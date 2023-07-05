#pragma once

#include <iostream>
#include <assert.h>

#include "ListNode.h"
using namespace std;

template <class T>
class QueueList
{
private:
	ListNode<T>* headP;
	ListNode<T>* tailP;
	int count;

public:
	QueueList();

	void enqueue(T*);
	T* dequeue();
	T* front();

	int length();
	bool isEmpty();

	bool elementExists(T*);
	T* getByIndex(int);
	T* removeID(long);

	void printQueue();

	~QueueList(void);
};

template <class T>
QueueList<T>::QueueList() :
	headP(nullptr),
	tailP(nullptr),
	count(0) {}

template <class T>
void QueueList<T>::enqueue(T* val)
{
	ListNode<T>* item = new ListNode<T>(val);

	if (count == 0)
	{
		headP = tailP = item;
	}
	else
	{
		tailP->setNextPointer(item);
		tailP = item;
	}

	count++;
}

template <class T>
T* QueueList<T>::dequeue()
{
	assert(headP != nullptr);

	T* value = headP->getValue();

	ListNode<T>* temp = headP->getNextPointer();
	delete(headP);
	headP = temp;
	count--;

	if (count == 0)
		tailP = nullptr;

	return value;
}

template <class T>
T* QueueList<T>::front() { return headP->getValue(); }

template <class T>
int QueueList<T>::length() { return count; }

template <class T>
bool QueueList<T>::isEmpty() { return (count == 0); }

template <class T>
bool QueueList<T>::elementExists(T* elm)
{
	ListNode<T>* temp = headP;
	while (temp != nullptr)
	{
		if (temp->getValue() == elm)
			return true;
		temp = temp->getNextPointer();
	}
	return false;
}

template <class T>
T* QueueList<T>::getByIndex(int ind)
{
	if (ind >= count)
		throw runtime_error("Index out of bounds!");

	ListNode<T>* temp = headP;
	for (int i = 0; i < ind; i++)
	{
		temp = temp->getNextPointer();
	}
	return temp->getValue();
}

template <class T>
T* QueueList<T>::removeID(long id)
{
	ListNode<T>* temp = headP, * previous = headP;
	int i = 0;
	long temp_id;
	for (; i < count; i++)
	{
		temp_id = *temp->getValue();
		if (temp_id == id)
			break;
		previous = temp;
		temp = temp->getNextPointer();
	}

	if (i == count)
		throw runtime_error("User doesn't exist!");

	T* val = temp->getValue();

	if (tailP == temp)
	{
		tailP = previous;
		tailP->setNextPointer(nullptr);
	}
	else if (headP == temp)
	{
		headP = headP->getNextPointer();
	}
	else
	{
		previous->setNextPointer(temp->getNextPointer());
	}

	count--;
	return val;
}

template <class T>
void QueueList<T>::printQueue()
{
	ListNode<T>* temp = headP;
	while (temp != nullptr)
	{
		std::cout << temp->getValue() << ", ";
		temp = temp->getNextPointer();
	}
	std::cout << std::endl;
}

template <class T>
QueueList<T>::~QueueList(void) {}