#include "DynamicArray.h"

template<typename T>
DynamicArray<T>::DynamicArray() : m_Length(0), m_Capacity(5)
{
}

template<typename T>
DynamicArray<T>::DynamicArray(int capacity) : m_Length(0), m_Capacity(capacity)
{
	m_InternalArray = new T[m_Capacity];
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
	delete[] m_InternalArray;
}

template<typename T>
int DynamicArray<T>::GetSize() {
	return m_Length;
}

template<typename T>
bool DynamicArray<T>::IsEmpty() {
	return m_Length == 0;
}

template<typename T>
bool DynamicArray<T>::Contains(T value) {
	//if the dynamic array is empty
	if (m_Length == 0) return false;

	//otherwise search for it
	for (int i = 0; i < m_Length; i++) {
		if (m_InternalArray[i] == value)
			return true;
	}
	return false;
}

template<typename T>
int DynamicArray<T>::ContainsAtIndex(T value) {
	//if the dynamic array is empty
	if (m_Length == 0) return -1;

	//otherwise search for it
	for (int i = 0; i < m_Length; i++) {
		if (m_InternalArray[i] == value)
			return i;
	}
	return -1;
}

template<typename T>
void DynamicArray<T>::AppendElement(T value) {
	//if we are in the bounds
	if (m_Length < m_Capacity) {
		m_InternalArray[m_Length] = value;
		m_Length++;
		return;
	}
	//else
	m_Capacity = m_Capacity * 2;
	T* temp_Array = new T[m_Capacity];

	for (int i = 0; i < m_Capacity / 2; i++) {
		temp_Array[i] = m_InternalArray[i];
	}
	temp_Array[m_Capacity / 2] = value;

	delete[] m_InternalArray;
	m_InternalArray = temp_Array;

	m_Length++;
}

template<typename T>
void DynamicArray<T>::ChangeElementAtIndex(int index, T value) {
	//if the user gives a bad index
	if (index < 0 || index >= m_Length) {
		throw("out of bounds index");
	}

	m_InternalArray[index] = value;
}

template<typename T>
int DynamicArray<T>::PopElement() {
	if (m_Length <= 0) {
		throw("there are no elements in the dynamic array");
	}

	//we do not need to overwrite the value of the element, because 
	//by minimizing the length we can not access it
	m_Length--;
	return(m_InternalArray[m_Length]);
}

template<typename T>
int DynamicArray<T>::RemoveElementAtIndex(int index) {
	//if the user gives a bad index
	if (index < 0 || index >= m_Length) {
		throw("out of bounds index");
	}


	T returnedValue = m_InternalArray[index];
	for (int i = index; i < m_Length - 1; i++) {
		m_InternalArray[i] = m_InternalArray[i + 1];
	}
	m_Length--;
	return(returnedValue);
}

template<typename T>
bool DynamicArray<T>::RemoveElement(T value) {
	//if the dynamic array is empty
	if (m_Length == 0) return false;

	for (int i = 0; i < m_Length; i++) {
		if (m_InternalArray[i] == value) {
			RemoveElementAtIndex(i);
			return true;
		}
	}

	return false;
}

template<typename T>
int DynamicArray<T>::GetElement(int index) {
	//if the user gives a bad index
	if (index < 0 || index >= m_Length) {
		throw("out of bounds index");
	}

	return m_InternalArray[index];
}

//essentionally bubble sort, because I am bored
template<typename T>
void DynamicArray<T>::Sort() {
	for (int i = 0; i < m_Length; i++) {
		bool exitLoop = true;
		for (int j = 0; j < m_Length - 1; j++) {
			if (m_InternalArray[j] > m_InternalArray[j + 1]) {
				int temp = m_InternalArray[j];
				m_InternalArray[j] = m_InternalArray[j + 1];
				m_InternalArray[j + 1] = temp;

				exitLoop = false;
			}
		}

		if (exitLoop) return;
	}
}

template<typename T>
void DynamicArray<T>::Clear() {
	delete[] m_InternalArray;
	m_Capacity = 5;
	m_Length = 0;
	m_InternalArray = new T[5];
}