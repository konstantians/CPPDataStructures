#include "HashTableSeparateChaining.h"
#include "SinglyLinkedList.h"
#include <iostream>

template<typename K, typename V>
HashTableSeparateChaining<K, V>::HashTableSeparateChaining()
{
    m_LoadFactor = 0.75;
    m_Capacity = 10;
    m_InternalLinkedListTable = new SinglyLinkedList<KeyValuePair>*[10];
    initializeTheInternalArray(m_InternalLinkedListTable);
}


template<typename K, typename V>
HashTableSeparateChaining<K, V>::HashTableSeparateChaining(int capacity) : m_Capacity(capacity)
{
    m_LoadFactor = 0.75;
    m_InternalLinkedListTable = new SinglyLinkedList<KeyValuePair>*[capacity];
    initializeTheInternalArray(m_InternalLinkedListTable);
}


template<typename K, typename V>
HashTableSeparateChaining<K, V>::HashTableSeparateChaining(int capacity, double loadFactor) : m_Capacity(capacity), m_LoadFactor(loadFactor) {
    if (m_LoadFactor > 1 || m_LoadFactor <= 0) {
        throw std::invalid_argument("load factor must be greater than 0 and less or equal than one");
    }
    m_InternalLinkedListTable = new SinglyLinkedList<KeyValuePair>*[capacity];
    initializeTheInternalArray(m_InternalLinkedListTable);
}


template<typename K, typename V>
HashTableSeparateChaining<K, V>::~HashTableSeparateChaining() {
    destroyTable(m_InternalLinkedListTable, m_Capacity);
}


template<typename K, typename V>
void HashTableSeparateChaining<K, V>::AddElement(K key, V value) {
    int hashedKey = hashFunction(key);
    KeyValuePair* kV = new KeyValuePair();
    kV->key = key;
    kV->value = value;

    //check if the key already exists(I know that this makes it take O(n worst cast cenario))
    for (int i = 0; i < m_InternalLinkedListTable[hashedKey]->GetSize(); i++) {
        //use iterator
        KeyValuePair kVTempStack = m_InternalLinkedListTable[hashedKey]->IterrateOverList();
        if (kVTempStack.key == key) {
            //reset iterator
            m_InternalLinkedListTable[hashedKey]->ResetIterator();
            throw("you inserted a duplicate key");
        }
    }

    //if we have not surpassed the limit
    if (m_LoadFactor * m_Length < m_Capacity) {
        m_InternalLinkedListTable[hashedKey]->AppendElementAtStart(*kV);
        m_Length++;
        return;
    }

    m_Capacity *= 2;
    SinglyLinkedList<KeyValuePair>** tempLinkedListTable = new SinglyLinkedList<KeyValuePair>*[m_Capacity];
    initializeTheInternalArray(tempLinkedListTable);


    for (int i = 0; i < m_Capacity / 2; i++) {
        //TODO fix this to be better
        //as long as the linked list is not empty
        while (!(m_InternalLinkedListTable[i]->IsEmpty())) {
            //get the key value pair
            KeyValuePair kVTempStack = m_InternalLinkedListTable[i]->RemoveFirstElement();
            KeyValuePair* kVTemp = &kVTempStack;
            //hash it with the updated hash function
            int hashedKeyForTemp = hashFunction(kVTemp->key);

            //add it to the new table
            tempLinkedListTable[hashedKeyForTemp]->AppendElementAtStart(*kVTemp);
        }
    }

    //destroy table
    destroyTable(m_InternalLinkedListTable, m_Capacity / 2);

    m_InternalLinkedListTable = tempLinkedListTable;
    //add the new element with the new hashfunction
    hashedKey = hashFunction(key);
    m_InternalLinkedListTable[hashedKey]->AppendElementAtStart(*kV);
    m_Length++;

}

//TODO fix the speed on that. Get an iterator for the linked list

template<typename K, typename V>
V HashTableSeparateChaining<K, V>::GetValue(K key) {
    int hashedKey = hashFunction(key);
    for (int i = 0; i < m_InternalLinkedListTable[hashedKey]->GetSize(); i++) {
        //use iterator
        KeyValuePair kVTempStack = m_InternalLinkedListTable[hashedKey]->IterrateOverList();
        if (kVTempStack.key == key) {
            //reset iterator
            m_InternalLinkedListTable[hashedKey]->ResetIterator();
            return kVTempStack.value;
        }
    }
    throw("the element does not exist");
}


template<typename K, typename V>
V HashTableSeparateChaining<K, V>::RemoveValue(K key) {
    int hashedKey = hashFunction(key);
    for (int i = 0; i < m_InternalLinkedListTable[hashedKey]->GetSize(); i++) {
        //use iterator
        KeyValuePair kVTempStack = m_InternalLinkedListTable[hashedKey]->IterrateOverList();
        if (kVTempStack.key == key) {
            //reset iterator
            m_InternalLinkedListTable[hashedKey]->ResetIterator();
            m_InternalLinkedListTable[hashedKey]->RemoveElementAtIndex(i);
            m_Length--;
            return kVTempStack.value;
        }
    }
    throw("the element does not exist");
}


template<typename K, typename V>
int HashTableSeparateChaining<K, V>::GetSize() {
    return m_Length;
}


template<typename K, typename V>
bool HashTableSeparateChaining<K, V>::IsEmpty() {
    return m_Length == 0;
}


template<typename K, typename V>
void HashTableSeparateChaining<K, V>::Clear() {
    destroyTable(m_InternalLinkedListTable, m_Capacity);

    m_InternalLinkedListTable = new SinglyLinkedList<KeyValuePair>*[10];
    m_Length = 0;
    m_Capacity = 10;
    initializeTheInternalArray(m_InternalLinkedListTable);
}

template<typename K, typename V>
void HashTableSeparateChaining<K, V>::destroyTable(SinglyLinkedList<HashTableSeparateChaining<K, V>::KeyValuePair>** m_InternalLinkedListTable, int capacity) {
    for (int i = 0; i < capacity; i++) {
        delete m_InternalLinkedListTable[i];
    }
    delete m_InternalLinkedListTable;
}

template<typename K, typename V>
int HashTableSeparateChaining<K, V>::hashFunction(K key) {
    size_t key_hash = std::hash<K>()(key);
    return key_hash % m_Capacity;
}

template<typename K, typename V>
void HashTableSeparateChaining<K, V>::initializeTheInternalArray(SinglyLinkedList<HashTableSeparateChaining<K, V>::KeyValuePair>** m_InternalLinkedListTable) {
    for (int i = 0; i < m_Capacity; i++) {
        SinglyLinkedList<KeyValuePair>* singlyLinkedList = new SinglyLinkedList<KeyValuePair>();
        m_InternalLinkedListTable[i] = singlyLinkedList;
    }
}