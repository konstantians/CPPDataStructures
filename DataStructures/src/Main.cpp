#include <iostream>
#include "classes/DynamicArray.h"
#include "classes/DynamicArray.cpp"
#include "classes/SinglyLinkedList.h"
#include "classes/SinglyLinkedList.cpp"
#include "classes/Stack.h"
#include "classes/Stack.cpp"
#include "classes/Queue.h"
#include "classes/Queue.cpp"

#define print(x) std::cout << x << std::endl

template <typename T>
class PriorityQueue {
private:
    DynamicArray<T>* m_InternalDynamicArray = new DynamicArray<T>;
    int m_Length = 0;
public:

    ~PriorityQueue()
    {
        delete[] m_InternalDynamicArray;
    }

public:
    void Add(T value) {
        m_InternalDynamicArray->AppendElement(value);
        BubbleUp(m_Length);

        m_Length++;
    }

    T Poll() {
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

    int Remove(T value){
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

    T RemoveAt(int index) {
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

    void PrintInternalArray() {
        for (int i = 0; i < m_Length; i++) {
            if (i + 1 == m_Length) {
                std::cout << m_InternalDynamicArray->GetElement(i);
                break;
            }
            std::cout << m_InternalDynamicArray->GetElement(i) << " , ";
        }
        print("");
    }

    bool Contains(T value) {

        for (int i = 0; i < m_Length; i++) {
            if (m_InternalDynamicArray->GetElement(i) == value) {
                return true;
            }
        }
        return false;
    }

    int ContainsAtIndex(T value) {

        for (int i = 0; i < m_Length; i++) {
            if (m_InternalDynamicArray->GetElement(i) == value) {
                return i;
            }
        }
        return -1;
    }

    bool IsEmpty() {
        return m_Length == 0;
    }

    int GetSize() {
        return m_Length;
    }

private:
    void BubbleUp(int currentPosition) {
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
            m_InternalDynamicArray->ChangeElementAtIndex(currentPosition ,m_InternalDynamicArray->GetElement(nextPosition));
            m_InternalDynamicArray->ChangeElementAtIndex(nextPosition, temp);
            BubbleUp(nextPosition);
        }

        //if it is not we are at the right position
        return;
    }

    void BubbleDown(int currentPosition) {
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

};


int main()
{
    //created on the heap
    //DynamicArray<int>* myDynamicArray = new DynamicArray<int>;
    //SinglyLinkedList<int>* mySinglyLinkedList = new SinglyLinkedList<int>;
    //Stack<int>* myStack = new Stack<int>;
    //Queue<int>* myQueue = new Queue<int>;
    //PriorityQueue<int>* myPriorityQueue = new PriorityQueue<int>;
    
    //created on the stack
    //DynamicArray<int> myDynamicArray = DynamicArray<int>();
    //SinglyLinkedList<int> mySinglyLinkedList = SinglyLinkedList<int>();
    //Stack<int> myStack = Stack<int>();
    //Queue<int> myQueue = Queue<int>();
    //PriorityQueue<int> myPriorityQueue = PriorityQueue<int>();
}
