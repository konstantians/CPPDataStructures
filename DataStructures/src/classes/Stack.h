#pragma once
#include "SinglyLinkedList.h"

//we push and pop from the head for performance(to avoid asymptotic complexity of O(n))
//if the stack was implemented with a different data structure (for example doubly linked list), then we could do 
//the push, pop and peek operation from the tail too
template<typename T>
class Stack
{
private:
	SinglyLinkedList<T>* m_InternalLinkedList = new SinglyLinkedList<T>;
	int m_Length = 0;
public:
	~Stack();
	void Push(T data);
	T Pop();
	T Peek();
	bool IsEmpty();

	int GetSize();
	void Clear();
};
