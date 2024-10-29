// LinkedList Class Template
#ifndef LinkedList_H
#define LinkedList_H

#include "Node.h"

// Use templates to allow the class to work with any data type (e.g., Student, Course, etc.)
//Example:
//LinkedList<Student> studentList;
//LinkedList<Course> courseList;

//<T> is a placeholder for the data type that will be used with the LinkedList

template <typename T>
class LinkedList {
private:
    Node<T> *head;  // Template node

public:
    // Default constructor
    LinkedList() { head = NULL; }

    // Primary constructor
    LinkedList(Node<T> *h) { head = h; }

    // Accessors
    Node<T> *GetHead() const { return head; }

    // Mutators
    void SetHead(Node<T> *h) { head = h; }

    // Insert at the back of the list
    void Insert(T data) {
        Node<T> *temp = new Node<T>(data);
        if (temp != NULL) {
            if (IsFull()) {
                cerr << "List is full, Data cannot be added" << endl;
            } else {
                if (IsEmpty()) {
                    head = temp;
                } else {
                    Node<T> *curr = head;
                    while (curr->GetNext() != NULL) {
                        curr = curr->GetNext();
                    }
                    curr->SetNext(temp);
                }
            }
        }
    }

    // Count the number of nodes
    int Size() const{
        int count = 0;
        Node<T> *curr = head;
        while (curr != NULL) {
            count++;
            curr = curr->GetNext();
        }
        return count;
    }

    // Search for a node by ID (assuming T has a GetId or equivalent method)
    T* Search(T id) {
        Node<T> *curr = head;
        while (curr != nullptr) {
            if (curr->GetData() == id) {  
                return curr->GetData();
            }
            curr = curr->GetNext();
        }
        return nullptr;  // Return default-constructed object if not found
    }

    // Check if the list is empty
    bool IsEmpty() { return head == NULL; }

    // Check if the list is full (memory allocation fails)
    bool IsFull() {
        Node<T> *temp = new Node<T>;
        if (temp != NULL) {
            delete temp;
            return false;
        }
        return true;
    }

    // Delete a node by ID
    void Remove(T data) {
        if (!IsEmpty()) {
            Node<T> *curr = head, *prev = NULL;
            while (curr != NULL) {
                if (curr->GetData() == data) {
                    if (curr == head) {
                        head = head->GetNext();
                    } else {
                        prev->SetNext(curr->GetNext());
                    }
                    delete curr;
                    break;
                }
                prev = curr;
                curr = curr->GetNext();
            }
        } else {
            cerr << "The list is empty; there is nothing to delete!" << endl;
        }
    }

    // Display the list [MAY NEED TO CHANGE LATER]
    void DisplayList () {
        Node<T> *curr = head;
        if (!IsEmpty()) {
            while (curr != NULL) {
                cout << "[";
                curr->GetData().Display();  // Assuming T has a Display method
                cout << "]->";
                curr = curr->GetNext();
            }
            cout << "NULL" << endl;
        } else {
            cout << "List is empty" << endl;
        }
    }

    
};

#endif
