
#pragma once

template<typename T>
class DynamicArray
{
private:
	int m_Length;
	int m_Capacity;
	T* m_InternalArray = new T[5];
public:
	DynamicArray();
	DynamicArray(int capacity);
	~DynamicArray();

public:
	int GetSize();
	bool IsEmpty();
	bool Contains(T value);
	int ContainsAtIndex(T value);
	void AppendElement(T value);
	void ChangeElementAtIndex(int index, T value);
	int PopElement();
	int RemoveElementAtIndex(int index);
	bool RemoveElement(T value);
	int GetElement(int index);
	void Sort();
	void Clear();
};


