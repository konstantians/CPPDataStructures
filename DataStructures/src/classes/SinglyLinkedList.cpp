#include "SinglyLinkedList.h"

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
	Clear();
}

template<typename T>
void SinglyLinkedList<T>::AppendElementAtEnd(T value) {
	Node* tempNode = new Node;
	tempNode->data = value;
	tempNode->pointer = nullptr;
	if (m_Length == 0) {
		m_Head = tempNode;
		m_Tail = tempNode;
		m_Length++;

		return;
	}
	else if (m_Length == 1) {
		m_Head->pointer = tempNode;
		m_Tail = tempNode;
		m_Length++;

		return;
	}
	//otherwise
	m_Tail->pointer = tempNode;
	m_Tail = tempNode;
	m_Length++;
}

template<typename T>
void SinglyLinkedList<T>::AppendElementAtStart(T value) {
	Node* tempNode = new Node;
	tempNode->data = value;
	tempNode->pointer = nullptr;
	if (m_Length == 0) {
		m_Head = tempNode;
		m_Tail = tempNode;
		m_Length++;

		return;
	}
	else if (m_Length == 1) {
		m_Head = tempNode;
		m_Head->pointer = m_Tail;
		m_Length++;

		return;
	}
	//otherwise
	tempNode->pointer = m_Head;
	m_Head = tempNode;
	m_Length++;
}

template<typename T>
void SinglyLinkedList<T>::AppendElementAtIndex(int index, T value) {
	Node* tempNode = new Node;
	tempNode->data = value;
	tempNode->pointer = nullptr;
	if (index == 0) {
		AppendElementAtStart(value);
		return;
	}
	if (index == m_Length) {
		AppendElementAtEnd(value);
		return;
	}
	if (index <= -1 || index > m_Length) {
		throw("index out of bounds");
	}

	Node* traversingNode = m_Head;
	for (int i = 0; i < m_Length; i++) {
		if (i + 1 == index) {
			tempNode->pointer = traversingNode->pointer;
			traversingNode->pointer = tempNode;
			m_Length++;
			return;
		}
		traversingNode = traversingNode->pointer;
	}
}

template<typename T>
T SinglyLinkedList<T>::RemoveLastElement() {
	if (m_Length == 0) {
		throw("there are not elements in the linked list");
	}
	if (m_Length == 1) {
		T returnedValue = m_Tail->data;

		delete m_Head;
		Node* m_Head = new Node;
		Node* m_Tail = m_Head;
		m_Length--;

		return returnedValue;
	}
	//otherwise
	Node* traversingNode = m_Head;
	for (int i = 0; i < m_Length; i++) {
		if (i + 2 == m_Length) {
			T returnedValue = m_Tail->data;

			traversingNode->pointer = nullptr;
			delete m_Tail;
			m_Tail = traversingNode;
			m_Length--;

			return returnedValue;
		}
		traversingNode = traversingNode->pointer;
	}
}

template<typename T>
T SinglyLinkedList<T>::RemoveFirstElement() {
	if (m_Length == 0) {
		throw("there are not elements in the linked list");
	}
	if (m_Length == 1) {
		T returnedValue = m_Head->data;

		delete m_Head;
		Node* m_Head = new Node;
		Node* m_Tail = m_Head;
		m_Length--;

		return returnedValue;
	}

	T returnedValue = m_Head->data;
	//otherwise
	Node* tempNode = m_Head->pointer;
	delete m_Head;
	m_Head = tempNode;
	m_Length--;

	return returnedValue;
}

template<typename T>
T SinglyLinkedList<T>::RemoveElementAtIndex(int index) {
	if (index == 0) {
		return RemoveFirstElement();
	}
	if (index == m_Length) {
		return RemoveLastElement();

	}
	if (index <= -1 || index > m_Length) {
		throw("index out of bounds");
	}
	//m_Head->pointer->pointer;
	//otherwise
	Node* traversingNode = m_Head;
	for (int i = 0; i < m_Length; i++) {
		if (i + 1 == index) {
			T returnedValue = traversingNode->pointer->data;

			Node* tempNode = traversingNode->pointer;
			traversingNode->pointer = tempNode->pointer;
			delete tempNode;

			m_Length--;

			return returnedValue;
		}
		traversingNode = traversingNode->pointer;
	}
}

template<typename T>
bool SinglyLinkedList<T>::RemoveElement(T value) {
	if (m_Length == 0) return false;
	if (m_Head->data == value) {
		RemoveFirstElement();
		return true;
	}
	if (m_Tail->data == value) {
		RemoveLastElement();
		return true;
	}
	//m_Head->pointer->pointer;
	//otherwise
	Node* traversingNode = m_Head;
	for (int i = 0; i < m_Length; i++) {
		//fixes the bug
		if (traversingNode->pointer == m_Tail) {
			break;
		}

		if (traversingNode->pointer->data == value) {
			T returnedValue = traversingNode->pointer->data;

			Node* tempNode = traversingNode->pointer;
			traversingNode->pointer = tempNode->pointer;
			delete tempNode;

			m_Length--;

			return true;
		}
		traversingNode = traversingNode->pointer;
	}

	return false;
}

template<typename T>
T SinglyLinkedList<T>::ReturnElementAtIndex(int index) {
	if (index < 0 || index >= m_Length) {
		throw("index out of bounds");
	}

	if (m_Length == 0) {
		throw("the linked list is empty");
	}

	Node* traversingNode = m_Head;
	for (int i = 0; i < m_Length; i++) {
		if (i == index) {
			return traversingNode->data;
		}
		traversingNode = traversingNode->pointer;
	}
}

template<typename T>
bool SinglyLinkedList<T>::Contains(T value) {

	if (m_Length == 0) {
		throw("the linked list is empty");
	}

	Node* traversingNode = m_Head;
	for (int i = 0; i < m_Length; i++) {
		if (traversingNode->data == value) {
			return true;
		}
		traversingNode = traversingNode->pointer;
	}

	return false;
}

template<typename T>
int SinglyLinkedList<T>::ContainsAtIndex(T value) {

	if (m_Length == 0) {
		throw("the linked list is empty");
	}

	Node* traversingNode = m_Head;
	for (int i = 0; i < m_Length; i++) {
		if (traversingNode->data == value) {
			return i;
		}
		traversingNode = traversingNode->pointer;
	}

	return -1;
}

template<typename T>
int SinglyLinkedList<T>::GetSize() {
	return m_Length;
}

template<typename T>
bool SinglyLinkedList<T>::IsEmpty() {
	return m_Length == 0;
}

template<typename T>
void SinglyLinkedList<T>::Clear() {
	Node* traversingNode = m_Head;
	for (int i = 0; i < m_Length - 1; i++) {
	Node* tempNode = traversingNode->pointer;
		delete traversingNode;
		traversingNode = tempNode;
	}
}