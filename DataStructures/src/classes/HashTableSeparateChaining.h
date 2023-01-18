#pragma once
#include "SinglyLinkedList.h"

template<typename K, typename V>
class HashTableSeparateChaining {

private:

    struct KeyValuePair {
        K key;
        V value;
    };

    double m_LoadFactor;
    int m_Length = 0;
    int m_Capacity = 0;
    SinglyLinkedList<KeyValuePair>** m_InternalLinkedListTable;

public:
    HashTableSeparateChaining();
    HashTableSeparateChaining(int capacity);
    HashTableSeparateChaining(int capacity, double loadFactor);    
    ~HashTableSeparateChaining();
    void AddElement(K key, V value);
    V GetValue(K key);
    V RemoveValue(K key);
    int GetSize();
    bool IsEmpty();
    void Clear();


private:
    void destroyTable(SinglyLinkedList<KeyValuePair>** m_InternalLinkedListTable, int capacity);
    int hashFunction(K key);
    void initializeTheInternalArray(SinglyLinkedList<KeyValuePair>** m_InternalLinkedListTable);
};