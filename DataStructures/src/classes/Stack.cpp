#include "Stack.h"

template <typename T>
Stack<T>::~Stack() {
	delete m_InternalLinkedList;
}

template <typename T>
void Stack<T>::Push(T data) {
	m_InternalLinkedList->AppendElementAtStart(data);
	m_Length++;
}

template <typename T>
T Stack<T>::Pop() {
	if (m_Length <= 0) {
		throw("there are no elements in the stack");
	}
	m_Length--;
	return m_InternalLinkedList->RemoveFirstElement();
}

template <typename T>
T Stack<T>::Peek() {
	if (m_Length <= 0) {
		throw("there are no elements in the stack");
	}
	return m_InternalLinkedList->ReturnElementAtIndex(0);
}

template <typename T>
bool Stack<T>::IsEmpty() {
	return m_Length == 0;
}

template <typename T>
int Stack<T>::GetSize() {
	return m_Length;
}

template <typename T>
void Stack<T>::Clear() {
	m_InternalLinkedList->Clear();
	m_Length = 0;
}


