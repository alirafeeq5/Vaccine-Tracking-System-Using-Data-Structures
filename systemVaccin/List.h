#pragma once

#include "ListNode.h"
#include "User.h"

using namespace std;

template <class T>
class List
{
private:
	ListNode<T>* headP;
	ListNode<T>* tailP;
	int count;

public:
	List();
	void add(T*);
	T* getByIndex(int);
	T* getUserByID(long);
	T* removeByIndex(int);
	T* removeUserByID(long);
	int length();
	void printList();
};

template <class T>
List<T>::List() :
	headP(nullptr),
	tailP(nullptr),
	count(0) {}

template <class T>
void List<T>::add(T* val)
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
T* List<T>::getByIndex(int ind)
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
T* List<T>::getUserByID(long id)
{
	bool isUser = std::is_same<T, User>::value;
	if (!isUser)
		throw runtime_error("List doesn't hold users!");
	
	ListNode<T>* temp = headP;
	int temp_id;
	for (int i = 0; i < count; i++)
	{
		temp_id = ((User*)temp->getValue())->userId;
		if (temp_id == id)
			return temp->getValue();
		temp = temp->getNextPointer();
	}
	throw runtime_error("User doesn't exist!");
}

template <class T>
T* List<T>::removeByIndex(int ind)
{
	if (ind >= count)
		throw runtime_error("Index out of bounds!");

	ListNode<T>* temp = headP, *previous = headP;
	int i = 0;
	for (; i < ind; i++)
	{
		previous = temp;
		temp = temp->getNextPointer();
	}
	
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
T* List<T>::removeUserByID(long id)
{
	bool isUser = std::is_same<T, User>::value;
	if (!isUser)
		throw runtime_error("List doesn't hold users!");

	ListNode<T>* temp = headP, *previous = headP;
	int i = 0;
	long temp_id;
	for (; i < count; i++)
	{
		temp_id = ((User*)temp->getValue())->userId;
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
int List<T>::length()
{
	return count;
}

template <class T>
void List<T>::printList()
{
	ListNode<T>* temp = headP;
	for (int i = 0; i < count; i++)
	{
		cout << temp->getValue() << ", ";
		temp = temp->getNextPointer();
	}
	cout << endl;
}