#include "PriorityQueue.h"

#define print(x) std::cout << x << std::endl;

template<typename T>    
PriorityQueue<T>::~PriorityQueue()
{
    delete m_InternalDynamicArray;
}

template<typename T>
void PriorityQueue<T>::Add(T value) {
    m_InternalDynamicArray->AppendElement(value);
    BubbleUp(m_Length);

    m_Length++;
}

template<typename T>
T PriorityQueue<T>::Poll() {
    if (m_Length <= 0) {
        throw("there are no elements in the priority queue");
    }

    T returnedValue = m_InternalDynamicArray->GetElement(0);
    m_InternalDynamicArray->ChangeElementAtIndex(0, m_InternalDynamicArray->GetElement(m_Length - 1));
    m_InternalDynamicArray->ChangeElementAtIndex(m_Length - 1, returnedValue);

    returnedValue = m_InternalDynamicArray->RemoveElementAtIndex(m_Length - 1);
    m_Length--;

    BubbleDown(0);

    return returnedValue;
}

template<typename T>
int PriorityQueue<T>::Remove(T value) {
    int index = -1;
    //linear scan to find the element
    for (int i = 0; i < m_Length; i++) {
        if (m_InternalDynamicArray->GetElement(i) == value) {
            index = i;
            break;
        }
    }

    //if the element was not found
    if (index == -1) {
        return -1;
    }
    //otherwise
    T temp = m_InternalDynamicArray->GetElement(index);
    m_InternalDynamicArray->ChangeElementAtIndex(index, m_InternalDynamicArray->GetElement(m_Length - 1));
    m_InternalDynamicArray->ChangeElementAtIndex(m_Length - 1, temp);

    m_InternalDynamicArray->RemoveElementAtIndex(m_Length - 1);
    m_Length--;
    //fixes a bug(we remove the last element)
    if (m_Length == index) return index;
    //check if we have to bubble up
    BubbleUp(index);
    //check if we have to bubble down
    BubbleDown(index);

    return index;
}

template<typename T>
T PriorityQueue<T>::RemoveAt(int index) {
    if (index < 0 || index > m_Length) {
        throw("index out of bounds");
    }

    T returnedValue = m_InternalDynamicArray->GetElement(index);
    m_InternalDynamicArray->ChangeElementAtIndex(index, m_InternalDynamicArray->GetElement(m_Length - 1));
    m_InternalDynamicArray->ChangeElementAtIndex(m_Length - 1, returnedValue);

    m_InternalDynamicArray->RemoveElementAtIndex(m_Length - 1);
    m_Length--;
    //fixes a bug(we remove the last element)
    if (m_Length == index) return returnedValue;
    //check if we have to bubble up
    BubbleUp(index);
    //check if we have to bubble down
    BubbleDown(index);

    return returnedValue;
}

template<typename T>
void PriorityQueue<T>::PrintInternalArray() {
    for (int i = 0; i < m_Length; i++) {
        if (i + 1 == m_Length) {
            std::cout << m_InternalDynamicArray->GetElement(i);
            break;
        }
        std::cout << m_InternalDynamicArray->GetElement(i) << " , ";
    }
    print("");
}

template<typename T>
bool PriorityQueue<T>::Contains(T value) {

    for (int i = 0; i < m_Length; i++) {
        if (m_InternalDynamicArray->GetElement(i) == value) {
            return true;
        }
    }
    return false;
}

template<typename T>
int PriorityQueue<T>::ContainsAtIndex(T value) {

    for (int i = 0; i < m_Length; i++) {
        if (m_InternalDynamicArray->GetElement(i) == value) {
            return i;
        }
    }
    return -1;
}

template<typename T>
bool PriorityQueue<T>::IsEmpty() {
    return m_Length == 0;
}

template<typename T>
int PriorityQueue<T>::GetSize() {
    return m_Length;
}

template<typename T>
void PriorityQueue<T>::Clear() {
    delete[] m_InternalDynamicArray;
    m_Length = 0;
    m_InternalDynamicArray = new DynamicArray<T>();
}

template<typename T>
void PriorityQueue<T>::BubbleUp(int currentPosition) {
    //base case
    if (currentPosition == 0) return;

    //find next position
    int nextPosition;
    if (currentPosition % 2 == 0) {
        nextPosition = (currentPosition - 2) / 2;
    }
    else {
        nextPosition = (currentPosition - 1) / 2;
    }

    //check if we must bubble up
    if (m_InternalDynamicArray->GetElement(nextPosition) > m_InternalDynamicArray->GetElement(currentPosition)) {
        T temp = m_InternalDynamicArray->GetElement(currentPosition);
        m_InternalDynamicArray->ChangeElementAtIndex(currentPosition, m_InternalDynamicArray->GetElement(nextPosition));
        m_InternalDynamicArray->ChangeElementAtIndex(nextPosition, temp);
        BubbleUp(nextPosition);
    }

    //if it is not we are at the right position
    return;
}

template<typename T>
void PriorityQueue<T>::BubbleDown(int currentPosition) {
    //find next position
    int nextPositionLeft = currentPosition * 2 + 1;
    int nextPositionRight = currentPosition * 2 + 2;
    int greatestPosition = currentPosition;

    if (nextPositionLeft < m_Length) {
        //check if the left child is the greatest element
        if (m_InternalDynamicArray->GetElement(nextPositionLeft) < m_InternalDynamicArray->GetElement(currentPosition)) {
            greatestPosition = nextPositionLeft;
        }
    }



    if (nextPositionRight < m_Length)
    {
        //check if the right child is the greatest element
        if (m_InternalDynamicArray->GetElement(nextPositionRight) < m_InternalDynamicArray->GetElement(greatestPosition)) {
            greatestPosition = nextPositionRight;
        }
    }


    //if the element did not change, it is on the right spot
    if (greatestPosition == currentPosition) return;
    //else swap the element with the correct element and repeat the process
    else {
        T temp = m_InternalDynamicArray->GetElement(currentPosition);
        m_InternalDynamicArray->ChangeElementAtIndex(currentPosition, m_InternalDynamicArray->GetElement(greatestPosition));
        m_InternalDynamicArray->ChangeElementAtIndex(greatestPosition, temp);
        BubbleDown(greatestPosition);
    }
}
