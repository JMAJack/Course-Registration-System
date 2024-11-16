// LinkedList Class Template
#ifndef LinkedList_H
#define LinkedList_H

#include "Node.h"
#include "Course.h"
// Use templates to allow the class to work with any data type (e.g., Student, Course, etc.)
// Example:
// LinkedList<Student> studentList;
// LinkedList<Course> courseList;

//<T> is a placeholder for the data type that will be used with the LinkedList

template <class T>
class LinkedList
{
private:
    Node<T> *head; // Template node

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
    void Insert(const T &data)
    {
        Node<T> *temp = new Node<T>(data);
        if (temp != NULL)
        {
            if (IsFull())
            {
                cerr << "List is full, Data cannot be added" << endl;
            }
            else
            {
                if (IsEmpty())
                {
                    head = temp;
                }
                else
                {
                    Node<T> *curr = head;
                    while (curr->GetNext() != NULL)
                    {
                        curr = curr->GetNext();
                    }
                    curr->SetNext(temp);
                }
            }
        }
    }

    // Count the number of nodes
    int Size() const
    {
        int count = 0;
        Node<T> *curr = head;
        while (curr != NULL)
        {
            count++;
            curr = curr->GetNext();
        }
        return count;
    }

    // Search for a node based on type T
    T *Search(const T &data)
    {
        Node<T> *curr = head;
        while (curr != nullptr)
        {
            if (curr->GetData() == data)
            {
                return &curr->GetData();
            }
            curr = curr->GetNext();
        }
        return nullptr; // Return default-constructed object if not found
    }

    // Check if the list is empty
    bool IsEmpty() { return head == NULL; }

    // Check if the list is full (memory allocation fails)
    bool IsFull()
    {
        Node<T> *temp = new Node<T>;
        if (temp != NULL)
        {
            delete temp;
            return false;
        }
        return true;
    }

    void Remove(const T &data)
    {
        if (IsEmpty())
        {
            cout << "List is Empty" << endl;
            return;
        }

        Node<T> *curr = head;
        Node<T> *prev = nullptr;

        // Special case: deleting the head node
        if (head->GetData() == data)
        {
            head = head->GetNext(); // Move head to the next node
            delete curr;
            return;
        }

        // Traverse the list to find the node to delete
        while (curr != nullptr)
        {
            if (curr->GetData() == data)
            { // Node with matching data found
                prev->SetNext(curr->GetNext());
                delete curr; // Delete the current node
                return;
            }
            prev = curr;            // Move prev to the current node
            curr = curr->GetNext(); // Move curr to the next node
        }
    }

    void EditNode(const T &data, const T &newData)
    {
        Node<T> *curr = head;
        while (curr != nullptr)
        {
            if (curr->GetData() == data)
            {
                curr->SetData(newData);
                return;
            }
            curr = curr->GetNext();
        }
    }

    // Display the list [MAY NEED TO CHANGE LATER]
    void DisplayList()
    {
        Node<T> *curr = head;
        if (!IsEmpty())
        {
            while (curr != NULL)
            {
                curr->GetData().Display(); // Assuming T has a Display method
                curr = curr->GetNext();
            }
        }
        else
        {
            cout << "List is empty" << endl;
        }
    }

    // Get node based on index
    Node<T> *GetNode(int index)
    {
        Node<T> *curr = head;
        int count = 0;
        while (curr != nullptr)
        {
            if (count == index)
            {
                return curr; // Return a pointer to the node
            }
            count++;
            curr = curr->GetNext();
        }
        return nullptr;
    }
};

#endif
