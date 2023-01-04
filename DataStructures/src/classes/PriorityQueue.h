#pragma once
#include "DynamicArray.h"
#include <iostream>

template <typename T>
class PriorityQueue {
private:
    DynamicArray<T>* m_InternalDynamicArray = new DynamicArray<T>;
    int m_Length = 0;

public:
    ~PriorityQueue();
public:
    void Add(T value);
    T Poll();
    int Remove(T value);
    T RemoveAt(int index);
    void PrintInternalArray();
    bool Contains(T value);
    int ContainsAtIndex(T value);
    bool IsEmpty();
    int GetSize();
    void Clear();
private:
    void BubbleUp(int currentPosition);
    void BubbleDown(int currentPosition);
};