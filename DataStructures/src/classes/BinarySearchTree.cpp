#include "BinarySearchTree.h"
#include "Queue.h"

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    //uses this method to traverse all nodes and to delete them
    LevelOrder(true);
    m_Length = 0;
}

template<typename T>
void BinarySearchTree<T>::AddElement(T value) {
    //if there are no elements
    if (m_Length == 0) {
        root->leftChild = nullptr;
        root->rightChild = nullptr;
        root->data = value;
        m_Length++;
        return;
    }
    //else
    DiveDownToAdd(value, root);
    m_Length++;
}

template<typename T>
T BinarySearchTree<T>::RemoveRoot() {
    if (m_Length == 0) {
        throw("there are no elements in the binary search tree");
    }

    T returnedValue = root->data;

    if (m_Length == 1) {
        delete root;
    }
    else if (root->leftChild != nullptr && root->rightChild == nullptr) {
        Node* tempNode = root->leftChild;
        delete root;
        root = tempNode;
    }
    else if (root->leftChild == nullptr && root->rightChild != nullptr) {
        Node* tempNode = root->rightChild;
        delete root;
        root = tempNode;
    }
    //both are not null
    else {
        Node* temp = DiveDownToReplace(root);

        //case where the left child of root does not have any right children
        if (temp == root->leftChild) {
            temp->leftChild = root->leftChild->leftChild;
        }
        //case where the lift child has at least one right child
        else {
            temp->leftChild = root->leftChild;
        }
        temp->rightChild = root->rightChild;
        delete root;
        root = temp;
    }

    m_Length--;
    return returnedValue;
}

template<typename T>
bool BinarySearchTree<T>::RemoveElement(T value) {
    //if it was the first element use this method
    if (root->data == value) {
        RemoveRoot();
        return true;
    }

    Node* traversingNode = root;
    Node* previousNode = root;
    while (traversingNode->data != value)
    {
        //if it was not found
        if ((traversingNode->data > value &&
            traversingNode->leftChild == nullptr)
            || (traversingNode->data < value &&
                traversingNode->rightChild == nullptr)) {
            return false;
        }

        //if it was found
        if (traversingNode->data == value) {
            break;
        }
        else if (traversingNode->data > value) {
            previousNode = traversingNode;
            traversingNode = traversingNode->leftChild;
        }
        else if (traversingNode->data < value)
        {
            previousNode = traversingNode;
            traversingNode = traversingNode->rightChild;
        }
    }

    //if it was a leaf node
    if (traversingNode->leftChild == nullptr && traversingNode->rightChild == nullptr) {
        //if it was the left child of the previous node
        if (previousNode->leftChild == traversingNode) {
            previousNode->leftChild = nullptr;
        }
        //if it was the right child of the previous node
        else {
            previousNode->rightChild = nullptr;
        }
    }
    //if it has only left child
    else if (traversingNode->leftChild != nullptr && traversingNode->rightChild == nullptr) {
        Node* tempNode = traversingNode->leftChild;
        //if it was the left child of the previous node
        if (previousNode->leftChild == traversingNode) {
            previousNode->leftChild = tempNode;
        }
        //if it was the right child of the previous node
        else {
            previousNode->rightChild = tempNode;
        }
    }
    //if it has only right child
    else if (traversingNode->leftChild == nullptr && traversingNode->rightChild != nullptr) {
        Node* tempNode = traversingNode->rightChild;
        //if it was the left child of the previous node
        if (previousNode->leftChild == traversingNode) {
            previousNode->leftChild = tempNode;
        }
        //if it was the right child of the previous node
        else {
            previousNode->rightChild = tempNode;
        }
    }
    //both are not null
    else {
        Node* temp = DiveDownToReplace(traversingNode);
        //if it was the left child of the previous node
        if (previousNode->leftChild == traversingNode) {
            temp->leftChild = traversingNode->leftChild;
            temp->rightChild = traversingNode->rightChild;
            previousNode->leftChild = temp;
        }
        //if it was the right child of the previous node
        else {
            temp->leftChild = traversingNode->leftChild;
            temp->rightChild = traversingNode->rightChild;
            previousNode->rightChild = temp;
        }
    }

    delete traversingNode;
    m_Length--;
    return true;

}

template<typename T>
void BinarySearchTree<T>::PrintAllElements(TraverseMethod traverseMethod) {
    switch (traverseMethod)
    {
    case TraverseMethod::preorder:
        PreOrder(root);
        break;
    case TraverseMethod::inorder:
        InOrder(root);
        break;
    case TraverseMethod::postorder:
        PostOrder(root);
        break;
    case TraverseMethod::levelorder:
        LevelOrder(false);
        break;
    }
}

template<typename T>
bool BinarySearchTree<T>::IsEmpty() {
    return m_Length == 0;
}

template<typename T>
bool BinarySearchTree<T>::GetSize() {
    return m_Length;
}

template<typename T>
bool BinarySearchTree<T>::Contains(T value) {
    if (root == nullptr) return false;

    Queue<Node*> queue = Queue<Node*>();
    queue.Enqueue(root);
    while (!queue.IsEmpty()) {
        Node* tempNode = queue.Dequeue();
        if (tempNode->data == value) return true;

        //if it has a left child add it to the queue
        if (tempNode->leftChild != nullptr)
            queue.Enqueue(tempNode->leftChild);
        //if it has a right child add it to the queue
        if (tempNode->rightChild != nullptr)
            queue.Enqueue(tempNode->rightChild);
    }
    return false;
}

template<typename T>
void BinarySearchTree<T>::PreOrder(Node* node) {
    if (node == nullptr) return;
    print(node->data);
    PreOrder(node->leftChild);
    PreOrder(node->rightChild);
}

template<typename T>
void BinarySearchTree<T>::InOrder(Node* node) {
    if (node == nullptr) return;
    InOrder(node->leftChild);
    print(node->data);
    InOrder(node->rightChild);
}

template<typename T>
void BinarySearchTree<T>::PostOrder(Node* node) {
    if (node == nullptr) return;
    PostOrder(node->leftChild);
    PostOrder(node->rightChild);
    print(node->data);
}

//use BFS
template<typename T>
void BinarySearchTree<T>::LevelOrder(bool deleteNode) {
    if (root == nullptr) return;

    Queue<Node*> queue = Queue<Node*>();
    queue.Enqueue(root);
    while (!queue.IsEmpty()) {
        Node* tempNode = queue.Dequeue();
        //if we are destroying the binary search tree do not print the data
        if (!deleteNode) print(tempNode->data);

        //if it has a left child add it to the queue
        if (tempNode->leftChild != nullptr)
            queue.Enqueue(tempNode->leftChild);
        //if it has a right child add it to the queue
        if (tempNode->rightChild != nullptr)
            queue.Enqueue(tempNode->rightChild);
        //used for the destructor
        if (deleteNode) delete tempNode;
    }
}

template<typename T>
void BinarySearchTree<T>::DiveDownToAdd(T value, Node* node) {
    //base case
    if (node->leftChild == nullptr && node->data > value) {
        Node* leftChild = new Node();
        leftChild->data = value;
        leftChild->leftChild = nullptr;
        leftChild->rightChild = nullptr;
        node->leftChild = leftChild;
        return;
    }

    //base case
    if (node->rightChild == nullptr && node->data < value) {
        Node* rightChild = new Node();
        rightChild->data = value;
        rightChild->leftChild = nullptr;
        rightChild->rightChild = nullptr;
        node->rightChild = rightChild;
        return;
    }

    //we do not allow duplicate values
    if (node->data == value) {
        m_Length--;
        return;
    }

    //if the value is smaller than the value of the node, go to the left child node and check
    if (node->data > value) {
        DiveDownToAdd(value, node->leftChild);
    }
    //else go to the right child node and check
    else if (node->data < value) {
        DiveDownToAdd(value, node->rightChild);
    }
}

template<typename T>
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::DiveDownToReplace(Node* node) {
    if (node->leftChild->rightChild == nullptr) {
        return node->leftChild;
    }
    //otherwise
    Node* traversingNode = node->leftChild;
    Node* returnedNode;
    while (true) {
        if (traversingNode->rightChild->rightChild == nullptr) {
            returnedNode = traversingNode->rightChild;
            traversingNode->rightChild = returnedNode->leftChild;
            returnedNode->leftChild = nullptr;
            break;
        }
        traversingNode = traversingNode->rightChild;
    }
    return returnedNode;

}
