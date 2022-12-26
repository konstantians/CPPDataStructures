#include "Queue.h"

template<typename T>
Queue<T>::~Queue() {
	delete m_InternalLinkedLinked;
}

template<typename T>
void Queue<T>::Enqueue(T data) {
	m_InternalLinkedLinked->AppendElementAtEnd(data);
	m_Length++;
}

template<typename T>
T Queue<T>::Dequeue() {
	if (m_Length <= 0) {
		throw("there are no elements in the queue");
	}
	m_Length--;
	return m_InternalLinkedLinked->RemoveFirstElement();
}

template<typename T>
T Queue<T>::Peek() {
	if (m_Length <= 0) {
		throw("there are no elements in the queue");
	}
	return m_InternalLinkedLinked->ReturnElementAtIndex(0);
}

template<typename T>
int Queue<T>::Size() {
	return m_Length;
}

template<typename T>
bool Queue<T>::IsEmpty() {
	return m_Length == 0;
}

template<typename T>
void Queue<T>::Clear() {
	m_InternalLinkedLinked->Clear();
	m_Length = 0;
}