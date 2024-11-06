// Joel Henry
// 2300087
// 10/20/2024

#ifndef Node_H
#define Node_H

#include <iostream>
using namespace std;


// Template Node class that can store any type of data (e.g., Student, Course)
template <class T>
class Node {
private:
    T data;          // Data stored in the node
    Node<T>* next;   // Pointer to the next node in the list

public:
    // Default Constructor
    Node() {
        next = NULL;
    }

    // Primary Constructor
    Node(T data) {
        this->data = data;
        this->next = NULL;
    }

    // Primary Constructor with Next Node
    Node(T data, Node<T>* next) {
        this->data = data;
        this->next = next;
    }

    // Copy Constructor
    Node(const Node<T>& n) {
        data = n.data;
        next = n.next;
    }

    // Accessors
    T GetData() {
        return data;
    }

    Node<T>* GetNext() {
        return next;
    }

    // Mutators
    void SetData(T data) {
        this->data = data;
    }

    void SetNext(Node<T>* next) {
        this->next = next;
    }

    // Optional: You could add a GetId() or GetCode() here if needed for searching
    // int GetId() { return data.GetId(); }  // If T has GetId()
};

#endif
