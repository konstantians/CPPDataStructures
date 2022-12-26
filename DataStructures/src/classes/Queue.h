#pragma once
#include "SinglyLinkedList.h"
//the dequeu happens at the head of the linked list and the enqueue at the tail of the linked list
//for performance reasons(to avoid O(n)). If the queue was implemented with a different data structure
//then we could have implemented it the other way around.
template<typename T>
class Queue {

private:
	int m_Length = 0;
	SinglyLinkedList<T>* m_InternalLinkedLinked = new SinglyLinkedList<T>;

public:
	~Queue();
	void Enqueue(T data);
	T Dequeue();
	T Peek();
	int Size();
	bool IsEmpty();
	void Clear();
};