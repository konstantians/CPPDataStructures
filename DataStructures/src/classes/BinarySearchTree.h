#pragma once
template<typename T>
class BinarySearchTree {
private:

    struct Node
    {
        T data;
        Node* leftChild;
        Node* rightChild;
    };

    int m_Length = 0;
    Node* root = new Node();

public:
    enum class TraverseMethod
    {
        preorder,
        inorder,
        postorder,
        levelorder
    };

    ~BinarySearchTree();
    void AddElement(T value);
    T RemoveRoot();
    bool RemoveElement(T value);
    void PrintAllElements(TraverseMethod traverseMethod);
    bool IsEmpty();
    bool GetSize();
    bool Contains(T value);

private:

    void PreOrder(Node* node);
    void InOrder(Node* node);
    void PostOrder(Node* node);
    void LevelOrder(bool deleteNode = false);
    void DiveDownToAdd(T value, Node* node);
    Node* DiveDownToReplace(Node* node);
};