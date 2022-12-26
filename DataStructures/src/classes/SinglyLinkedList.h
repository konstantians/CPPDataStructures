#pragma once

template<typename T>
class SinglyLinkedList {
private:
	struct Node
	{
		T data;
		Node* pointer;
	};

	int m_Length = 0;
	Node* m_Head = new Node;
	Node* m_Tail = m_Head;

public:
	~SinglyLinkedList();

public:
	void AppendElementAtEnd(T value);
	void AppendElementAtStart(T value);
	void AppendElementAtIndex(int index, T value);
	T RemoveLastElement();
	T RemoveFirstElement();
	T RemoveElementAtIndex(int index);
	bool RemoveElement(T value);
	T ReturnElementAtIndex(int index);
	bool Contains(T value);
	int ContainsAtIndex(T value);
	int GetSize();
	bool IsEmpty();
	void Clear();
};