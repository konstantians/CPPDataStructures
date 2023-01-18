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
	Node* m_CurrentNode;

public:
	~SinglyLinkedList();

public:
	void AppendElementAtEnd(T value);
	void AppendElementAtStart(T value);
	void AppendElementAtIndex(int index, T value);
	T RemoveLastElement();
	T RemoveFirstElement();
	T RemoveElementAtIndex(int index);
	T ReturnElementAtIndex(int index);
	T IterrateOverList();
	void ResetIterator();
	bool RemoveElement(T value);
	bool Contains(T value);
	int ContainsAtIndex(T value);
	int GetSize() const;
	bool IsEmpty() const;
	void Clear();
};